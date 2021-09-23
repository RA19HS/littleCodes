/* TODO
 * ability: add & remove user events
 */
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#define 	IRANTIMEZONE	(45LL*360)
#define		DAYLIGHTSAVE	3600LL
#define 	SECINDAY	(24LL*3600)
#define 	SECINYEAR	31556925.216L	//  365.24219 days in year  jalaali: 365 + 8/33
#define 	EPOCHYEAR	1348		//  epoch: 1348/10/11 3:30
#define 	EPOCHREMSEC	(286LL*SECINDAY)
#define		DAY		((second/SECINDAY))
#define		HOUR		(((second-DAY*SECINDAY)/3600))
#define		MINUTE		(((second-DAY*SECINDAY-HOUR*3600)/60))
#define		SECOND		(((second-DAY*SECINDAY-HOUR*3600-MINUTE*60)))
#define		MAXEVENT	12345
time_t		_sec,second;
int		i,month,year,next_option,one_line,colored_day[32],show_events;
char		*program_name;
const char*const short_options="ha:A:le";
const struct	option long_options[]={
		{"help",	0,0,'h'},
		{"add-second",	1,0,'a'},
		{"add-day",	1,0,'A'},
		{"line",	0,0,'l'},
		{"events",	0,0,'e'},
		{NULL,		0,0, 0 }};
struct		event{int day;char *desc;};
const int	event_count[12]={3,4,3, 3,1,5, 3,2,3, 1,4,3};
const struct	event	events[12][10]={
/*FARVARDIN*/	{{1,	"NORUZ EVE"},
		 {12,	"JOMHURI ESLAMI"},
		 {25,	"ATTAR NEISHABURI"}},
/*ORDIBEHESHT*/	{{1,	"SA'DI"},
		 {3,	"SHEIKH BAHAYI"},
		 {25,	"FERDOSI"},
		 {28,	"KHAYYAM"}},
/*KHORDAD*/	{{1,	"MOLLASADRA"},
		 {14,	"REHLATE EMAM KHOMEINI"},
		 {15,	"GHIAM 15 KHORDAD"}},
/*TIR*/		{{4,	"TAVALLOD REZA"},
		 {14,	"GHALAM"},
		 {22,	"KHARAZMI"}},
/*MORDAD*/	{{8,	"SHEIKH SHAHABEDDIN SOHREVARDI"}},
/*SHAHRIVAR*/	{{1,	"ABU ALI SINA"},
		 {5,	"ZAKARIA RAZI"},
		 {13,	"ABU REIHAN BIRUNI"},
		 {17,	"GHIAM 17 SHAHRIVAR"},
		 {27,	"SHAHRIAR"}},
/*MEHR*/	{{16,	"KUDAK"},
		 {20,	"HAFEZ"},
		 {29,	"KUHNAVARDI"}},
/*ABAN*/	{{13,	"DANESHAMUZ"},
		 {24,	"KETAB"}},
/*AZAR*/	{{16,	"DANESHJU"},
		 {25,	"PAZHUHESH"},
		 {30,	"IALDA"}},
/*DEI*/		{{13,	"SHAHADAT SARDAR HAJ GHASEM SOLEIMANI"}},
/*BAHMAN*/	{{1,	"FERDOSI"},
		 {12,	"BAZGASHT EMAM KHOMEINI BE IRAN"},
		 {22,	"PIRUZI ENGHELAB ESLAMI"},
		 {27,	"TAVALLOD MOHAMMAD"}},
/*ESFAND*/	{{5,	"KHAJE NASIREDDIN TUSI"},
		 {15,	"DERAKHTKARI"},
		 {29,	"SAN'AT NAFT MELLI"}}};
char		*DAY_NAME[]={	"SHANBE","1SHANBE","2SHANBE","3SHANBE",
				"4SHANBE","5SHANBE","JOM'E"};
char		*MONTH_NAME[]={	"FARVARDIN","ORDIBEHESHT","KHORDAD",
       				"TIR","MORDAD","SHAHRIVAR",
       				"MEHR","ABAN","AZAR",
       				"DEI","BAHMAN","ESFAND"};
char		*SEASON_COLOR[]={"\033[1;32m","\033[1;33m",
				"\033[1;30m","\033[1;34m"};
