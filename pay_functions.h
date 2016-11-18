#ifndef PAY_FUNCTIONS_H
#define PAY_FUNCTIONS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

extern union payload *zerg;
void messages(union payload *zerg);
void stat_payload(union payload *zerg);
void com_payload(union payload *zerg);
void gps(union payload *zerg);


#endif
