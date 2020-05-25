#include <stdio.h>
#include <stdlib.h>

typedef struct RBTnode
{
 int data;
 int colour; //0-Red	1-Black
 struct RBTnode * left, * right, *parent;
} node;

/* Red Black Tree operations
	 1. isEmpty(T) : Checks if the RBT T is empty and returns a integer accordingly.
	 2. find(T,x) : Checks if a node with data x exists in the RBT T and returns a pointer accordingly.  
	 3. inPred(T,x) : Finds the inorder predecessor of the node with data x in the RBT T, if it exists, and returns the pointer.
	 4. inSucc(T,x) : Finds the inorder successor of the node with data x in the RBT T, if it exists, and returns the pointer.
	 5. leftRotate(T,x) : Rotates in anticlockwise direction about the node with data x in RBT T, if it exists.
	 6. rightRotate(T,x) : Rotates in clockwise direction about the node with data x in RBT T, if it exists.
	 7. insert(T,x) : Inserts a node with data x into the RBT T, if it doesn't exist already in T, and restructures the tree appropriately. In default, a red node is inserted.
	 8. delete(T,x) : Deletes a node with data x from the RBT T, if it exists and restructures the tree appropriately. 
	 9. inOrder(T) : Prints the data in RBT T by using inorder traversal.
	10. blackH(T) : Returns the black height of the RBT T. (Including Dummy Nodes).
	11. colour(T,x) : Returns the number equivalent to the colour of the node with data x in T, if it exists.
	12. height(T) : Returns the height of the RBT T.
	13. range(T,x,y) : Returns a list of all the data in the RBT T in range [x,y]. Note : x<=y. 
	 14. leafCount(T) : Returns the number of leaves (Not External Nodes i.e. Dummy Nodes) present in the RBT T.
*/

int isEmpty(node * T)
{
	return(T==NULL);
}


node * find(node *T, int x)
{
 node * p=T;
 if(!isEmpty(T)) 
 {
 while(p!=NULL && p->data!=x)
 {
 	if(p->data>x)	p=p->left;
 	else p=p->right;
 }
 }
 return p;
}

node *inPred(node * T, int x)
{
 node * p=find(T,x),*a;
 if(p==NULL) printf("ERROR : Given data doesn't exist in the tree.\n");
 else
 {
 	if(p->left!=NULL)
 	{
 		a=p->left;
 		while(a->right!=NULL)	a=a->right;
 	}
 	else
 	{
 		a=p->parent;
 		while(a!=NULL && p==a->left)
 		{
 			p=a;
 			a=a->parent;
 		}
 	}
 }
 return a;
}

node *inSucc(node * T, int x)
{
 node * p=find(T,x),*a;
 if(p==NULL) printf("ERROR : Given data doesn't exist in the tree.\n");
 else
 {
 	if(p->right!=NULL)
 	{
 		a=p->right;
 		while(a->left!=NULL)	a=a->left;
 	}
 	else
 	{
 		a=p->parent;
 		while(a!=NULL && p==a->right)
 		{
 			p=a;
 			a=a->parent;
 		}
 	}
 }
 return a;
}


void leftRotate(node **T, int x)
{
 node * p=find(*T,x);
 if(p==NULL)
 {
  	printf("ERROR : Given data doesn't exist in the tree.\n");
	exit(1);
 } 
 else
 {
 	if(p->right==NULL)	printf("ERROR : Node is not Left Rotation compatible.\n");
 	else
 	{
 	node *q = p->right;
 	p->right =q->left;
 	if(q->left!=NULL)	q->left->parent=p;
 	q->parent=p->parent;
 	if(p->parent!=NULL && p==p->parent->left)	p->parent->left=q;
 	else if(p->parent!=NULL && p==p->parent->right)	p->parent->right=q;
 	else    *T=q;
 	p->parent=q;
 	q->left=p;
 	}
 }
 return;
}


void rightRotate(node **T, int x)
{
 node * p=find(*T,x);
 if(p==NULL) printf("ERROR : Given data doesn't exist in the tree.\n");
 else
 {
 	if(p->left==NULL)	printf("ERROR : Node is not Right Rotation compatible.\n");
 	else
 	{
 	node *q = p->left;
 	p->left =q->right;
 	if(q->right!=NULL)	q->right->parent=p;
 	q->parent=p->parent;
 	if(p->parent!=NULL && p==p->parent->left)	p->parent->left=q;
 	else if(p->parent!=NULL && p==p->parent->right)	p->parent->right=q;
 	else    *T=q;
 	p->parent=q;
 	q->right=p;
 	}
 }
 return;
}


