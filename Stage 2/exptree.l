%{
	#include<stdio.h>
	#include<stdlib.h>
	#include"exptree.h"
	#include"y.tab.h"
	
	int numbers;
	char *variable;
%}

%%

[0-9]+ {
		numbers = atoi(yytext); 
		yylval.nptr = createTree(0 ,number, NODE_NUM, NULL, NULL);
		return NUM; 
		}
"begin" {return START;}
"end" {return END;}
"read" {return READ;}
"write" {return WRITE;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"=" {return ASSGN;}
[ \t\n] {}
[();] {return *yytext;}  //read again from the user
[a-z] {
		variable = (char*)malloc(sizeof(yytext));
		strcpy(variable, yytext);
		yylval.nptr = createTree(1, 0, NODE_ID, variable, NULL, NULL);
		return ID;
	  }
. {
	yyerror("Characters Mismatched\n"); 
	exit(1);
   }
   
%%

int yywrap(void){
	return 1;
}

