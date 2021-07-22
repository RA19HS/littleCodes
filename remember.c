#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 1234
int i;
char note[N+3],*home;
FILE *notebook;
int main(int argc,char *argv[]){
	home=getenv("HOME");
	notebook=fopen(strcat(home,"/.remember"),"a");
	if(!notebook)return fprintf(stderr,"Can't open %s\n",home),1;
	if(argc<2){
		printf("Enter note: ");
		fgets(note,N,stdin);
		if(!((int)note[0]*(note[0]-'\n')))exit(0);	//  |note| > 0
		i=strlen(note)-1,note[i]='\n';
		fprintf(notebook,"%s",note);
		exit(0);
	}
	for(i=1;i<argc;i++)fprintf(notebook,"%s ",argv[i]);
	fprintf(notebook,"\n");
	exit(0);
}
