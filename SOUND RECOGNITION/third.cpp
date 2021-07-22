#include <cmath>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#define fi(e) for(int i = 0; i < (int)(e); i++)
#define fj(e) for(int j = 0; j < (int)(e); j++)
#define fk(e) for(int k = 0; k < (int)(e); k++)

const int maxn = 1000;
const int maxm = 1000;
const int maxp =  100;

string name;

double d_;

int	_;
int	K_;
int	nfft;
int	smplrt;
int	meln;
int	fl;
int	fu;

double	p   [maxm][maxn];
double	mel [maxp];
double	imel[maxp];
int	f   [maxp];
double	e   [maxm][maxp];
double	d   [maxm][maxp];

int main() {
	ifstream cin(".1");
	cin >> name >> _ >> K_ >> nfft >> smplrt;
	fi(_) fj(K_) cin >> p[i][j];
	cin.close();
	meln = 26;
	fl =  300;
	fu = 8000;
	mel[0]      = 1125 * log(1 + fl / 700.0);
	mel[meln+1] = 1125 * log(1 + fu / 700.0);
	d_ = mel[meln+1] - mel[0];
	fi(meln) mel[i+1] = mel[0] + d_ * (i + 1) / (meln + 1);
	fi(meln+2) imel[i] = 700 * (exp(mel[i] / 1125) - 1);
	fi(meln+2) f[i] = (nfft + 1) * imel[i] / smplrt;
	fi(_) fj(K_) fk(meln)
		if	(j <  f[k] || j > f[k+2]) ;
		else if	(j >= f[k] && j < f[k+1]) e[i][k] += p[i][j] * 1.0 * (j - f[k]   ) / (double)(f[k+1] - f[k  ]);
		else				  e[i][k] += p[i][j] * 1.0 * (f[k+2]  - j) / (double)(f[k+2] - f[k+1]);
//	fi(_) fj(K_)   cout << p[i][j] << ' '; cout << endl << endl;
//	fi(_) fj(meln) cout << e[i][j] << ' '; cout << endl << endl;
	fi(_) fj(meln)
		if(e[i][j]) 	e[i][j] = log10(e[i][j]);
		else 		e[i][j] = (1l << 62) - 1;
	fi(_) fj(meln) fk(meln) d[i][j] += e[i][k] * cos((2*k+1)*j*acos(-1)/2/meln);
//	fi(_) fj(12) cout << e[i][j+1] << ' ';
//	fi(_) fj(12) cout << d[i][j+1] << ' ';
	fi(_) d[i][0] /= sqrt(1.0 * meln);
	fi(_) fj(meln-1) d[i][j+1] *= sqrt(2.0 / meln);
	ofstream cout(".2");
	cout << name << endl <<  _ << endl;
	fi(_) fj(12) cout << d[i][j+1] << ' ';
	cout << endl;
	cout.close();
	return 0;
}
