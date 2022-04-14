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
	    		   		
	    case NODE_ASSG: number = 4096 + t->left->varname[0] - 'a';
	    		   
	 }
}

