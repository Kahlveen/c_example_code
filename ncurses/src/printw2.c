#include <ncurses.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char mesg[] = "Santa tell me if you're really there";
	int row, col;

	initscr();
	int a = 10, b = 20, c = 30;

	while(1){
		getmaxyx(stdscr,row,col);
		//always rows then col
		mvprintw(15,col/6, "%s","Statistics 1");	//prints to centre of screen
		mvprintw(16,col/6, "%s","Statistics 2");	//prints to centre of screen
		mvprintw(17,col/6, "%s","Statistics 3");	//prints to centre of screen
		mvprintw(15,4*col/6, "%d",a);	//prints to centre of screen
		mvprintw(16,4*col/6, "%d",b);	//prints to centre of screen
		mvprintw(17,4*col/6, "%d",c);	//prints to centre of screen
		a++;
		b++;
		c++;

		refresh();		//Dump to screen
		clear();			//clear the screen
		sleep(1);
	}
	endwin();
	return 0;
}
