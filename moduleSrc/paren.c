#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../src/os_defs.h"
#include "module_api.h"


char* transform(char* str) {
  return stringWrap(str, '(', ')');
}
