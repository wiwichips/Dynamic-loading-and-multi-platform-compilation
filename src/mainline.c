#include <stdio.h>

/** include os_defs before checks based on OS */
#include "os_defs.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef OS_WINDOWS
# include<unistd.h>
# include <unistd.h> 
#else
# include <conio.h>
#endif

#include "module_tools.h"
#include "string_tools.h"

static int
printHelp(char *progname)
{
	printf("%s <options> [ <files> ]\n", progname);
	printf("\n");
	printf("Run scripts from files, or stdin if no file specified\n");
	printf("\n");
	printf("Options:\n");
	printf("-o <file>    : place output in <file>\n");
	printf("-v           : be more verbose\n");
	printf("-p <path>    : set search path for modules\n");
	printf("             : (default value taken from $%s variable)\n", VAR_MODPATH);
	printf("-m <modules> : add <modules> to processing chain.\n");
	printf("             : The value in <modules> is a comma separated list made\n");
	printf("             : up of short module names: box, paren, quote, shout\n");
	printf("\n");
	exit (1);
}

int
transformInput(StringList *moduleNames, char *modpath) {
	char line[BUFSIZ];
	int lineNo = 0;

	puts("Type \"exit\" or \"quit\" to end the program");
	puts("Type \"help\" for instructions");
	printf(">>> "); // get input
	while (fgets(line, BUFSIZ, stdin) != NULL) {
		if (line[strlen(line)-1] == '\n') 
			line[strlen(line)-1] = '\0'; 

		// printf("line = %s\n", line);
		if (loadAllModules(NULL, moduleNames,modpath, 0, line) < 0) {
			fprintf(stderr, "Modules not successfully loaded\n");
			exit (-1);
		}

		if (!strcasecmp(line, "exit") || !strcasecmp(line, "quit")) {
			return 0;
		} else if (!strcasecmp(line, "help")) {
			puts("Type \"exit\" or \"quit\" to end the program");
		}

		printf(">>> "); // get input
	}
	return 0;
}

int
main(int argc, char **argv)
{
	FILE *ofp = stdout;
	ModuleList *loadedModules;
	StringList *moduleNames;
	char *modulePath = NULL;
	char* modulePathENV = NULL;
	char *optionArg;
	int verbosity = 0;
	int processingStatus = 0;
	int fileOnlyArgC = 1;
	int exitStatus = (-1);
	int i, ch;

	/**
	 * Ensure that both the StringList and ModuleList
	 * know they are empty.
	 */
	loadedModules = createEmptyModuleList(MAX_N_MODULES);
	moduleNames = createEmptyStringList(MAX_N_MODULES);

	//Get the environment variable whose name is stored in VAR_MODPATH
	modulePathENV = getenv(VAR_MODPATH);

	/** there is no getopt on Windows, so just do the work ourselves */
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-'
#					ifdef OS_WINDOWS
					|| argv[i][0] == '/'
#					endif
				) {
			/** is a flag */
			switch (argv[i][1]) {
			case 'v':
				verbosity++;
				break;

			case 'o':
				optionArg = pullArgvOptionArgument(argv, &i, "o");
				if (optionArg == NULL) {
					printHelp(argv[0]);
					exit(-1);
				}
					
				if ((ofp = fopen(optionArg, "w")) == NULL) {
					(void) fprintf(stderr,
							"failed opening output file '%s' : %s\n",
							optionArg, strerror(errno));
					printHelp(argv[0]);
				}
				break;

			case 'p':
				modulePath = pullArgvOptionArgument(argv, &i, "p");
				if (modulePath == NULL) {
					printHelp(argv[0]);
					exit(-1);
				}

				break;

			case 'm':
				optionArg = pullArgvOptionArgument(argv, &i, "m");
				if (optionArg == NULL) {
					printHelp(argv[0]);
					exit(-1);
				}

				if (addStringsToListWithDelimiter(
							moduleNames, optionArg, ",") < 0) {
					fprintf(stderr, "Failed adding module name to list\n");
					exit(-1);
				}
				break;


			case '?':
			case 'h':
			default:
				printf("HELP!\n");
				printHelp(argv[0]);
				break;
			}
		} else {
			/**
			 * is a file -- move it up the list
			 * (overwriting non-file options)
			 */
			argv[fileOnlyArgC++] = argv[i];
		}
	}

	/** if no modules are loaded yet, try the "default" module */
	if (moduleNames->nStrings == 0) {
		printf("Error: no modules specified!\n");
		printf("Provide at least one -m option\n\n");
		printHelp(argv[0]);
		exit (-1);
	}

	// get array of modules
	

	// open the file and transform it
	if (fileOnlyArgC <= 1) {
		transformInput(moduleNames, modulePath);
	} else {
		// transform line by line
		for (i = 1; i < fileOnlyArgC; i++) {
			if (processFileWithModuleList(ofp, argv[i], loadedModules, verbosity, moduleNames,modulePath) < 0) {
				exitStatus = (-1);
				break;
			}
		}
	}

	// clean up 
	unloadAllModules(loadedModules);
	destroyStringList(moduleNames);
	free(loadedModules);
	return exitStatus;
}

