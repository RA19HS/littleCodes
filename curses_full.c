#include<stdlib.h>
#include<curses.h>
#define F(I,B) for(I=0;I<B;I++)
int i,x,y;
int main(){
	srand(77777);
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr,FALSE);
	keypad(stdscr,TRUE);
	F(i,1e4){
		F(x,40)F(y,20)
			move(y,x),addch(rand()%64+64);
		refresh();
	}
	endwin();
	return 0;
}
