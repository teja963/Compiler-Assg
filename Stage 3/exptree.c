#include"exptree.h"
#include<string.h>	
struct node* createTree(int type, int val, int nodetype, char *name, struct node* left, struct node* right){
	struct node *tmp;
	tmp = (struct node*)malloc(sizeof(struct node));
	tmp->val = val;
	tmp->type = type;
	tmp->nodetype = nodetype;
	if(name != NULL){
		tmp->varname = (char *)malloc(sizeof(name));
		strcpy(tmp->varname, name);
	}
	tmp->left = left;
	tmp->right = right;
	return tmp;
}

int evaluate(struct node* t){
	if(t->op == NULL){
		return t->val;
	}
	else{
		switch(*(t->op)){
			case '+': return evaluate(t->left) + evaluate(t->right);
					  break;
					  
			case '-': return evaluate(t->left) - evaluate(t->right);
					  break;
					  
			case '*': return evaluate(t->left) * evaluate(t->right);
					  break;
					  
			case '/': return evaluate(t->left) / evaluate(t->right);
					  break;			  
		}
	}
}

struct node* makeLeafNode(int n){
	struct node* tmp;
	tmp = (struct node*)malloc(sizeof(struct node));
	tmp->val = n;
	tmp->op = NULL;
	tmp->type = -1;
	tmp->left = NULL;
	tmp->right = NULL;
}

struct node* makeOperatorsNode(char op, struct node* l, struct node* r){
	struct node* tmp;
	tmp = (struct node*)malloc(sizeof(struct node));
	tmp->op = malloc(sizeof(char));
	*(tmp->op) = op;
	tmp->left = l;
	tmp->right = r;
	return tmp;
} 

