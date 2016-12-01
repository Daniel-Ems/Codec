#ifndef ENCODE_FUNCTION_H
#define ENCODE_FUNCTION_H

#define _GNU_SOURCE
#define _BSD_SOURCE
#include <endian.h>
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
#include "structs.h"

void fileHeader(FILE *writeFile);
void ethernetHeader(FILE *writeFile);
int getVal(char **tmpBuff, const char *search);
int getType(char *payload);
void getPayload(char **packerCapture,int type);
char *getPacket(char *tmpBuff, char *payload, off_t fileEnd);
void notDigit(char **packetCapture);
uint32_t convertInt(float tmpNum);
uint64_t convertDoub(double number);
//char payVals(char **packetCapture, const char *search, off_t fileEnd);

#endif
