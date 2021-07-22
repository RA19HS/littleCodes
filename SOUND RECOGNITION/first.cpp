#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>

SNDFILE* sf;
SNDFILE* sfout;
SF_INFO info;

int num, num_items;
int* buf;
int* buf2;
int f,sr,c;
FILE* out;

int main(int argc, char** argv) {
	info.format = 0;
	sf = sf_open(argv[1], SFM_READ, &info);
	if (sf == NULL) {
		printf("Failed to open the file.\n");
		exit(-1);
	}
	f = info.frames;
	sr = info.samplerate;
	c = info.channels;
///	printf("frames=%d\n", f);
///	printf("samplerate=%d\n", sr);
///	printf("channels=%d\n", c);
	num_items = f * c;
///	printf("num_items=%d\n", num_items);
	buf = (int*)malloc(num_items * sizeof(int));
	num = sf_read_int(sf, buf, num_items);
	sf_close(sf);
///	printf("Read %d items\n", num);
	out = fopen(".0", "w");
	fprintf(out, "%s\n", argv[2]);
	fprintf(out, "%d\n", num    );
	for(int i = 0; i < num; i += c) {
		for(int j = 0; j < c; j++)
			fprintf(out, "%d ", buf[i+j]);
		fprintf(out, "\n");
	}
	fflush(NULL);
	fclose(out);
	free(buf);
	return 0;
	buf2 = (int*)malloc(2 * 88300 * sizeof(int));
	for(int i = 0; i < 2 * 88300; i++)
		buf2[i] = buf[(i%1000)+40000];
	info.frames = 88300;
	printf("!!!!!!num_items = %d\n", num_items);
	sfout = sf_open("out.wav", SFM_WRITE, &info);
	sf_write_int(sfout, buf2, 2 * 88300);
	sf_close(sfout);
	return 0;
}

