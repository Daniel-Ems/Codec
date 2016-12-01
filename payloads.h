#ifndef payload_H
#define paylaod_H

void StatusPayload(char *packetCapture, FILE* writeFile, struct EncodeZerg *ez);
void CommandPayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez);
void GpsPayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez);
void MessagePayload(char *packetCapture, FILE *writeFile, struct EncodeZerg *ez);
#endif
