%{
	#include<stdio.h>
	#include<stdlib.h>
	#include"exptree.c"
	
	int yylex(void);
%}

%union{
	struct node* number; //for changing the type we r using this for yylval
}

%type <number> exp NUM program END//all the non-terminals used in the grammar need to write here
%token NUM PLUS MINUS MUL DIV END
%left PLUS MINUS
%left MUL DIV


%%
program : exp END {
						$$ = $2;
						printf("Final_result: %d\n", evaluate($1));
						exit(1);
					}
		;
		
exp : exp PLUS exp	{$$ = makeOperatorsNode('+', $1, $3);}	
	| exp MINUS exp {$$ = makeOperatorsNode('-', $1, $3);}
	| exp DIV exp {$$ = makeOperatorsNode('/', $1, $3);}
	| exp MUL exp {$$ = makeOperatorsNode('*', $1, $3);}
	| '(' exp ')' {$$ = $2;}
	| NUM {$$ = $<number>1;}
	;
	
%%

int yyerror(char const* s){
	printf("yyerror %s", s);
}

int main(void){
	yyparse();
	return 0;
}
