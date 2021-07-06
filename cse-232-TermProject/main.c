#include"myeditor_header.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>

int main(int argc, char *argv[]){
    initscr(); 
    raw();
    noecho();
    char ch;
    char input[40];
    int k = 0;
	edit(argv[1]);
    refresh();
    y = 0, x = 0;

    for(int i = 0; i < size; i++){
        printw("%s",textbuffer[i].statement);
    }
    move(y,x);
    while(true){
        ch = getch();
        if(ch == 'W' || ch == 'w'){ //line up
            move(--y,x);
            refresh();
        }
        else if(ch == 'Z' || ch == 'z'){// line down
            move(++y,x);
            refresh();
        }
		else if(ch == 'I' || ch == 'i'){//- I (insert): Inserts a line in text buffer
			move(size + 1,x);
			refresh();
			printw("Give me string to insert: ");
			echo();
			while(ch != 10){
				ch = getch();
				input[k] = ch;
				k++;
			}
			input[k] = '\0';
			noecho();
			clear();
			refresh();
			insert(input);
			k = 0;
			move(++y, x);
			refresh();
        }
        else if(ch == 'D' || ch == 'd'){// - D (delete): Deletes a line
			clear();
			refresh();
			Delete();
			move(y, x);
			refresh();
        }
        else if(ch == 's' || ch == 'S'){//{- S (save): Saves the file 
            save();
        }
        else if(ch == 'x' || ch == 'X'){ // break the while loop and exit
            break;
        }
        
    }
    endwin();
    return 0;
}