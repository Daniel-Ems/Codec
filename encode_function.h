#ifndef ENCODE_FUNCTION_H
#define ENCODE_FUNCTION_H

#define _GNU_SOURCE
#include <stdio.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int getVal(char **tmpBuff, const char *search);
int getType(char *payload);
char *getPayload(char *tmpBuff, char *payload);
char *getPacket(char *tmpBuff, char *payload, off_t fileEnd);
void notdigit(char **packetCapture);
//char payVals(char **packetCapture, const char *search, off_t fileEnd);

#endif
