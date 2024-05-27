#include "DataTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * fingerToString(const Finger * finger, char response[], int responseSize) {
  static char formatFinger[]="Finger %d is %s\n";
  int textSize;

  if(responseSize < strlen(formatFinger)) {
    puts("fingerToString: response buffer to small");
    exit(-1);
  }
  if(NULL == response) {
    puts("fingerToString: no response buffer");
    exit(-1);
  }
  textSize = snprintf(response, responseSize, formatFinger, finger->id, finger->name);
  if(textSize < 0 || responseSize == textSize) {
    puts("fingerToString: response buffer overflow");
    exit(-1);
  }
  
  return response;
}

char * palmToString(Palm * palm, char * response, int responseSize) {
  puts("palmToString: not implemented");
  exit(-1);
}

bool fingersEqual(const Finger * fingerOne, const Finger * fingerTwo) {
  bool result, equalIDs, equalNames;

  result = equalIDs = equalNames = false;

  if (NULL == fingerOne || NULL == fingerTwo) {
    puts("fingersEqual: NULL given");
    exit(-1);
  }

  if(fingerOne->id == fingerTwo->id) {
    equalIDs = true;
  }
  if(0 == strcmp(fingerOne->name, fingerTwo->name)) {
    equalNames = true;
  }
  result = equalIDs && equalNames;
    
  return result;
}
