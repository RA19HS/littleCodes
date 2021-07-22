#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace cv;
using namespace std;

#define UC	unsigned char
#define VM	vector<Mat>
#define VS	vector<string>
#define PDI	pair<double, int>
#define PSI	pair<string, int>
#define MSI	map <string, int>
#define F	first
#define S	second
#define pb	push_back
#define fi(e)	for(int i = 0; i < (int)(e); i++)
#define fj(e)	for(int j = 0; j < (int)(e); j++)
#define fk(e)	for(int k = 0; k < (int)(e); k++)

const int	maxn = 100*1000;
const int	maxm = 1000;
const double	EPS  = 1e16;

int	i_;
double	d_;
double	d__;
UC *	uca_;
string	str_;
Mat	mat_;
Mat	mt2_;

VM	in;

int	m;
int	n;
int	c;
int	f   [maxm][maxn];
double	avg [maxn];
int	d   [maxm][maxn];
int	l   [maxm][maxm];
double	eval[maxm];
double	evec[maxm][maxm];
double	u   [maxm][maxn];
double	w   [maxm][maxm];
int	cont[maxn];
VS	nam;
double	dist[maxm];
double	p   [maxn];
PDI	res [maxm];
int	rcnt[maxn];
MSI	mp;

int cmp(PSI, PSI);

