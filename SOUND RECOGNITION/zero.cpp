#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <iostream>
using namespace std;

#define cpy(x)	for(int i = 0; i < min((x), (int)str_.length()); i++)\
			cs_[i] = str_[i];\
		cs_[min((x), (int)str_.length())] = 0;

char	cs_[70];
string	str_  ;

int main(int t, char** a) {
	system("umount /usb");
	system("fdisk -l > .alaki");
	ifstream fin(".alaki");
	while(fin >> str_) {
		if(str_.length() != 9)			continue;
		if(str_[8] == ':')			continue;
		cpy(5); if( strcmp(cs_, "/dev/"    ))	continue;
		cpy(8); if(!strcmp(cs_, "/dev/sda" ))	continue;
		cout << str_ << endl;
		break;
	}
	fin.close();
	system("rm -f .alaki");
	system(("mount " + str_ + " /usb/").c_str());
	system("cp /usb/Recordings/rec* /root/SndFile");
	system("ls /usb/Recordings/rec* > .x");
	sleep(5);
	ifstream cin(".x");
	while(cin >> str_) {
		system(("./o1 " + str_ + " " + a[1]).c_str());
		system("./o2");
		system("./o3");
		system("cat .2 >> .20");
	}
	cin.close();
	system("rm -f .x");
	system("umount /usb/");
	system("./o4");
	return 0;
}
