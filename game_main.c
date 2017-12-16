/* file : game_main.c
 * description : 메인 기능 선택 */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define CHECK addch('o');
int main(void){
	
	char  menu;
	initscr();
	crmode();
	noecho();
	while(1){
		clear();
		move(5,4);
		addstr("ooo");
		move(6,4);
		CHECK
		move(6,7);
		CHECK
		move(7,4);
		addstr("ooo");
		move(8,4);
		CHECK
		move(8,7);
		CHECK
		move(9,4);
		CHECK
		move(9,8);
		CHECK
		
		// r 종료
	
		move(5,10);
		CHECK
		move(5,15);
		CHECK
		move(6,10);
		CHECK
		move(6,15);
		CHECK
		move(7,10);
		CHECK
		move(7,15);
		CHECK
		move(8,10);
		CHECK
		move(8,15);
		CHECK
		move(9,11);
		addstr("oooo");
		// u 

		move(5,17);
		CHECK
		move(6,17);
		CHECK
		move(7,17);
		CHECK
		move(8,17);
		CHECK	
		move(9,17);
		CHECK
		move(8,20);
		CHECK
		move(7,19);
		CHECK
		move(6,18);
		CHECK
		move(5,21);
		CHECK
		move(6,21);
		CHECK
		move(7,21);
		CHECK
		move(8,21);
		CHECK
		move(9,21);
		CHECK
		//n
		
		move(5,33);
		CHECK
		move(6,32);
		CHECK
		move(6,34);
		CHECK
		move(7,31);
		addstr("ooooo");
		move(8,30);
		CHECK
		move(8,36);
		CHECK
		move(9,29);
		CHECK
		move(9,37);
		CHECK
		
		//a
		//
	
		move(5,41);
		CHECK
		CHECK
		CHECK
		move(6,40);
		CHECK
		move(7,39);
		CHECK
		move(8,39);
		CHECK
		move(9,40);
		CHECK
		CHECK
		CHECK
		CHECK
		move(8,44);
		CHECK
		move(7,43);
		CHECK
		move(7,42);
		CHECK
		//g

		move(5,50);
		CHECK
		move(6,49);
		CHECK
		move(6,51);
		CHECK
		move(7,48);
		addstr("ooooo");
		move(8,47);
		CHECK
		move(8,53);
		CHECK
		move(9,46);
		CHECK
		move(9,54);
		CHECK
		//a
		
		move(5,57);
		addstr("ooo");
		move(6,58);
		CHECK
		move(7,58);
		CHECK
		move(8,58);
		CHECK
		move(9,57);
		addstr("ooo");
		//i
		//


		move(5,62);
		CHECK
		move(6,62);
		CHECK
		move(7,62);
		CHECK
		move(8,62);
		CHECK	
		move(9,62);
		CHECK
		move(8,65);
		CHECK
		move(7,64);
		CHECK
		move(6,63);
		CHECK
		move(5,66);
		CHECK
		move(6,66);
		CHECK
		move(7,66);
		CHECK
		move(8,66);
		CHECK
		move(9,66);
		CHECK


			
			
		move(13,27);
		addstr("1 : Game Start");
		move(15,27);
		addstr("2 : Select Mode");
		move(17,27);
		addstr("3 : See Rank");
		move(19,27);
		addstr("4 : Help");
		move(21,27);
		addstr("5 : Exit");
		refresh();
		move(16,10);
		menu=getchar();
		
		switch(menu){
			case '1' : game_start();
				   break;
			case '5' : endwin();
				   exit(1);
		}

	}
	return 0;
}	
