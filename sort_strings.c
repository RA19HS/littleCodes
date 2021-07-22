#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 1000
#define FOR for(i=0;i<n;++i)
char *s[N];
int i,n;
int cmp(const void*,const void*);
int main(){
	for(;s[n]=malloc(sizeof(char)*N),fgets(s[n++],N,stdin););--n;
	qsort(s,n,sizeof(char*),cmp);
	FOR printf("%s",s[i]);
	for(i=1;i<n;++i){int _=cmp(s+i-1,s+i);printf("%d\n",_);}
	FOR free(s[i]);
	return 0;
}
int cmp(const void *a,const void *b){
	return strcmp(*(char*const*)a,*(char*const*)b);
}
