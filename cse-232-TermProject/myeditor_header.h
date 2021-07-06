#ifndef MYEDITOR_HEADER
#define MYEDITOR_HEADER 

struct node{
	char statement[40]; // max 40 char
	int next;
}textbuffer[25];

int x, y, size;
int free_head;
int inuse_head;
void edit(char *);
void insert(char *);
void Delete();
void save();

#endif
