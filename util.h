
#ifndef UTIL_H
#define UTIL_H

int read16(const unsigned char *a);
int read32(const unsigned char *a);
int readfloat(const unsigned char *a);
void write16(unsigned char *a, int b);
void write32(unsigned char *a, int b);
void writefloat(unsigned char *a, float f);

int stringreplace(char *in, int insize, char *out, int outsize, const char *search, const char *replace);

#endif

