#include "encode_function.h"


int
getVal(char **tmpBuff, const char *search)
{
    int ver;

    *tmpBuff = strcasestr(*tmpBuff, search);
    while (!isdigit(**tmpBuff))
    {
        (*tmpBuff)++;

    }
    ver = strtol(*tmpBuff, NULL, 10);
    while (isdigit(**tmpBuff))
    {
        (*tmpBuff)++;
    }
    return ver;
}

int
getType(char *packetCapture)
{
    int type;

    if (strcasestr(packetCapture, "message"))
    {
        type = 0;
    }
    else if (strcasestr(packetCapture, "name"))
    {
        type = 1;
    }
    else if (strcasestr(packetCapture, "latitude"))
    {
        type = 3;
    }
    else
    {
        type = 2;
    }
    return type;
}

void
getPayload(char **packetCapture, int type)
{
    if (type == 2)
    {
        while (!isalpha(**packetCapture))
        {
            (*packetCapture)++;
        }
    }
    else
    {
        while (!isalpha(**packetCapture))
        {
            (*packetCapture)++;
        }
        while (isalpha(**packetCapture))
        {
            (*packetCapture)++;
        }
        while (!isalnum(**packetCapture))
        {
            (*packetCapture)++;
        }
    }
}

char *
getPacket(char *tmpBuff, char *payload, off_t fileEnd)
{
    char *tmpCapture = calloc(1, fileEnd + 1);
    int a;

    if ((payload = strcasestr(tmpBuff, "Version")))
    {
        int remainder = payload - tmpBuff;

        for (a = 0; a < remainder; a++)
        {
            tmpCapture[a] = *tmpBuff;
            tmpBuff++;
        }
    }
    else
    {
        memcpy(tmpCapture, tmpBuff, strlen(tmpBuff));
    }
    return tmpCapture;
}

void
notDigit(char **packetCapture)
{
    while (!isdigit(**packetCapture))
    {
        (*packetCapture)++;
    }
}

uint32_t
convertInt(float tmpNum)
{
    union converter
    {
        float speed;
        uint32_t test;
    };

    union converter speed_test;

    speed_test.speed = tmpNum;
    uint32_t maxSpeed = htonl(speed_test.test);

    return maxSpeed;
}

uint64_t
convertDoub(double number)
{
    union ConvertDoub
    {
        double placeHolder;
        uint64_t oldNumber;
    };

    union ConvertDoub conversion;

    conversion.placeHolder = number;
    return htobe64(conversion.oldNumber);
}

void
fileHeader(FILE * writeFile)
{
    struct FileHeader fh;

    fh.fileType = 0xa1b2c3d4;
    fh.majorVersion = 2;
    fh.minorVersion = 4;
    fh.gmtOffset = 0;
    fh.accuracyDelta = 0;
    fh.maximumLength = 0;
    fh.linkLayer = 1;

    fwrite(&fh, sizeof(fh), 1, writeFile);
    return;
}



int
writeHeaders(FILE * writeFile, int size)
{
    int fCheck;
    int exit = 0;

    struct PcapHeader ph;

    ph.unixEpoch = 0x00000000;
    ph.epochMicroseconds = 0x00000000;
    ph.captureLength = (54 + size);
    ph.packetLength = 0x00000000;

    fCheck = fwrite(&ph, sizeof(ph), 1, writeFile);
    exit = writeCheck(fCheck);
    if (exit)
    {
        return exit;
    }

    struct EthernetFrame ef;

    ef.d_mac = 0x000000000000;
    ef.s_mac = 0x111111111111;
    ef.type = 0x0008;

    fCheck = fwrite(&ef, sizeof(ef), 1, writeFile);
    exit = writeCheck(fCheck);
    if (exit)
    {
        return exit;
    }

    struct encodeIpv4 ei;

    ei.version = 0x45;
    ei.dscpEcn = 0x00;
    ei.total_length = htons(40 + size);
    ei.id = 0x00000000;
    ei.offset = 0x0016;
    ei.protocol = 0x1100;
    ei.checksum = 0x1234;
    ei.s_ip = 0x87654321;
    ei.d_ip = 0x12345678;

    fCheck = fwrite(&ei, sizeof(ei), 1, writeFile);
    exit = writeCheck(fCheck);
    if (exit)
    {
        return exit;
    }

    struct UdpHeader uh;

    uh.s_port = 0x1111;
    uh.d_port = 0xa70e;
    uh.length = htons(20 + size);
    uh.checksum = 0x4444;

    fCheck = fwrite(&uh, sizeof(uh), 1, writeFile);
    exit = writeCheck(fCheck);
    if (exit)
    {
        return exit;
    }

    return exit;
}

int
writeCheck(int fCheck)
{
    int exit = 0;

    if (fCheck != 1)
    {
        exit = 1;
    }
    return exit;
}
