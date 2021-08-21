
#include <stdlib.h>
#include <stdio.h>
#include "file.h"

int readfile(char *filename, void **mem, int *size)
{
	FILE *file;
	char *filemem;
	int filesize, readsize;
	*mem = NULL;
	*size = 0;
	file = fopen(filename, "rb");
	if (!file)
		return -1;
	fseek(file, 0, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0, SEEK_SET);
	filemem = malloc(filesize+1);
	if (!filemem)
	{
		fclose(file);
		return -1;
	}
	readsize = fread(filemem, 1, filesize, file);
	fclose(file);
	if (readsize < filesize)
	{
		free(filemem);
		return -1;
	}
	((char *)filemem)[filesize] = 0; // null terminate the text file
	*mem = filemem;
	*size = filesize;
	return 0;
}

int writefile(char *filename, void *mem, int size)
{
	FILE *file;
	int writesize;
	file = fopen(filename, "wb");
	if (!file)
		return -1;
	writesize = fwrite(mem, 1, size, file);
	fclose(file);
	if (writesize < size)
		return -2;
	return 0;
}
