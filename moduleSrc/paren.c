#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../src/os_defs.h"
#include "module_api.h"

OS_EXPORT void OS_C_DECL
hello()
{
	puts("Init: Module Paren has been initialized");
}

OS_EXPORT void OS_C_DECL
goodbye()
{
	puts("Done: Module Paren has been de-initialized");
}

OS_EXPORT char* OS_C_DECL
transform(char* str) {
  return stringWrap(str, '(', ')');
}
