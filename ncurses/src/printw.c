#include <ncurses.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char mesg[] = "Santa tell me if you're really there";
	int row, col;

	initscr();

	while(1){
		getmaxyx(stdscr,row,col);
		//always rows then col
		mvprintw(row/2,(col - strlen(mesg))/2, "%s",mesg);	//prints to centre of screen

		mvprintw(row-2,0,"THis screen has %d rows, %d cols\n",row,col);
		printw("Try resizing window and rerun program");
		refresh();		//Dump to screen
		clear();			//clear the screen
		sleep(1);
	}
	endwin();
	return 0;
}
