#include<curses.h>
int i,x,y;
int main(){
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr,FALSE);
	keypad(stdscr,TRUE);
	for(;;){
		i=getch();
		switch(i){
			case KEY_RIGHT:	if(x<19) x++; break;
			case KEY_UP:	if(y> 0) y--; break;
			case KEY_LEFT:	if(x> 0) x--; break;
			case KEY_DOWN:	if(y<19) y++; break;
			case 'q':	goto abc;
		}
		move(y,x);
		refresh();
	}
abc:	endwin();
	return 0;
}
