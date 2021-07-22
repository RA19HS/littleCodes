#include <map>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

#define PDI	pair<double, int>
#define MSI	map <string, int>
#define pb	push_back
#define F	first
#define S	second
#define fi(e)	for(int i = 0; i < (int)(e); i++)
#define fj(e)	for(int j = 0; j < (int)(e); j++)
#define fk(e)	for(int k = 0; k < (int)(e); k++)
#define fl(e)	for(int l = 0; l < (int)(e); l++)
#define min(a, b, c) min((double)a, min((double)b, (double)c))

const int maxn =  100;
const int maxm = 1000;
const int maxp =  100;

int	n = 0;
int	m;
int	p = 12;


int	i_;
double	d_;
string	s_;

vector<string> v;

double	a  [maxn][maxm][maxp];
int	b  [maxn];
int	c  [maxn];
double	t  [maxm][maxm];
double	d  [maxn];
PDI	r  [maxn];
MSI	mp ;
string	rev[maxn];
int	cnt[maxn];
double	res[maxn];

int main(int argc, char** argv) {
	int x = 0;
	stringstream ss;
	ss << argv[1];
	ss >> x;
	cout << "X = " << x << endl;
	i_ = 0;
	ifstream cin(".20");
	while( cin >> s_ ) {
		if(mp.count(s_)) cnt[mp[s_]]++;
		else { rev[i_] = s_; mp[s_] = i_++; cnt[mp[s_]] = 1; }
		v.pb(s_);
		cin >> b[n];
		fj(b[n]) fk(p) cin >> a[n][j][k];
		n++;
	}
	cin.close();
	//fi(n) { cout << "asdfghjk" << endl; cout << b[i] << endl; fj(b[i]) fk(p) cout << a[i][j][k] << ' '; cout << endl; }
	fi(n) {
		if(i == x) continue;
		fi(maxm) fj(maxm) t[i][j] = 0;
		fi(maxm) t[i][0] = t[0][i] = 1l << 62;
		t[0][0] = 0;
		d_ = 0;
		fj(b[x]) fk(b[i]) {
			fl(p) d_ += (a[i][j][l] - a[x][k][l]) * (a[i][j][l] - a[x][k][l]);
			t[j+1][k+1] = d_ + min(t[j][k], t[j+1][k], t[j][k+1]);
		}
		d[i] = t[b[x]][b[i]];
	}
	//fi(b[0]) { fj(b[1]+10) cout << t[i+1][j+1] << ' '; cout << endl; }
	fi(n) res[mp[v[i]]] += d[i] / cnt[mp[v[i]]];
	fi(i_) r[i] = make_pair(res[i], i);
	sort(r, r + i_);
	fi(i_) { cout << rev[r[i].S] << " : ";
	printf("%.30e\n", r[i].F); }
	fi(n) r[i] = make_pair(d[i], i);
	sort(r, r + n);
	fi(n) { cout << v[r[i].S] << '(' << r[i].S << ')' << " \t: ";
       	printf("%.30e", r[i].F); cout << "\t(" << b[r[i].S] << ')'<< endl; }
	//fi(n) cout << v[i] << ' ' << i << " \t: " << d[i] << "\t(" << b[i] << ')'<< endl;
	return 0;
}