const char 	*NOCOLOR=	"\033[0m";
const char 	*COLORED=	"\033[1;7m";
int isleapyear(int);
int print_month(int,int,int);
void print_usage(FILE*,int);
int main(int argc,char *argv[]){
	program_name=argv[0];
	do{
		next_option=getopt_long(argc,argv,short_options,long_options,0);
		switch(next_option){
			case 'h':print_usage(stdout,0);
			case '?':print_usage(stderr,1);
			case 'a':i=atoi(optarg);break;
			case 'A':i+=atoi(optarg)*SECINDAY;break;
			case 'l':one_line=1;break;
			case 'e':show_events=1;break;
			case  -1:break;
			default:abort();
		}
	}while(1+next_option);
	time(&_sec);
	_sec=second=_sec+i+IRANTIMEZONE+EPOCHREMSEC;	//  _sec := seconds since the beginning of 1348
	for(year=EPOCHYEAR;second>=(365+isleapyear(year))*SECINDAY;)
		second-=(365+isleapyear(year++))*SECINDAY;
	for(;month<5&&second>31*SECINDAY;month++)second-=31*SECINDAY;
	if(month>4&&second>=30*SECINDAY)second-=DAYLIGHTSAVE;
	if(month>4&&second>=31*SECINDAY)month++,second-=31*SECINDAY;
	for(;month>5&&second>30*SECINDAY;month++)second-=30*SECINDAY;
	if(one_line)return printf("%i %s %d %s -- %.2d:%.2d:%.2d\n",year,MONTH_NAME[month],DAY+1,DAY_NAME[(_sec/SECINDAY-1)%7],HOUR,MINUTE,SECOND),fflush(0);
	colored_day[DAY+1]=1;
	if(show_events)for(i=0;i<event_count[month];i++)colored_day[events[month][i].day]=1;
	print_month(month,year,(_sec/SECINDAY-DAY-1)%7);	//  3rd arg: 1st day of the month in the week: 0..6
	if(show_events)
		for(printf("\n\n%2i: TODAY\n",DAY+1),i=0;i<event_count[month];i++)
			printf("%2i: %s%c",events[month][i].day,events[month][i].desc,"\n "[i+1==event_count[month]]);
	return puts(""),0;
}
int isleapyear(int y){
	if(y==1214||y==1218||y==1222||y==1226||y==1230||y==1234||y==1238||y==1247||y==1251||y==1255||y==1259||y==1263||y==1267||y==1271
	 ||y==1280||y==1284||y==1288||y==1292||y==1296||y==1300||y==1304||y==1313||y==1317||y==1321||y==1325||y==1329||y==1333||y==1337
	 ||y==1346||y==1350||y==1354||y==1358||y==1362||y==1366||y==1370||y==1379||y==1383||y==1387||y==1391||y==1395||y==1399||y==1403
	 ||y==1412||y==1416||y==1420||y==1424||y==1428||y==1432||y==1436||y==1445||y==1449||y==1453||y==1457||y==1461||y==1465||y==1469
	 ||y==1478||y==1482||y==1486||y==1490||y==1494||y==1498
	 ||y==1210||y==1243||y==1276||y==1309||y==1342||y==1375||y==1408||y==1441||y==1474)
		return 1;
	return 0;
}
int print_month(int month,int year,int begin_week){
	int i,month_length=30;
	for(i=0;i<(15-strlen(MONTH_NAME[month]))/2;i++)printf(" ");
	printf("%s%s%s %d\n",SEASON_COLOR[month/3],MONTH_NAME[month],NOCOLOR,year);
	puts("SN 1S 2S 3S 4S 5S JM");
	for(i=0;i<begin_week;i++)printf("   ");
	if(month<6)month_length=31;
	if(month==11&&!isleapyear(year))month_length=29;
	for(i=1;i<=month_length;i++)
		printf("%s%s%s%s%d%s",i-1&&(i-1+begin_week)%7==0?"\n":i-1?" ":"",colored_day[i]?COLORED:"",
			colored_day[i]?SEASON_COLOR[month/3]:"",i<10?" ":"",i,NOCOLOR);
}
void print_usage(FILE *stream,int exit_code){
		fprintf(stream,"\nUsage:");
		fprintf(stream,"  %s [option]\n",program_name);
		fprintf(stream,"\nDisplay PERSIAN calendar.  (1206..1498)\n");
		fprintf(stream,"\noption:\n");
		fprintf(stream,"  -a NUM, --add-second\t\tadd NUM seconds to current date\n");
		fprintf(stream,"  -A NUM, --add-day\t\tadd NUM days to current date\n");
		fprintf(stream,"  -e, --events\t\t\tshow events of month\n");
		fprintf(stream,"  -l, --line\t\t\tprint output in one line\n");
		fprintf(stream,"  -h, --help\t\t\tdisplay this help and exit\n");
		fprintf(stream,"\n");
		exit(exit_code);
}
