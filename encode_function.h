#ifndef ENCODE_FUNCTION_H
#define ENCODE_FUNCTION_H

#define _GNU_SOURCE
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sysexits.h>
#include <sys/stat.h>

int getVal(char **tmpBuff, const char *search);
int getType(char *payload);
char *getPayload(char *tmpBuff, char *payload);
char *getPacket(char *tmpBuff, char *payload, off_t fileEnd);
void notdigit(char **packetCapture);
uint32_t convertInt(float tmpNum);
//char payVals(char **packetCapture, const char *search, off_t fileEnd);

#endif