int main(int argc, char * argv[]) {
	ofstream cout("/root/OPENCV/output");
	VideoCapture cp;
	cp.open(0);
	if(strcmp(argv[1], "ins")) {
		while(waitKey(10) != 27) {
			cp >> mat_;
			mat_ = mat_(Rect(300, 200, 168, 192));
			cvtColor(mat_, mt2_, CV_BGR2GRAY);
			imshow("doorbin", mt2_);
		}
		imwrite("t.pgm", mt2_);
		mt2_ = imread("t.pgm", CV_LOAD_IMAGE_COLOR);
		cout << "mt2_ size : " << mt2_.rows << ' ' << mt2_.cols << endl;
	}
	else {
		ofstream ofs(".1");
		while(waitKey(10) != 27) {
			cp >> mat_;
			mat_ = mat_(Rect(300, 200, 168, 192));
			cvtColor(mat_, mat_, CV_BGR2GRAY);
			imshow("cam", mat_);
			if(waitKey(10) == 97) {
				stringstream ss;
				ss << i_;
				i_ ++;
				ss >> str_;
				string str__ = "face/";
				str_ = str__ + argv[2] + str_ + ".pgm";
				ofs << argv[2] << ' ' << str_ << endl;
				imwrite(str_, mat_);
				waitKey(0);
			}
		}
		ofs << endl;
		ofs.close();
		str_ = "cat .1 >> ";
		str_ += argv[3];
		system(str_.c_str());
		cout.close();
		return 0;
	}
	//mt2_ = imread("face/a1.pgm", CV_LOAD_IMAGE_COLOR);
	cout << argv[1] << endl;
	ifstream fin(argv[1]);
	c = m = 0;
	i_ = 0;
	while(fin >> str_) {
		m++;
		nam.pb(str_);
		if(!mp.count(str_)) mp[str_] = i_++;
		cont[mp[str_]]++;
		fin >> str_;
		mat_ = imread(str_, CV_LOAD_IMAGE_COLOR);
		if(!mat_.data) { cout << "No image data " << str_ << endl; return -1; }
		in.pb(mat_);
	}
	c = i_;
	in.pb(mt2_);
	fin.close();
	namedWindow("INIT FACE", CV_WINDOW_AUTOSIZE);
	imshow("INIT FACE", in[m]);
	cout << "IMREAD FINISH" << endl;
	cout << "!!!!!!!!!!" << endl;
/**	fi(m) {
		stringstream ss; ss << i; ss >> str_;
		str_ = "FACE " + str_;
		namedWindow(str_, CV_WINDOW_AUTOSIZE);
		imshow(str_, in[i]);
	}
/**/	fi(m+1) {
		i_ = 0;
		uca_ = in[i].data;
		fj(in[i].rows) fk(in[i].cols) {
			f[i][i_/3] = uca_[i_];
			i_ += 3;
		}
	}
	n = i_/3;
	fi(m) fj(n) avg[j] += (double)f[i][j]/m;
/**/	cout << n << ' ' << in[0].channels() << endl;
	mat_ = Mat::zeros(mat_.size(), mat_.type());
	i_ = 0;
	fi(in[0].rows) fj(in[0].cols) {
		fk(3) mat_.at<Vec3b>(i,j)[k] = saturate_cast<uchar>((int)avg[i_]);
		i_++;
	}
	namedWindow("AVG", CV_WINDOW_AUTOSIZE);
/**/	imshow("AVG", mat_);
	fi(m+1) fj(n) d[i][j] = f[i][j] - avg[j];
	fi(m)   fj(m) fk(n) l[i][j] += d[i][k] * d[j][k];
	ofstream fout("/root/OPENCV/.eigen");
	fout << m << endl;
	cout << m << endl;
	fi(m) fj(m) fout << l[i][j] << endl;
	fout.close();
	char* v[] = {"./eigen", "/root/OPENCV/.eigen", NULL};
	pid_t pid = fork();
	if(!pid) { execv("/root/OPENCV/eigen",  v); cerr << "AHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAN(eigen ro besaz)" << endl; }
	else	waitpid(pid, &i_, 0);
	fin.open(".eigen");
	fi(m) {
		fin >> eval[i];
		fj(m) fin >> evec[i][j];
	}
	fin.close();
	fi(m)   fj(n) fk(m) u[i][j] += evec[i][k] * d[k][j];
	fi(m+1) fj(m) fk(n) w[i][j] += u   [j][k] * d[i][k];
	fi(m) {
		d_ = 0;
		fj(m) d_ += (w[m][j] - w[i][j]) * (w[m][j] - w[i][j]);
		res[i] = make_pair(d_, i);
	}
	sort(res, res+m);
	fi(m) cout << res[i].S << ' ' << res[i].F << endl; cout << endl;
//	fi(m) if(res[i].F > 4e27) break; else { dist[clas[res[i].S]] += (res[i].F - res[0].F) * (res[i].F - res[0].F); rcnt[clas[res[i].S]]++; }
//	fi(m/2) if(res[i].F > 4e27) break; else { dist[clas[res[i].S]] /= rcnt[clas[res[i].S]]; }
	fi(m) dist[mp[nam[res[i].S]]] += res[i].F / cont[mp[nam[res[i].S]]];
/**/	d_ = dist[mp.begin()->S];
	str_ = mp.begin()->F;
	for(MSI::iterator it = mp.begin(); it != mp.end(); it++)
		if(d_ > dist[it->S]) {
			d_ = dist[it->S];
			str_ = it->F;
		}
	cerr << str_ << ' ' << d_ << endl;
/**/	cout << "init face no. : " << m << endl;
/**	fi(m/2) {
		if(res[i].F > 4e27) break;
		stringstream ss; ss << res[i].S; ss >> str_;
		str_ = "FACE " + str_;
		namedWindow(str_, CV_WINDOW_AUTOSIZE);
		imshow(str_, in[res[i].S]);
	}
/**/	namedWindow("CLOSEST FACE", CV_WINDOW_AUTOSIZE);
	imshow("CLOSEST FACE", in[res[0].S]);
/**/	cout << "MIN DISTANCE : " << res[0].S << ' ' << res[0].F << endl;
	if(d_ < 1e16)	cout << "VERY CLOSE TO " << res[0].S << endl;
	for(MSI::iterator it = mp.begin(); it != mp.end(); it++)
		cout << it->F << " : " << dist[it->S] << " COUNT " << cont[it->S] << endl;
	fi(m) fj(n) p[j] += w[m][i] * u[i][j];
	d_ = 0;
	fi(n) d_ += (d[m][i] - p[i]) * (d[m][i] - p[i]);
	cout << "FACENESS " << d_ << endl;
	cout.close();
	system("cat output");
	waitKey(0);
	return 0;
}

