
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "util.h"

#ifdef WIN32
#define snprintf _snprintf
#endif

// scraps that would be useful for making makespr or makespr32 utilities
//"Quake sprite types:\n"
//"0 - doom1-style sprites, they stand upright and align with the view angle\n"
//"1 - upright and faces view location, they are angled when off to the side\n"
//"2 - (default) billboard, stays upright on screen and matches view angles\n"
//"3 - decal style, oriented by entity angles, bullet marks and shockwaves\n"
//"4 - billboard but rotates relative to view angles, spinning explosions etc\n"
//"Note: glquake only supports types 2 and 3\n"

void printusage(void)
{
	fprintf(stderr,
"usage: makesp2 <sp2filename> <imageprintf> <numframes> <width> <height>\n"
"example:\n"
"makesp2 models/explosion1.sp2 models/explosion1_%%02d.tga 20 64 64\n"
"(note: that would be frames named explosion1_00.tga then 01 and so on,\n"
"       use %%d by itself for _0 then _1 and so on)\n"
	);
	exit(1);
}

int main(int argc, char **argv)
{
	int i;
	int datasize;
	int numframes;
	int width;
	int height;
	unsigned char *data;
	unsigned char *framedata;
	char *sp2filename;
	char *imageprintf;

	if (argc != 6)
		printusage();

	sp2filename = argv[1];
	imageprintf = argv[2];
	numframes = atoi(argv[3]);
	width = atoi(argv[4]);
	height = atoi(argv[5]);

	if (numframes < 1 || width < 1 || height < 1)
		printusage();

	datasize = 12 + 80 * numframes;
	data = malloc(datasize);
	memcpy(data, "IDS2", 4);
	write32(data + 4, 2); // version
	write32(data + 8, numframes);
	for (i = 0;i < numframes;i++)
	{
		framedata = data + 12 + i * 80;
		write32(framedata, width);
		write32(framedata + 4, height);
		write32(framedata + 8, width / 2);
		write32(framedata + 12, height / 2);
		memset(framedata + 16, 0, 64);
		snprintf((char *)framedata + 16, 64, imageprintf, i);
	}
	writefile(sp2filename, data, datasize);
	free(data);
	return 0;
}