void insert(node **T, int x)
{
 if(find(*T,x)!=NULL)	printf("ERROR : Given data already exists in the tree.\n");
 else
 {
	node *p=(node*)malloc(sizeof(node)),*a,*b;
	if(p==NULL)
	{
		printf("ERROR in allocation of memory.\n");
		exit(1);
	}
	p->data=x;
	p->colour=0;
	p->left=p->right=p->parent=NULL;
	//insertion
	if(isEmpty(*T))
	{
		(*T)=p;
		(*T)->colour=1;
	}
	else
	{
		a=*T,b=NULL;
		while(a!=NULL)
		{
			b=a;
			if(p->data<a->data)	a=a->left;
			else    a=a->right;	
		}
		p->parent = b;
		if(p->data<b->data)	b->left=p;
		else    b->right=p;
		a=p;
		//restructuring
		while(a!=*T && a->parent->colour==0)
		{
			//A's parent is left child
			if(a->parent==a->parent->parent->left)
			{
				b=a->parent->parent->right;
				//B is red (Case 0)
				if(b!=NULL && b->colour==0)
				{
					a->parent->colour=1;
					b->colour=1;
					if(b->parent!=*T)	b->parent->colour=0;
					else    b->parent->colour=1;
					a=a->parent->parent;
				}
				//B is black or NULL and A is right child (Case 3)
				else if(a==a->parent->right)
				{
					leftRotate(T,a->parent->data);
					rightRotate(T,a->parent->data);
					a->colour=1;
					a->right->colour=0;
				}
				//B is black or NULL and A is left child (Case 2)
				else
				{
					rightRotate(T,a->parent->parent->data);
					a->parent->colour=1;
					a->parent->right->colour=0;
				}
			}
			// A's parent is right child
			else
			{
				b=a->parent->parent->left;
				//B is red (Case 0)
				if(b!=NULL && b->colour==0)
				{
					a->parent->colour=1;
					b->colour=1;
					if(b->parent!=*T)	b->parent->colour=0;
					else b->parent->colour =1;
					a=a->parent->parent;
				}
				//B is black or NULL and A is left child (Case 4)
				else if(a==a->parent->left)
				{
					rightRotate(T,a->parent->data);
					leftRotate(T,a->parent->data);
					a->colour=1;
					a->left->colour=0;
				}
				//B is black or NULL and A is right child (Case 1) 
				else
				{
					leftRotate(T,a->parent->parent->data);
					a->parent->colour=1;
					a->parent->left->colour=0;
				}				
			}
		}
		(*T)->colour=1;
	}
 }
 (*T)->colour=1;
 return;
}


void delete(node **T, int x)
{
 node *p=find(*T,x),*a,*b;
 if(p==NULL) 	printf("ERROR : Given data doesn't exist in the tree.\n");	
 //deletion
 else
 {
 	//P has two children
 	if(p->left!=NULL && p->right!=NULL)
 	{
 		a=inSucc(*T,x);
 		p->data=a->data;
 		a->data=x;
 		b=p;
 		p=a;
 		a=b;
 	} 		
 	//P has only left child
 	if(p->left!=NULL)
 	{	
 		a=p->left;
 		p->data=a->data;
 		a->data=x;
 		b=p;
 		p=a;
 		a=b;
 		a->left=NULL;
 		free(p);
 	}	
 	//P has only right child
 	else if(p->right!=NULL)
 	{
 		a=p->right;
 		p->data=a->data;
 		a->data=x;
 		b=p;
 		p=a;
 		a=b;
 		a->right=NULL;	
 		free(p);	
 	}	
 	//P has no child
 	else
	{
 		//P is red leaf.
 		if(p->colour==0)
 		{
 			if(p==p->parent->left)	p->parent->left=NULL;
 			else    p->parent->right=NULL;
 			free(p);
 		}
 		//P is black leaf
 		else		
 		//restructuring (double black)
	 	{
 			//P is not root
 			if(p->parent!=NULL)
 			{
 				//P is left child
 				if(p==p->parent->left)
 				{
 					b=p->parent->right;
 					//B is red (Case 1)
 					if(b->colour==0)
 					{
 						leftRotate(T,b->parent->data);
 						p->colour=1;
 						b->colour=1;
 					}
 					//B is black (Case 2)
 					else
 					{
 						//Both the children of B are black (Case 2.1)
 						if(b->left!=NULL && b->right!=NULL && b->left->colour==1 && b->right->colour==1)
 						{
 							b->colour=0;
 							b->parent->colour+=1;
 							p->colour=1;
 							p=p->parent;
 						}
 						//B's left child is red (Case 2.2)
 						else if(b->left!=NULL && b->left->colour==0)
 						{
							rightRotate(T,b->data);
							b=b->parent;
							b->colour=1;
							b->right->colour=0;
 						}
 						//B's right child is red (Case 2.3)
 						if(b->right!=NULL && b->right->colour==0)
 						{
 							leftRotate(T,b->parent->data);
 							b->colour=b->left->colour;
 							b->left->colour=1;
 							b->right->colour=1;
 							b->left->left=NULL;
 						}
 					}	
 				}
				//A is right child
				else if(p->parent!=NULL && p==p->parent->right)
				{
					b=p->parent->left;
					//B is red (Case 1)
					if(b->colour==0)
					{
						rightRotate(T,b->parent->data);
						p->colour=1;
						b->colour=1;
					}
					//B is black (Case 2)
					else
					{
						//Both the children of B are black (Case 2.1)
 						if(b->left!=NULL && b->right!=NULL && b->left->colour==1 && b->right->colour==1)
 						{
 							b->colour=0;
 							b->parent->colour+=1;
 							p->colour=1;
 							p=p->parent;
 						}
 						//B's right child is red (Case 2.2)
 						else if(b->right!=NULL && b->right->colour==0)
 						{
							leftRotate(T,b->data);
							b=b->parent;
							b->colour=1;
							b->left->colour=0;
 						}
 						//B's left child is red (Case 2.3)
 						if(b->left!=NULL && b->left->colour==0)
 						{
 							rightRotate(T,b->parent->data);
 							b->colour=b->right->colour;
 							b->left->colour=1;
 							b->right->colour=1;
 							b->right->right=NULL;
 						}
					}	
				}	
				free(p);
				(*T)->colour=1;
 			}	
 			//P is root
 			else
 			{
 				*T=NULL;
 				free(p);
 			}
 		}		
 	}
 }	
 return;
}

