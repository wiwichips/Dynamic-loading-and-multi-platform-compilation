#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../src/os_defs.h"
#include "module_api.h"


char* transform(char* str) {
  int length = strlen(str);
  int quoOff = 0;
  char* newStr = malloc(sizeof(char) * length + 1);

  for (int i = 0; i < length; i++) {
    if (str[i] == '\"') {
      newStr = realloc(newStr, sizeof(char) * length + quoOff + 2);
      newStr[i + quoOff++] = '\\';
    }
    newStr[i + quoOff] = str[i];
  }

  newStr[length + quoOff] = 0;

  char* final = stringWrap(newStr, '\"', '\"');
  free(newStr);
  return final;
}
