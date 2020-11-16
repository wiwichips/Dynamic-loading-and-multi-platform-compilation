#include <string.h>
#include <stdlib.h>

// returns a malloc'd string
OS_EXPORT char* OS_C_DECL
transform(char* str);

// used by transform to add a character to the start and end
char* stringWrap(char* str, char start, char end) {
  int length = strlen(str);
  char* newStr = malloc(sizeof(char) * (length + 3));
  newStr[0] = start;
  for (int i = 1; i <= length; i++) {
    newStr[i] = str[i - 1];
  }
  newStr[length + 1] = end;
  newStr[length + 2] = 0;
  return newStr;
}
