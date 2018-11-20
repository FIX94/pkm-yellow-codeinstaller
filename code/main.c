/*
 * Copyright (C) 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#define COPYTOTAL 5
typedef struct _copyinfo {
	int frame;
	size_t offset;
	size_t length;
} copyinfo;
static copyinfo info[4][COPYTOTAL] =
{//installer
  { { 53454, 0x381, 0xE1 }, { 54943, 0x281, 0x100 }, { 55872, 0x181, 0x100 }, { 56801, 0x81, 0x100 }, { 57730, 0, 0x81 } }, //pokemon yellow
  { { 53842, 0x37C, 0xE6 }, { 55282, 0x27C, 0x100 }, { 56220, 0x17C, 0x100 }, { 57158, 0x7C, 0x100 }, { 58096, 0, 0x7C } }, //pokemon gelb
//updater
  { {  7145, 0x381, 0xE1 }, {  8650, 0x281, 0x100 }, {  9579, 0x181, 0x100 }, { 10512, 0x81, 0x100 }, { 11441, 0, 0x81 } }, //pokemon yellow
  { {  7176, 0x37C, 0xE6 }, {  8625, 0x27C, 0x100 }, {  9563, 0x17C, 0x100 }, { 10501, 0x7C, 0x100 }, { 11439, 0, 0x7C } }, //pokemon gelb
};

int main()
{
	printf("Pokemon Yellow Code Installer WIP by FIX94\n");
	//open up input log to install code
	FILE *log = fopen("tmp/Input Log.txt","rb+");
	if(!log)
	{
		printf("Unable to open input log!\n");
		return 0;
	}
	fseek(log,0,SEEK_END);
	size_t fsize = ftell(log);
	copyinfo *cinfo;
	const char *ccodename;
	if(fsize == 791940)
	{
		cinfo = info[0];
		ccodename = "yellow.bin";
	}
	else if(fsize == 803458)
	{
		cinfo = info[1];
		ccodename = "gelb.bin";
	}
	else if(fsize == 170605)
	{
		cinfo = info[2];
		ccodename = "yellow.bin";
	}
	else if(fsize == 167004)
	{
		cinfo = info[3];
		ccodename = "gelb.bin";
	}
	else
	{
		printf("Unexpected input log size!\n");
		fclose(log);
		return 0;
	}
	//read in raw code
	FILE *codebin = fopen(ccodename, "rb");
	if(!codebin)
	{
		printf("Unable to open code!\n");
		fclose(log);
		return 0;
	}
	fseek(codebin, 0, SEEK_END);
	size_t codesize = ftell(codebin);
	if(codesize > 0x462)
	{
		printf("Code too big to be installed!\n");
		fclose(codebin);
		fclose(log);
		return 0;
	}
	//extend code to 0x462 bytes if needed
	uint8_t codebuf[0x462];
	//fill in some easily checkable values
	memset(codebuf+cinfo[4].offset,0x10,cinfo[4].length);
	memset(codebuf+cinfo[3].offset,0x20,cinfo[3].length);
	memset(codebuf+cinfo[2].offset,0x30,cinfo[2].length);
	memset(codebuf+cinfo[1].offset,0x40,cinfo[1].length);
	memset(codebuf+cinfo[0].offset,0x50,cinfo[0].length);
	//read in code
	rewind(codebin);
	fread(codebuf, 1, codesize, codebin);
	fclose(codebin);
	//install code
	size_t cpos, clen;
	for(cpos = 0; cpos < COPYTOTAL; cpos++)
	{
		printf("Frame %i Buffer Offset %08x Length %i\n", cinfo[cpos].frame, cinfo[cpos].offset, cinfo[cpos].length);
		for(clen = 0; clen < cinfo[cpos].length; clen++)
		{
			//seek to exact frame position
			fseek(log, 0x3D+((cinfo[cpos].frame+(clen*3))*0xD), SEEK_SET);
			uint8_t v = codebuf[cinfo[cpos].offset+cinfo[cpos].length-clen-1];
			//print in button presses
			fprintf(log,"|%s%s%s%s%s%s%s%s.|",(v&0x40)?"U":".",(v&0x80)?"D":".",(v&0x20)?"L":".",(v&0x10)?"R":".",
				(v&0x8)?"S":".",(v&0x4)?"s":".",(v&0x2)?"B":".",(v&0x1)?"A":".");
		}
	}
	//done
	printf("Added code to inputs!\n");
	fclose(log);
	return 0;
}