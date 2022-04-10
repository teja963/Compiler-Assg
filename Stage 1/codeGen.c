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
	if(t == NULL){
		return -1;
	}
	else if(t->op == NULL){
		int reg_1 = getReg();
		fprintf(targetFile, "MOV R%d, %d\n", reg_1, t->val);
		return reg_1;
	}
	int reg_1 = codeGen(t->left);
	int reg_2 = codeGen(t->right);
	switch(*(t->op)){
		case '+' : fprintf(targetFile, "ADD R%d, R%d\n", reg_1, reg_2);
				   freeReg();
				   return reg_1;
				   
	    case '-' : fprintf(targetFile, "SUB R%d, R%d\n", reg_1, reg_2);
	    		   freeReg();
	    		   return reg_1;
	    		   
	    case '*' : fprintf(targetFile, "MUL R%d, R%d\n", reg_1, reg_2);
				   freeReg();
				   return reg_1;
				   
	    case '/' : fprintf(targetFile, "DIV R%d, R%d\n", reg_1, reg_2);
	    		   freeReg();
	    		   return reg_1;  
	    		   
	 }
	}

