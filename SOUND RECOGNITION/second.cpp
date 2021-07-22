#include <cmath>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#define C	pair<double, double>
#define F	first
#define S	second
#define mp	make_pair
#define fi(e)	for(int i = 0; i < (int)(e); i++)
#define fj(e)	for(int j = 0; j < (int)(e); j++)
#define fk(e)	for(int k = 0; k < (int)(e); k++)

const int maxm	= 1000;
const int maxn	= 1000;
const int maxp	= 1000;
const int maxq	= 1000 * 1000;

string name;

int	_;
int	n;
int	d;
int	N;
int	smplrt;
int	K;
int	K_;
double	fl;
double	fu;
int	meln;
double	a   [maxq];
double	h   [maxm];
C	s   [maxn][maxp];
double	p   [maxn][maxp];

int main() {
///	printf("%.30f\n", exp ( 1)); fflush(stdout);
///	printf("%.30f\n", acos(-1)); fflush(stdout);
	ifstream cin(".0");
	cin >> name >> n;
	fi(n) cin >> a[i];
	cin.close();
	d  = 160;
	N  = 400;
	K  = 512;
	K_ = 257;
	smplrt = 16000;
	fi(N) h[i] = 0.54 - 0.46 * cos(2 * acos(-1) * i / (N - 1));
	_ = 0;
///	cerr << "ninja1." << endl;
	for(int k = 0; (k + N <= n) && (_ < 254); k += d, _++/*, cerr << k << endl*/) fi(K) fj(N)
		s[_][i] = mp(	s[_][i].F + a[k+j] * h[j] * cos(-2 * acos(-1) * i * j / N),
				s[_][i].S + a[k+j] * h[j] * sin(-2 * acos(-1) * i * j / N));
///	cerr << "ninja2." << endl;
	fk(_) fi(K)
		p[k][i] = (s[k][i].F * s[k][i].F + s[k][i].S * s[k][i].S) / N;
	ofstream fout(".1");
	fout	<< name << endl
		<< _  << endl
		<< K_ << endl
		<< K  << endl
		<< smplrt << endl;
	fi(_) fj(K_) fout << p[i][j] << endl;
	fout.close();
	return 0;
}

