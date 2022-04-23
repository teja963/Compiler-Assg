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
		yylval.nptr = createTree(TYPE_INT ,numbers, NODE_NUM, NULL, NULL, NULL, NULL);
		return NUM; 
		}

"read" {return READ;}
"write" {return WRITE;}
"If"        {return IF;}
"then"      {return THEN;}
"else"      {return ELSE;}
"endif"     {return ENDIF;}
"while"     {return WHILE;}
"do"        {return DO;}
"endwhile"  {return ENDWHILE;}
"break"     {return BREAK;}
"continue"  {return CONT;}
"=="        {return EQ;}
"!="        {return NEQ;}
"<="        {return LE;}
">="        {return GE;}
"<"         {return LT;}
">"         {return GT;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"=" {return ASSGN;}
[ \t\n] {}
"FUN" {return FUN;}
[{}();] {return *yytext;}  //read again from the user
[a-zA-Z]([a-zA-Z]|[0-9])* {
		variable = (char*)malloc(sizeof(yytext));
		strcpy(variable, yytext);
		yylval.nptr = createTree(TYPE_INT, 0, NODE_ID, variable, NULL, NULL, NULL);
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


