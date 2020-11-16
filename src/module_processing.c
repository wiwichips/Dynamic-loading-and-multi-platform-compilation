#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdarg.h> 
#include <assert.h> 
#include <errno.h> 

#include "os_defs.h"

#ifndef OS_WINDOWS
# include <dlfcn.h> 
# include <unistd.h> 
#else
# include <conio.h>
#endif

#include "module_tools.h"
#include "module_api.h"

/**
 *	This is where your work needs to happen.  Code has been provided
 *	to create a list for you to put the loaded modules in, but you
 *	need to add in all the code to actually load the modules and use
 *	them.
 */

/**
 * Tool to manage a list of modules.  This creates and initializes
 * a data structure to hold a list of Module structures, into which
 * you can put all of your information.
 */
ModuleList *createEmptyModuleList(int max)
{
	ModuleList *newList;

	newList = (ModuleList *) malloc(sizeof(ModuleList));
	newList->nModules = 0;
	newList->max = max;
	newList->modList = (Module *) malloc(newList->max * sizeof(Module));
	memset(newList->modList, 0, newList->max * sizeof(Module));

	return newList;
}

int destroyModuleList(ModuleList* mList) {
	// go through the modlist
	for (int i = 0; i < mList->nModules; i++) {
		free(mList->modList[i].name);
		free(mList->modList[i].data);
		//WINDOWS TODO ??? sharedObject
		free(&(mList->modList[i]));
	}
	free(mList->modList);
	// free(mList);
	return 0;
}

/**
 * Load all the modules.  The short names are provided in the
 * moduleNames list of strings, and there is a Module structure
 * set aside for each in moduleList, but you need to add the
 * code to actually make the loading happen.
 *
 * As the modules are loaded, they should be initialized.
 */
int
loadAllModules(ModuleList *moduleList, StringList *moduleNames, char *modpath, int verbosity)
{
	StringList *modulePathList;
	int i;
	char fname[20] = "";
	char* (*fnName)();
	char* error;

	// non windows based definitions
	#ifndef OS_WINDOWS
	void *libHandle = NULL;
	#else
	HMODULE libHandle = NULL;
	#endif

	/**
	 * Convert path to a list of strings.  This will leave
	 * you a nice list of strings with each path component
	 * that you can use in your search.
	 *
	 * Notice how the OS_WINDOWS macro from os_defs is
	 * used here to figure out if we are on Windows or
	 * not in order to use the right path delimiter.
	 */
	modulePathList = createEmptyStringList(256);
	addStringsToListWithDelimiter(modulePathList, modpath,
#			ifdef	OS_WINDOWS
			";"
#			else
			":"
#			endif
			);

	// load all modules passed
	for (i = 0; i < moduleNames->nStrings; i++) {
		#ifndef OS_WINDOWS
		sprintf(fname, "%s%s.so", modpath, moduleNames->strList[i]);
		#else
		sprintf(fname, "%s%s.dll", modpath, moduleNames->strList[i]);
		#endif
		
		// open the shared library
		#ifndef OS_WINDOWS
		libHandle = dlopen (fname, RTLD_LAZY);
		#else
		libHandle = LoadLibrary(fname);
		#endif
		
		// check validity
		if (libHandle == NULL) {
			#ifndef OS_WINDOWS
			fprintf(stderr, "Failed loading library : %s\n", dlerror());
			dlerror();
			#else
			fprintf(stderr, "Failed loading library\n");
			#endif
			return -1;
		}

		// get the pointer address of the function being called
		#ifndef OS_WINDOWS
		fnName = dlsym(libHandle, "transform"); // idea - make a dlsym wrapper 
		#else
		fnName = (char* (*) (char*) ) GetProcAddress(libHandle, "transform"); // idea - make a dlsym wrapper 
		#endif
		
		// check validity
		#ifndef OS_WINDOWS
		if ((error = dlerror()) != NULL)  {
			fprintf (stderr, "DL error trying to find 'helloWorld' : %s\n", error);
			return -1;
		}
		#else
		if (!fnName) {
			fprintf (stderr, "DL error trying to find 'helloWorld' : \n");
			return -1;
		}
		#endif
		
		char* str = (*fnName)("he said: \"okay.\" Can you believe that?");
		printf("transformed string: %s\n", str);
		free(str);
		str = NULL;

		// close the shared library with the handle
		#ifndef OS_WINDOWS
		dlclose(libHandle);
		#else
		FreeLibrary(libHandle);
		#endif
	}

	// free any memory etc
	destroyStringList(modulePathList);

	return moduleList->nModules;
}


/**
 * Call the finalization function for each module, and then unload
 * it from memory, cleaning up all the resources as you go.
 */
void
unloadAllModules(ModuleList *modules)
{
	void (*termSymb)(void *);
	int i;

	puts("unloadAllModules just called");
	destroyModuleList(modules);

	for (i = 0; i < modules->nModules; i++) {

		/**
		 * Clean up by calling the finalization function
		 */
		/** ... add your code here ... */
		

		/**
		 * Now unload the library
		 */
		/** ... add your code here ... */
		

		/**
		 * Clean up any other memory that we have to
		 */
		/** ... add your code here ... */


	}

	/**
	 * Flag the modules structure back to unitilialized state
	 */
	modules->nModules = 0;
}


/**
 * Do the main work of processing the given file stream.
 *
 * For all lines in the file, call for some processing to
 * happen.  After the processing is complete, print out
 * the final result.
 */
static int
processFPWithModuleList(FILE *ofp,FILE *ifp,const char *filename,ModuleList *moduleList,int verbosity)
{
	char line[BUFSIZ];
	int lineNo = 0;


	/**
	 * Do any setup that is required in your code before
	 * we get going...
	 */
	/* ... add your code here ... */


	/**
	 * Read lines, stopping when we get to EOF.  We can
	 * assume that BUFSIZ is plenty of length for each line
	 */
	while (fgets(line, BUFSIZ, ifp) != NULL) {

		/**
		 * Remove the trailing '\n' -- we will print it out
		 * separately below
		 */
		if (line[strlen(line)-1] == '\n') 
			line[strlen(line)-1] = '\0'; 

		/**
		 * apply each module in turn to the line.
		 */
		/** ... add your code here ... */





		/**
		 * Now that we have applied all the modules to
		 * this line, wite out the result of all of the
		 * processing
		 */
		/** ... add your code here ... */
		/*
		fputs(finalLineBuffer, ofp);
		*/

		/** add in the \n that we took off above */
		fputc('\n', ofp);
	}
	
	return 0;
}


/*
 * Open the indicated file, and then pass the open FILE handle
 * to the above function to actually do the processing.
 */
int
processFileWithModuleList(FILE *ofp,const char *filename,ModuleList *moduleList,int verbosity)
{
	FILE *ifp;
	int status;

	ifp = fopen(filename, "r");
	if (ifp == NULL) {
		fprintf(stderr, "Cannot open input script '%s' : %s\n",
				filename, strerror(errno));
		return -1;
	}

	status = processFPWithModuleList(ofp, ifp,
			filename, moduleList, verbosity);

	fclose(ifp);
	return status;
}

