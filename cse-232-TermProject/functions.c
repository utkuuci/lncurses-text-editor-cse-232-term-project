#include"myeditor_header.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ncurses.h>

void edit(char *filename){
    FILE *fp;
    int index = 0, z = 0;
    char string[40];

	if (fopen(filename, "r") != NULL){ // opening the file if its exists and copy lines to textbuffer.
		fp = fopen(filename, "r");
        while(!feof(fp)){
        fgets(string, 40, fp);
        strcpy(textbuffer[index].statement, string);
        index++;
        size++;
        }
		fclose(fp);
    }
	
	if(index >= 1){ // Adding new line to last element for visibility purpose
        while(textbuffer[index - 1].statement[z] != '\0'){
            z++;
        }
		textbuffer[index - 1].statement[z] = '\n';
		textbuffer[index - 1].statement[z + 1] = '\0';
    }
	
    for(int i = 0; i < 24; i++) // initializing index
        textbuffer[i].next = i+1;
    textbuffer[24].next = -1;
    free_head = index;
    inuse_head = 0;
    if(free_head == 0) inuse_head = -1;
    if(size == 25) free_head = -1;
}

void insert(char *stat){
	
	int size_saver = size; // just for printing there are total 25 lines...
	
	if(inuse_head == -1){
		for(int i = 0; i < 24; i++) // initializing index
			textbuffer[i].next = i+1;
		textbuffer[24].next = -1;
		inuse_head = 0;
		free_head = 0; 
	}

    if(inuse_head == free_head){ // adding an empty file
        strcpy(textbuffer[free_head].statement, stat);
        free_head = textbuffer[free_head].next;
		size++;
    }

    else if(free_head <= 24 && free_head >= 0){
		
		int temp_choosen = inuse_head;
		int temp_last = inuse_head;
		int temp_freenext = textbuffer[free_head].next;
	
        for(int i = inuse_head; i < inuse_head + y; i++){ // index of chosen element
            temp_choosen = textbuffer[temp_choosen].next;
        }
		
        while(true){// index of last element.
            temp_last = textbuffer[temp_last].next;
            if(textbuffer[temp_last].next == free_head) break;
        }
		
        strcpy(textbuffer[free_head].statement, stat);
		
		if(textbuffer[temp_choosen].next == free_head){// for adding last element 
			free_head = temp_freenext;
		}
		
		else if(temp_choosen == free_head){// for adding last element using empty side
			free_head = temp_freenext;
		}
		
		else{ // for adding elements between
			textbuffer[free_head].next = textbuffer[temp_choosen].next;
			textbuffer[temp_choosen].next = free_head;
			free_head = temp_freenext;
			textbuffer[temp_last].next = free_head;
		}
		size++;
    }
	
	
	int temp_printer = inuse_head;
	while(inuse_head != -1){ // printing all to the screen using index pointers
		if(temp_printer == inuse_head) printw("%s", textbuffer[temp_printer].statement);
		if(textbuffer[temp_printer].next == free_head) break;
		printw("%s", textbuffer[textbuffer[temp_printer].next].statement);
		temp_printer = textbuffer[temp_printer].next;
	}
	
	if(size_saver == size) printw("\nThere are total 25 lines you can't add more.");
}

void Delete(){
	
	if(size == 0){
        printw("There is nothing to delete!");
    }
	
	else if(size == 1){
		free_head = 0;
		inuse_head = -1;
		size--;
	}
	
    else{
		int temp_choosen = inuse_head;
		int temp_last = inuse_head;
		int temp_freenext = textbuffer[free_head].next;
		int temp_choosenbefore = inuse_head;
		
		for(int i = inuse_head; i < inuse_head + y; i++){//index of chosen 
			temp_choosen = textbuffer[temp_choosen].next;
		}
		
		while(true){// index of last element.
			if(textbuffer[temp_last].next == free_head) break;
			temp_last = textbuffer[temp_last].next;
		}
		
		for(int i = inuse_head; i < inuse_head + y - 1; i++){// index of the element before choosen element
				temp_choosenbefore = textbuffer[temp_choosenbefore].next;
		}
		
		if((temp_choosen != inuse_head) && (textbuffer[temp_choosen].next != free_head)){// deleting lines between
			textbuffer[temp_choosenbefore].next = textbuffer[temp_choosen].next;
			textbuffer[temp_choosen].next = free_head;
			free_head = temp_choosen;
			textbuffer[temp_last].next = free_head;
		}
		
		else if(textbuffer[temp_choosen].next == free_head){//deleting the last line
			free_head = temp_choosen;
		}
		
		else{//deleting the inuse_head
			inuse_head = textbuffer[inuse_head].next;
			textbuffer[temp_choosen].next = free_head;
			free_head = temp_choosen;
			textbuffer[temp_last].next = free_head;
		}
		size--;
    }
	
	int temp_printer = inuse_head;
	while(inuse_head != -1){ // printing all to the screen using index pointers
		if(temp_printer == inuse_head) printw("%s", textbuffer[temp_printer].statement);
		if(textbuffer[temp_printer].next == free_head) break;
		printw("%s", textbuffer[textbuffer[temp_printer].next].statement);
		temp_printer = textbuffer[temp_printer].next;
	}
}

void save(){
	int temp = inuse_head;
    FILE *saveFP = fopen("save.txt", "w+");
    while(inuse_head != -1){// saving all to the txt file using index pointers
		if(temp == inuse_head) fputs(textbuffer[temp].statement, saveFP);
		if(textbuffer[temp].next == free_head) break;
        fputs(textbuffer[textbuffer[temp].next].statement, saveFP);
		temp = textbuffer[temp].next;
    }
	fclose(saveFP);
}