void inOrder(node *T)
{
 node *p=T;
 if(!isEmpty(p))
 {
 	inOrder(p->left);
 	printf("%d-%d ",p->data,p->colour);
 	inOrder(p->right);
 }
 return;
}


int blackH(node* T)
{
	int x=1;
	node *p=T;
	while(p!=NULL)
	{
		if(p->colour==1)	x++;
		p=p->left;
	}
	return x;
}


int colour(node *T,int x)
{
 return(find(T,x)->colour);
}


int height(node *T)
{
	node *p=T;
	if(isEmpty(p))	return -1;
	int a=height(p->left),b=height(p->right);
	return((a>b?a:b)+1);	
}


void range(node *T,int x, int y)
{
 if(x>y)	printf("ERROR : First input is greater than second input.\n");
 else
 {
	printf("Data available in the following range : ");
	for(int i=x;i<=y;i++)
	{
		if(find(T,i)!=NULL)	printf("%d ", i);	
	}
	printf("\n");
 }
 return;	
}


int leafCount(node * T)
{
 node *p=T;
 if(isEmpty(p))	return 0;
 if(p->left==NULL && p->right==NULL)	return 1;
 else return (leafCount(p->left) + leafCount(p->right));
}


int main()
{
	int n,x,y,a,b;
	node *T=NULL;
	printf("Enter the number of insertions to be done : ");
	scanf("%d",&n);
	printf("Enter the elements :\n");
	for(y=0;y<n;y++)
	{
		scanf("%d",&x);
		insert(&T,x);
	}
	printf("Data in Red Black Tree in the Inorder form : ");
	inOrder(T);
	printf("\n");
	y=0;
	while(y!=5)
	{
		printf("Choose among the following options :\n");
		printf("1. Delete a node.\n");
		printf("2. Count the number of leaves.\n");
		printf("3. Find the height of the tree.\n");
		printf("4. Get the data within the range [a,b].\n");
		printf("5. Exit.\n");
		scanf("%d",&y);
		switch(y)
		{
			case 1:
				printf("Enter the number to be deleted : ");
				scanf("%d",&x);
				delete(&T,x);
				printf("Data in updated Red Black Tree in the Inorder form : ");
				inOrder(T);
				printf("\n");
				break;
			case 2:
				printf("The number of leaves in the tree : %d\n",leafCount(T));
				break;
			case 3:
				printf("Height of the tree : %d\n",height(T));
				break;
			case 4:
				printf("Enter the lower range : ");
				scanf("%d",&a);
				printf("Enter the upper range : ");
				scanf("%d",&b);
				range(T,a,b);
				break;
			case 5:
				break;
			default:
				printf("Please enter the option in range [1,5].\n");
				break;
		}
	}
	free(T);
	return 0;
}

