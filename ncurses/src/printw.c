#include <ncurses.h>
#include <string.h>

int main()
{
	char mesg[] = "Santa tell me if you're really there";
	int row, col;

	initscr();
	getmaxyx(stdscr,row,col);

	//always rows then col
	mvprintw(row/2,(col - strlen(mesg))/2, "%s",mesg);	//prints to centre of screen

	mvprintw(row-2,0,"THis screen has %d rows, %d cols\n",row,col);
	printw("Try resizing window and rerun program");
	refresh();
	getch();
	endwin();
	return 0;
}
