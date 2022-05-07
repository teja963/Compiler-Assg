#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int stackOffset = 4096;
extern FILE *targetFile;
struct symbol_table{
	char *name;
	int type;
	int size;
	int binding;
	struct symbol_table *next;
};

struct symbol_table *GSTHead = NULL, *GSTTail = NULL;	//Global Symbol Table

struct symbol_table *lookup_symbol(char *name) {
    struct symbol_table *temp;

	temp = GSTHead;
	
	while (temp != NULL)
	{

		if (strcmp(name, temp->name) == 0)
			return temp;
			

		temp = temp->next;
	}
	return NULL;
}


struct symbol_table *install_variable(char *name, int type, int size) {
    
	if (lookup_symbol(name) != NULL) {
		return lookup_symbol(name);
        // yyerror("variable redeclaration", 1);
    }


    struct symbol_table *temp;
	temp = (struct symbol_table *)malloc(sizeof(struct symbol_table));
	temp->name = name;
	temp->type = type;
    temp->size = size;
	temp->binding = ++stackOffset;
	temp->next=NULL;
	if (GSTHead == NULL)
	{
		GSTHead = temp;
		GSTTail = temp;
	}
	else
	{
		(GSTTail)->next = temp;
		GSTTail = (GSTTail)->next;
	}
	//fprintf(targetFile, "PUSH R0\n");
	return temp;
}

int count_variables(){
	int count = 0;
    struct symbol_table *temp;

	temp = GSTHead;
	
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	
	return count;
	
}


