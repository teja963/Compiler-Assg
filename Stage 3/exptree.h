#define NODE_CONNECT 0
#define NODE_PLUS 1
#define NODE_MINUS 2
#define NODE_MUL 3
#define NODE_DIV 4
#define NODE_ID 5
#define NODE_NUM 6
#define NODE_ASSGN 7
#define NODE_READ 8
#define NODE_WRITE 9

typedef struct node{
	int val;   //value of a number for NUM nodes
	char *op;   //name of a variable
	int type;   //type of variable
	int nodetype; //information about non-leaf node - read/write/connector
	char *varname; //Name of variable for ID names
	struct node* left; 
	struct node* right;
}node;

struct node* makeLeafNode(int n);
struct node* makeOperatorsNode(char op, struct node* l, struct node* r);
struct node* createTree(int type, int val, int nodetype, char*name, struct node* left, struct node* right);
int codeGen(struct node* t);

