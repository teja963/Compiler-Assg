%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include"symbol_table.c"
	#include"exptree.c"
	#include"codeGen.c"
	#include"typecheck.c"
	
	int yylex(void);
	extern FILE *yyin;
	FILE *fp;
	FILE *targetFile;
%}

%union{
	struct node* nptr; //for changing the type we r using this for yylval
}


%token START READ WRITE NUM PLUS MINUS MUL DIV END ASSGN ID FUN
%token IF THEN ELSE ENDIF WHILE DO ENDWHILE EQ NEQ LE GE LT GT
%token BREAK CONT
%left PLUS MINUS
%left MUL DIV
%right ASSGN
%nonassoc LT GT LE GE
%right EQ NEQ

//%type <nptr> NUM ID START END READ WRITE PLUS MINUS DIV ASSGN//all the non-terminals used in the grammar need to write here
%type <nptr> program Slist Stmt InputStmt OutputStmt AssgStmt exp IfStmt WhileStmt
//%type <nptr> IF THEN ELSE ENDIF WHILE DO ENDWHILE EQ NEQ LE GE LT GT BREAK CONT
%type <nptr> BrkStmt ContStmt 

%%
program : FUN '('  ')' '{' Slist '}' {       //there is only one funnction that returns an integer
					int i, var_count;
					var_count = count_variables();
					for(i=0; i<var_count; i++) {
						fprintf(targetFile, "PUSH R0\n");
					}
		
					codeGen($5);
					fprintf(targetFile, "INT 10\n");
			}
		
exp : exp PLUS exp	{
						typecheck($1->type, $3->type, 'a');
						$$ = createTree(TYPE_INT, 0, NODE_PLUS, NULL, $1, $3, NULL);
					}	
	| exp MINUS exp {
						typecheck($1->type, $3->type, 'a');
						$$ = createTree(TYPE_INT, 0, NODE_MINUS, NULL, $1, $3, NULL);
					}
	| exp DIV exp {
						typecheck($1->type, $3->type, 'a');
						$$ = createTree(1, 0, NODE_MUL, NULL, $1, $3, NULL);
				  }
	| exp MUL exp {		
	                    typecheck($1->type, $3->type, 'a');
						$$ = createTree(1, 0, NODE_DIV, NULL, $1, $3, NULL);
				   }
	| exp LT exp {
						typecheck($1->type, $3->type, 'b');
						$$ = createTree(TYPE_BOOL, 0, NODE_LT, NULL, $1, $3, NULL);
				 }
	| exp GT exp {
						typecheck($1->type, $3->type, 'b');
						$$ = createTree(TYPE_BOOL, 0, NODE_GT, NULL, $1, $3, NULL);
				 }
	| exp LE exp {
						typecheck($1->type, $3->type, 'b');
						$$ = createTree(TYPE_BOOL, 0, NODE_LE, NULL, $1, $3, NULL);
				 }
	| exp GE exp {
						typecheck($1->type, $3->type, 'b');
						$$ = createTree(TYPE_BOOL, 0, NODE_GE, NULL, $1, $3, NULL);
				 }
	| exp EQ exp {
						typecheck($1->type, $3->type, 'b');
						$$ = createTree(TYPE_BOOL, 0, NODE_EQ, NULL, $1, $3, NULL);
				 }
    | exp NEQ exp {
						typecheck($1->type, $3->type, 'b');
						$$ = createTree(TYPE_BOOL, 0, NODE_NEQ, NULL, $1, $3, NULL);
				 }
	| '(' exp ')' {$$ = $<nptr>2;}
	| NUM {$$ = $<nptr>1;}
	| ID {
			struct symbol_table * t = lookup_symbol($<nptr>1->varname);
			if ( t== NULL) {
				yyerror("symbol undefined");
				exit(0);
			}
			$$ = $<nptr>1;
		}
	;
	
Slist : Slist Stmt {$$ = createTree(TYPE_VOID, 0, NODE_CONNECT, NULL, $1, $2, NULL);
}
      | Stmt {$$ = $1;}
      ;
      
Stmt : InputStmt {$$ = $1;}
     | OutputStmt {$$ = $1;}
     | AssgStmt {$$ = $1;}
     | IfStmt {$$ = $1;}
     | WhileStmt {$$ = $1;}
     | BrkStmt {$$ = $1;}
     | ContStmt {$$ = $1;}
     
InputStmt : READ '(' ID ')' ';' {								
									install_variable($<nptr>3->varname, $<nptr>3->type, 1);
									$$ = createTree(TYPE_VOID, 0, NODE_READ, NULL, $<nptr>3, NULL, NULL);}
          ;
          
OutputStmt : WRITE '(' exp ')' ';' {$$ = createTree(TYPE_VOID, 0, NODE_WRITE, NULL, $3, NULL, NULL);}
           ;
           
AssgStmt : ID ASSGN exp ';' {
								typecheck($<nptr>1->type, $3->type, '=');
								install_variable($<nptr>1->varname, $<nptr>3->type, 1);
								$$ = createTree(TYPE_VOID, 0, NODE_ASSGN, NULL, $<nptr>1, $3, NULL);
							}
         ;
         
IfStmt: IF '(' exp ')' '{' Slist '}' ELSE '{' Slist '}'    {
                                                                typecheck($3->type, TYPE_BOOL, 'e');
                                                                $$ = createTree(TYPE_VOID, 0, NODE_IF_ELSE, NULL, $3, $10, $6);
                                                            }
      | IF '(' exp ')' '{' Slist '}'                 {
                                                                typecheck($3->type, TYPE_BOOL, 'i');
                                                                $$ = createTree(TYPE_VOID, 0, NODE_IF, NULL, $3, $6, NULL);
                                                            }
                                                            

WhileStmt: DO '{' Slist '}' WHILE '(' exp ')' ';'         {
                                                                typecheck($7->type, TYPE_BOOL, 'w');
               
                                                                $$ = createTree(TYPE_VOID, 0, NODE_WHILE, NULL, $3, $7, NULL);
                                             
                                                            }
BrkStmt: BREAK ';'                  {$$ = createTree(TYPE_VOID, 0, NODE_BREAK, NULL, NULL, NULL, NULL);}

ContStmt: CONT ';'                  {$$ = createTree(TYPE_VOID, 0, NODE_CONT, NULL, NULL, NULL, NULL);}
	
%%



int yyerror(char const* s)
{
	printf("yyerror %s\n", s);
}

int main(int argc, char *argv[]){
	if (argc < 2){
        printf("Enter filename Properly\n");
        exit(1);
    } 
    else{
        fp = fopen(argv[1], "r");
        targetFile = fopen("target_file.xsm", "w");
	    fprintf(targetFile, "0\n2056\n0\n0\n0\n0\n0\n0\n");
	    fprintf(targetFile, "MOV SP, 4095\n");
	    fprintf(targetFile, "MOV BP, 4096\n");
	    fprintf(targetFile, "PUSH BP\n");
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
