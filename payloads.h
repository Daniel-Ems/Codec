#ifndef payload_H
#define paylaod_H

int StatusPayload(char *packetCapture, FILE* writeFile, struct EncodeZerg *ez);
int CommandPayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez);
int GpsPayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez);
int MessagePayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez);
#endif
