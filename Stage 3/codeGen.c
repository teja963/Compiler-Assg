int reg_number = -1;
extern FILE *targetFile;
int getReg(){
	if(reg_number < 20){
		reg_number += 1;
		return reg_number;	
	}
	printf("Registers are beyond the scope\n");
	exit(1);
}

int freeReg(){
	if(reg_number >= 0){
		reg_number -= 1;
		return reg_number;	
	}
}

int codeGen(struct node* t){
    int reg_1, reg_2, reg_3, number, status = 0;
	if(t == NULL){
		return -1;
	}
	else if(t->nodetype == NODE_CONNECT){
		codeGen(t->left);
		codeGen(t->right);
		
	}
	switch(t->nodetype){
	    case NODE_NUM: reg_1 = getReg();
					   fprintf(targetFile, "MOV R%d, %d\n", reg_1, t->val);
					   return reg_1;
		case NODE_ID: reg_1 = getReg();
		              number = 4096 + t->varname[0] - 'a';
		              fprintf(targetFile, "MOV R%d, [%d]\n", reg_1, number);
		              return reg_1;
		case NODE_PLUS: reg_1 = codeGen(t->left);
						reg_2 = codeGen(t->right);
						fprintf(targetFile, "ADD R%d, R%d\n", reg_1, reg_2);
				   		freeReg();
				   		return reg_1;
				   
	    case NODE_MINUS: reg_1 = codeGen(t->left);
	    				 reg_2 = codeGen(t->right);
	    				 fprintf(targetFile, "SUB R%d, R%d\n", reg_1, reg_2);
	    		   		 freeReg();
	    		   		 return reg_1;
	    		   
	    case NODE_MUL: reg_1 = codeGen(t->left);
	    			   reg_2 = codeGen(t->right);
	    			   fprintf(targetFile, "MUL R%d, R%d\n", reg_1, reg_2);
				       freeReg();
				       return reg_1;
				   
	    case NODE_DIV:  reg_1 = codeGen(t->left);
	    			    reg_2 = codeGen(t->right);
	    				fprintf(targetFile, "DIV R%d, R%d\n", reg_1, reg_2);
	    		   		freeReg();
	    		   		return reg_1; 
	    		   		 		   		
	    case NODE_ASSGN: number = 4096 + t->left->varname[0] - 'a';
	                    reg_2 = codeGen(t->right);
	                    fprintf(targetFile, "MOV [%d], R%d\n", number, reg_2);
	                    freeReg();
	                    return 0;
	                    
	    case NODE_WRITE: for(int i = 0; i <= reg_number; i++)
	    					fprintf(targetFile, "PUSH R%d\n", i);
	    				 status = reg_number;
	    				 
	    				 fprintf(targetFile, "MOV R0,\"Write\"\n");
	    				 fprintf(targetFile, "PUSH R0\n"); //function code
	    				 fprintf(targetFile, "MOV R0,-2\n");
	    				 fprintf(targetFile, "PUSH R0\n"); //Arguement 1
	    				 
	    				 reg_1 = codeGen(t->left);
	    				 fprintf(targetFile, "PUSH R%d\n", reg_1);
	    				 freeReg();
	    				 fprintf(targetFile, "ADD SP,2\n");
	    				 fprintf(targetFile, "CALL 0\n");
	    				 fprintf(targetFile, "SUB SP,5\n");
	    				 
	    				 for(int i = status; i >= 0; i--)
	    				 	fprintf(targetFile, "POP R%d\n", i);
	    				 reg_number = status;
	    				 break;
	    				 
	    case NODE_READ: number = 4096 + t->left->varname[0] - 'a';
	    				for(int i = 0; i <= reg_number; i++)
	    					fprintf(targetFile, "PUSH R%d\n", i);
	    				status = reg_number;
	    				
	    				fprintf(targetFile, "MOV R0,\"Read\"\n");
	    				fprintf(targetFile, "PUSH R0\n"); //function code
	    				fprintf(targetFile, "MOV R0,-1\n");
	    				fprintf(targetFile, "PUSH R0\n"); //argument 1
	    				fprintf(targetFile, "MOV R0,%d\n", number);
	    				fprintf(targetFile, "PUSH R0\n"); //argument 1
	    				fprintf(targetFile, "ADD SP,2\n");
	    				fprintf(targetFile, "CALL 0\n");
	    				fprintf(targetFile, "SUB SP,5\n");
	    				
	    				for(int i = status; i >= 0; i--)
	    					fprintf(targetFile, "POP R%d\n", i);
	    				reg_number = status;
	    				break; 
	    		   
	 }
}

