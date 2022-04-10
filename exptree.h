typedef struct node{
	int val;
	char *op;
	int type;
	struct node* left;
	struct node* right;
}node;

struct node* makeLeafNode(int n);
struct node* makeOperatorsNode(char op, struct node* l, struct node* r);
