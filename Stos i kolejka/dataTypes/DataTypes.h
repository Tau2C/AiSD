#ifndef DATATYPES_1FDI_PRZ
#define DATATYPES_1FDI_PRZ

#include <stdbool.h>

typedef struct SFinger {
  int  id;
  char name[32];
} Finger;

typedef struct SPalm {
  int  id;
  bool  leftPalm;
  Finger fingers[5];
} Palm;

char * palmToString(Palm * palm, char * response, int responseSize);
char * fingerToString(const Finger * finger, char response[], int responseSize);
bool fingersEqual(const Finger * fingerOne, const Finger * fingerTwo);

#endif
