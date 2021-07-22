#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<termios.h>
char c;
struct termios a;
int main(int n, char *in[]){
	assert(n==2);
	for(assert((n=atoi(in[1]))>0);n--;){
		fflush(stdout);
		tcgetattr(0, &a);
		a.c_lflag &= ~ICANON;
		a.c_lflag |= ECHO;
		a.c_cc[VMIN]  = 1;
		a.c_cc[VTIME] = 0;
		tcsetattr(0, TCSAFLUSH, &a);
		read(0, &c, 1);
	}
	fflush(stdout);
	return 0;
}
