typedef struct node{
	int val;   //value of a number for NUM nodes
	char *op;   //name of a variable
	int type;   //type of variable
	int nodetype; //information about non-leaf node - read/write/connector
	struct node* left; 
	struct node* right;
}node;

struct node* makeLeafNode(int n);
struct node* makeOperatorsNode(char op, struct node* l, struct node* r);


int codeGen(struct node* t);

