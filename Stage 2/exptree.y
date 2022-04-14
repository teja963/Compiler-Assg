%{
	#include<stdio.h>
	#include<stdlib.h>
	#include"exptree.c"
	#include"codeGen.c"
	#include"init_code.c"
	
	int yylex(void);
	extern FILE *yyin;
	FILE *fp;
	FILE *targetFile;
%}

%union{
	struct node* nptr; //for changing the type we r using this for yylval
}


%token START READ WRITE NUM PLUS MINUS MUL DIV END ASSGN ID FUN
%left PLUS MINUS
%left MUL DIV

%type <nptr> NUM ID START END READ WRITE PLUS MINUS DIV ASSGN//all the non-terminals used in the grammar need to write here
%type <nptr> program Slist Stmt InputStmt OutputStmt AssgStmt exp

%%
program : FUN '('  ')' '{' Slist '}' {       //there is only one funnction that returns an integer
					codeGen($5);
			}
		
exp : exp PLUS exp	{$$ = createTree(1, 0, NODE_PLUS, NULL, $1, $3);}	
	| exp MINUS exp {$$ = createTree(1, 0, NODE_MINUS, NULL, $1, $3);}
	| exp DIV exp {$$ = createTree(1, 0, NODE_MUL, NULL, $1, $3);}
	| exp MUL exp {$$ = createTree(1, 0, NODE_DIV, NULL, $1, $3);}
	| '(' exp ')' {$$ = $2;}
	| NUM {$$ = $1;}
	| ID {$$ = $1;}
	;
	
Slist : Slist Stmt {$$ = createTree(1, 0, NODE_CONNECT, NULL, $1, $2);}
      | Stmt {$$ = $1;}
      ;
      
Stmt : InputStmt {$$ = $1;}
     | OutputStmt {$$ = $1;}
     | AssgStmt {$$ = $1;}
     
InputStmt : READ '(' ID ')' ';' {$$ = createTree(1, 0, NODE_READ, NULL, $3, NULL);}
          ;
          
OutputStmt : WRITE '(' exp ')' ';' {$$ = createTree(1, 0, NODE_WRITE, NULL, $3, NULL);}
           ;
           
AssgStmt : ID ASSGN exp ';' {$$ = createTree(1, 0, NODE_ASSGN, NULL, $1, $3);}
         ;
	
%%



int yyerror(char const* s)
{
	printf("yyerror %s", s);
}

int main(int argc, char *argv[]){
	if (argc < 2){
        printf("Enter filename Properly\n");
        exit(1);
    } 
    else{
        fp = fopen(argv[1], "r");
        if (!fp){
            printf("Invalid input file selected\n");
            exit(1);
        }
        else{
            yyin = fp;
        }
    }
	yyparse();
	return 0;
}
