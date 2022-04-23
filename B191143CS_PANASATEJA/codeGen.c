int reg_number = -1, i, j, label = 0;
int while_start = -1, while_end = -1;
extern FILE *targetFile;

int getlabel(){
	label += 1;
	return label;
}

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
    int reg_1, reg_2, reg_3, label_1, label_2, number, status = 0;
    int prev_while_start, prev_while_end;
    
	if(t == NULL){
		return -1;
	}
	else if(t->nodetype == NODE_CONNECT){
		codeGen(t->left);
		codeGen(t->right);
		return -1;
		
	}
	struct symbol_table * st_entry;
	switch(t->nodetype){
	    case NODE_NUM: reg_1 = getReg();
					   fprintf(targetFile, "MOV R%d, %d\n", reg_1, t->val);
					   return reg_1;
		case NODE_ID: reg_1 = getReg();
					  st_entry = lookup_symbol(t->varname);
		              number = st_entry->binding;
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
		              
		case NODE_LT: reg_1 = codeGen(t->left);
					  reg_2 = codeGen(t->right);
					  fprintf(targetFile, "LT R%d, R%d\n", reg_1, reg_2);
					  freeReg();
					  return reg_1;
					  
		case NODE_GT: reg_1 = codeGen(t->left);
					  reg_2 = codeGen(t->right);
					  fprintf(targetFile, "GT R%d, R%d\n", reg_1, reg_2);
					  freeReg();
					  return reg_1;
					  
		case NODE_LE: reg_1 = codeGen(t->left);
					  reg_2 = codeGen(t->right);
					  fprintf(targetFile, "LE R%d, R%d\n", reg_1, reg_2);
					  freeReg();
					  return reg_1;
					  
		case NODE_GE: reg_1 = codeGen(t->left);
					  reg_2 = codeGen(t->right);
					  fprintf(targetFile, "GE R%d, R%d\n", reg_1, reg_2);
					  freeReg();
					  return reg_1;
					  
		case NODE_EQ: reg_1 = codeGen(t->left);
					  reg_2 = codeGen(t->right);
					  fprintf(targetFile, "EQ R%d, R%d\n", reg_1, reg_2);
					  freeReg();
					  return reg_1;
						
		case NODE_NEQ: reg_1 = codeGen(t->left);
					   reg_2 = codeGen(t->right);
					   fprintf(targetFile, "NE R%d, R%d\n", reg_1, reg_2);
					   freeReg();
					   return reg_1;		
	    		   		 		   		
	    case NODE_ASSGN:st_entry = lookup_symbol((t->left)->varname);
		              	number = st_entry->binding;
	                    reg_2 = codeGen(t->right);
	                    fprintf(targetFile, "MOV [%d], R%d\n", number, reg_2);
	                    freeReg();
	                    return 0;
	                    
	    case NODE_WRITE: for(i = 0; i <= reg_number; i++)
	    					fprintf(targetFile, "PUSH R%d\n", i);
	    				 status = reg_number;
	    				 
	    				 fprintf(targetFile, "MOV R0, 5\n");
	    				 fprintf(targetFile, "PUSH R0\n"); //function code
	    				 fprintf(targetFile, "MOV R0,-2\n");
	    				 fprintf(targetFile, "PUSH R0\n"); //Arguement 1
	    				 
	    				 reg_1 = codeGen(t->left);
	    				 fprintf(targetFile, "PUSH R%d\n", reg_1);
	    				 freeReg();
	    				 fprintf(targetFile, "ADD SP,2\n");
	    				 fprintf(targetFile, "INT 7\n");
	    				 fprintf(targetFile, "SUB SP,5\n");
	    				 
	    				 for(i = status; i >= 0; i--)
	    				 	fprintf(targetFile, "POP R%d\n", i);
	    				 reg_number = status;
	    				 break;
	    				 
	    case NODE_READ: st_entry = lookup_symbol((t->left)->varname);

		              	number = st_entry->binding;

	    				for(i = 0; i <= reg_number; i++)
	    					fprintf(targetFile, "PUSH R%d\n", i);
	    				status = reg_number;
	    				
	    				fprintf(targetFile, "MOV R0, 7\n");
	    				fprintf(targetFile, "PUSH R0\n"); //function code
	    				fprintf(targetFile, "MOV R0,-1\n");
	    				fprintf(targetFile, "PUSH R0\n"); //argument 1
	    				fprintf(targetFile, "MOV R0,%d\n", number);
	    				fprintf(targetFile, "PUSH R0\n"); //argument 1
	    				fprintf(targetFile, "ADD SP,2\n");
	    				fprintf(targetFile, "INT 6\n");
	    				fprintf(targetFile, "SUB SP,5\n");
	    				
	    				for(i = status; i >= 0; i--)
	    					fprintf(targetFile, "POP R%d\n", i);
	    				reg_number = status;
	    				break; 
	    		   
	    case NODE_IF: reg_1 = codeGen(t->left);
	    			  label_1 = getlabel();
	    			  fprintf(targetFile, "JZ R%d,L%d\n", reg_1, label_1);
	    			  number = codeGen(t->right);
	    			  fprintf(targetFile, "L%d:\n", label_1);
	    			  freeReg();
	    			  break;
	    			  
	    case NODE_IF_ELSE: reg_1 = codeGen(t->left);
	    				   label_1 = getlabel();
	    				   label_2 = getlabel();
	    				   fprintf(targetFile, "JZ R%d,L%d\n", reg_1, label_1);
	    				   freeReg();
	    				   number = codeGen(t->middle);
	    				   fprintf(targetFile, "JMP L%d\n", label_2);
	    				   fprintf(targetFile, "L%d:\n", label_1);
	    				   number = codeGen(t->right);
	    				   fprintf(targetFile, "L%d:\n", label_2);
	    				   break;
	    				   
	   case NODE_WHILE: label_1 = getlabel();
	   					label_2 = getlabel();
	   					
	   					prev_while_start = while_start;
	   					prev_while_end = while_end;
	   					
	   					while_start = label_1;
	   					while_end = label_2;
	   					
	   					fprintf(targetFile, "L%d:\n", label_1);
	   					
	   					number = codeGen(t->left);
	   					reg_1 = codeGen(t->right);
	   					fprintf(targetFile, "JZ R%d,L%d\n", reg_1, label_2);
	   					freeReg();
	   					
	   					fprintf(targetFile, "JMP L%d\n", label_1);
	   					fprintf(targetFile , "L%d:\n", label_2);
	   					
	   					while_start = prev_while_start;
	   					while_end = prev_while_end;
	   					break;
	   					
	   case NODE_BREAK: if(while_end != -1)
	   						fprintf(targetFile, "JMP L%d\n", while_end);
	   					break;
	   					
	   case NODE_CONT: if(while_start != -1)
	   						fprintf(targetFile, "JMP L%d\n", while_start);
	   					break;
	    			  
	 }
}

