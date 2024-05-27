#include "TestDataTypes.h"
#include <stdio.h>

void createFingers(Finger * fingers) {
  Finger finger;

  finger.id = 1;
  snprintf(finger.name, 32, "%s", "pollex");
  fingers[0] = finger;

  finger.id = 2;
  snprintf(finger.name, 32, "%s", "index");
  fingers[1] = finger;

  finger.id = 3;
  snprintf(finger.name, 32, "%s", "digitus medius");
  fingers[2] = finger;

  finger.id = 4;
  snprintf(finger.name, 32, "%s", "digitus annularis");
  fingers[3] = finger;

  finger.id = 5;
  snprintf(finger.name, 32, "%s", "digitus minimus");
  fingers[4] = finger;
}

void printFingerInfo(const Finger * finger) { 
    char message[1024];

    fingerToString(finger, message, 1024);
    printf("%s", message);
}
