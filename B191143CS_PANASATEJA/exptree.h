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
#define NODE_IF 10
#define NODE_IF_ELSE 11
#define NODE_WHILE 12
#define NODE_LT 13
#define NODE_GT 14
#define NODE_LE 15
#define NODE_GE 16
#define NODE_EQ 17
#define NODE_NEQ 18
#define NODE_BREAK 19
#define NODE_CONT 20

#define TYPE_VOID 0
#define TYPE_INT 1
#define TYPE_BOOL 2

typedef struct node{
	int val;   //value of a number for NUM nodes
	char *op;   //name of a variable
	int type;   //type of variable
	int nodetype; //information about non-leaf node - read/write/connector
	char *varname; //Name of variable for ID names
	struct node* left; 
	struct node* right;
	struct node* middle;
}node;

struct node* makeLeafNode(int n);
struct node* makeOperatorsNode(char op, struct node* l, struct node* r);
struct node* createTree(int type, int val, int nodetype, char*name, struct node* left, struct node* right, struct node* mid);
int codeGen(struct node* t);

