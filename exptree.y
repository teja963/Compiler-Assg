%{
	#include<stdio.h>
	#include<stdlib.h>
	#include"exptree.h"
	#include"exptree.c"
	
	int yylex(void);
%}

%union{
	struct node* number; //for changing the type we r using this for yylval
}

%type number //all the non-terminals used in the grammar need to write here


%%
	
%%

int yyerror(char const* s){
	printf("yyerror %s", s);
}

int main(void){
	yyparse();
	return 0;
}
