#include<stdlib.h>
#ifndef VECTOR_TYPE
#define VECTOR_TYPE long long
#endif
struct vector{	//  max size = 2^l-1
	long long l,s;
	VECTOR_TYPE *a[61];
};
int vec_ini(struct vector *v){
	int i;
	for(i=0;i<61;i++)v->a[i]=0;
	return v->l=v->s=0;
}
int vec_add(struct vector *v,VECTOR_TYPE x){
	if(v->s+1==1LL<<v->l)
		return	v->a[v->l]=(VECTOR_TYPE*)malloc(sizeof(VECTOR_TYPE)*1LL<<v->l),
			v->a[v->l++][0]=x,v->s++,0;
	return v->s++,v->a[v->l-1][v->s-(1LL<<(v->l-1))]=x,0;
}
VECTOR_TYPE *vec_ind(struct vector *v,long long i){
	register long long l,m,r;
	for(l=0,r=v->l;l+1<r;)
		if((1LL<<(m=(l+r)>>1))<=i+1)l=m;else r=m;
	return &v->a[l][i-(1LL<<l)+1];
}
int vec_del(struct vector *v){
	for(;v->l;v->l--)free(v->a[v->l-1]),v->a[v->l-1]=0;
	return v->l=v->s=0;
}
