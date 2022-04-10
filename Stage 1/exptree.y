%{
	#include<stdio.h>
	#include<stdlib.h>
	#include"exptree.c"
	#include"codeGen.c"
	
	int yylex(void);
	extern FILE *yyin;
	FILE *fp;
	FILE *targetFile;
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
						codeGen($1);
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

int main(int argc, char *argv[]){
	if (argc < 2) {
        printf("Enter filename Properly\n");
        exit(1);
    } else {
        targetFile = fopen("target_file.xsm", "w");
        fprintf(targetFile, "0\n2056\n0\n0\n0\n0\n0\n0\n");
        fp = fopen(argv[1], "r");
        if (!fp) {
            printf("Invalid input file selected\n");
            exit(1);
        } else {
            yyin = fp;
        }
    }
	yyparse();
	return 0;
}
