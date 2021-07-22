/* TODO:	100..200 digits integer
 * 		big int functions:
 * 			= + - * % ==0 >0 &1 <<1 >>1 random() 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PRINT_ERROR(X)\
	do{return fprintf(stderr,(X)),1;}while(0)
#define PRINT_USAGE(X,Y) \
	do{	fprintf((X),	"Usage:  %s positive_integer | -h | --help\n",argv[0]);\
		fprintf((X),	"\nDetermine primality of a positive integer given as argument."\
				"\nThe integer must be less than 10^10."\
				"\nThis program first runs Fermat primality test on 123 random bases;"\
				"\nThen if passed, runs Miller-Rabin primality test on above bases."\
				"\nComplexity:  O(lg^3(n)), where n is the input integer."\
				"\nIf n is prime, then the output is \"PRIME\" with probability 1;"\
				"\nBut if composite, then the output is \"PRIME\" with probability at most 4^-123."\
				"\nThis probability is \"far less, for instance, than the probability that"\
				"\na random cosmic ray will sabotage the computer during the computation!\""\
				"\n  -- Algorithms. Dasgupta, Papadimitriou, and Vazirani. 2006. p 36.\n");\
		exit((Y));\
	}while(0)
int n;
char *endptr;
int power_mod(int,int,int);
int fermat(int);
int miller_rabin(int);
int main(int argc,char **argv){
	if(argc-2)PRINT_USAGE(stderr,1);
	if(!(strcmp(argv[1],"-h")*strcmp(argv[1],"--help")))PRINT_USAGE(stdout,0);
	if(strlen(argv[1])>9)PRINT_ERROR("at most 9 digits\n");
	n=strtol(argv[1],&endptr,0);
	if(*endptr)PRINT_ERROR("enter an integer\n");
	if(n<1)PRINT_ERROR("enter a positive integer\n");
	if(n==1)puts("one is exception");
	else if(n==2||fermat(n)&&miller_rabin(n))puts("PRIME");
	else puts("composite");
	exit(0);
}
int power_mod(int a,int b,int m){
	if(!b)return 1;
	long r;
	r=power_mod(a,b/2,m);
	r=r*r%m;
	if(b%2)r=r*a%m;
	return r;
}
int fermat(int n){
	int i;
	srand(7777777U+n);
	for(i=0;i<123;i++)
		if(power_mod(rand()%(n-2)+2,n-1,n)-1)
			return 0;
	return 1;
}
int miller_rabin(int n){
	int i,j,t,u,a;
	long x;
	srand(7777777U+n);
	for(t=0,u=n-1;u%2==0;)t++,u>>=1;	//  n-1 = 2^t*u,  u = 2k-1
	for(i=0;i<123;i++){
		a=rand()%(n-2)+2;
		x=power_mod(a,u,n);
		//if(power_mod(a,n-1,n)-1)return 0;	//  fermat primality test
		if(x==1)continue;
		for(j=0;j<t;j++,x=x*x%n)if(x==n-1)goto L;
		return 0;
L:;     }
	return 1;
}
