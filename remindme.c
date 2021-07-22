#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 1234
#define TOUPPER(X) ('a'<=(X)&&(X)<='z'?(X)-'a'+'A':(X))
#define STRTOUPPER(X) for(i=0;X[i];i++)X[i]=TOUPPER(X[i]);
int i;
char note[N+3],*home,upper_note[N+3];
FILE *notebook;
int main(int argc,char *argv[]){
	if(argc>2)return fprintf(stderr,"at most one argument"),1;
	home=getenv("HOME");
	notebook=fopen(strcat(home,"/.remember"),"r");
	if(!notebook)return fprintf(stderr,"Can't open %s\nuse  remember  command\n",home),1;
	if(argc<2){for(;fgets(note,N,notebook);)printf("%s",note);exit(0);}
	STRTOUPPER(argv[1]);
	for(;fgets(note,N,notebook);){
		upper_note[0]=0;
		strcat(upper_note,note);
		STRTOUPPER(upper_note);
		if(strstr(upper_note,argv[1]))
			printf("%s",note);
	}
	exit(0);
}
