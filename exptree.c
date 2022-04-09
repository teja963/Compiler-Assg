#include<stdio.h>
#include<stdlib.h>
#include"exptree.h"

int reg_number = -1;
struct node* makeLeafNode(int n);
struct node* makeOperatorsNode(char op, struct node* l, struct node* r);

int getReg(){
	reg_number += 1;
	return reg_number;
}

int freeReg(){
	return reg_number--;
}

int codeGen(struct node* t, FILE *targetfile){
	
}

int evaluate(struct node* t){
	
}

int main(){

	return 0;
	
	
}

