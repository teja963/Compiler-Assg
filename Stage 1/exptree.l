%{
	#include<stdio.h>
	#include<stdlib.h>
	#include"exptree.h"
	#include"y.tab.h"
	
	int numbers;
%}

%%

[0-9]+ {numbers = atoi(yytext); yylval.number = makeLeafNode(numbers); return NUM; }
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
[ /t] {}
[()] {return *yytext;}  //read again from the user
[\n] {return END;}
. {yyerror("Characters Mismatched\n"); exit(1);}

%%

int yywrap(void){
	return 1;
}


