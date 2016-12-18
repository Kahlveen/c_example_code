#include <ncurses.h>

int main()
{
	initscr();		//init ncurses
	raw();				//disable line buffering

	//enable reading of function keys like F1, arrow keys etc
	//enable for regular screen stdscr
	keypad(stdscr,TRUE);		

	//Disable echo when using getch
	noecho();

	printw("Type any character to see it in bold!");		//write stuff to placeholder screen
	int ch = getch();

	if(ch == KEY_F(1))
		printw("F1 key pressed");		//would not get here without keypad enabled

	else
	{
		printw("Pressed key: ");
		attron(A_BOLD);
		printw("%c",ch);
		attroff(A_BOLD);
	}
	refresh();		//Print onto real screen
	getch();
	endwin();			//end ncurses
	return 0;
}
