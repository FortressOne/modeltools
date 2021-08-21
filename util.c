
#include <string.h>
#include "util.h"

int read16(const unsigned char *a)
{
	return a[0] + a[1] * 256;
}

void write16(unsigned char *a, int b)
{
	a[0] = (unsigned char)(b);
	a[1] = (unsigned char)(b >> 8);
}

int read32(const unsigned char *a)
{
	return a[0] + a[1] * 256 + a[2] * 65536 + a[3] * 16777216;
}

void write32(unsigned char *a, int b)
{
	a[0] = (unsigned char)(b);
	a[1] = (unsigned char)(b >> 8);
	a[2] = (unsigned char)(b >> 16);
	a[3] = (unsigned char)(b >> 24);
}

int readfloat(const unsigned char *a)
{
	union
	{
		int i;
		float f;
	}
	u;
	u.i = read32(a);
	return u.f;
}

void writefloat(unsigned char *a, float f)
{
	union
	{
		int i;
		float f;
	}
	u;
	u.f = f;
	write32(a, u.i);
}

int stringreplace(char *in, int insize, char *out, int outsize, const char *search, const char *replace)
{
	int searchlength = strlen(search);
	char *inend = in + insize;
	char *outend = out + outsize;
	const char *b;
	while (in < inend-1 && *in)
	{
		if (out >= outend-1)
			return 0;
		if (in + searchlength < inend && !memcmp(in, search, searchlength))
		{
			in += searchlength;
			for (b = replace;*b;b++, out++)
			{
				if (out >= outend-1)
					return 0;
				*out = *b;
			}
		}
		else
			*out++ = *in++;
	}
	while (out < outend)
		*out++ = 0;
	return 1;
}


