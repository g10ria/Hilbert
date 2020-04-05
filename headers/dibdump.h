#ifndef dibdump_h
#define dibdump_h

#include <windows.h>

int *readBitmap(char *, char *);
void writePelsToTextFile(unsigned int *, int, char *);
void writeBitmap(char *, char *, char *);
void writeBitmapHelper(char *, unsigned int *, int, BITMAPFILEHEADER, BITMAPINFOHEADER);

#endif