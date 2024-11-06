#include <stdio.h>
#include <stdlib.h>
typedef struct bst
{
int data;
struct bst *left, *right;
} node;
void insert(node **root, node *newNode);
void inorder(node *root);
node *search(node *root, int key, node **parent);
void del(node **root, int key);
node *getnode();
int main()
{
int choice;
char ans = 'N';
int key;
node *root = NULL;
node *parent,*temp;
clrscr();
do
{
printf("\n1. Create\n2. Search\n3. Delete\n4. Display\n5. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice)
{
case 1:
do
{
node *s = getnode();
printf("Enter the element: ");
scanf("%d", &s->data);
insert(&root, s);
printf("Do you want to enter more elements? (y/n): ");
ans = getch();
printf("\n");
} while (ans == 'y' || ans == 'Y');
break;
case 2:
printf("Enter the element to search: ");
scanf("%d", &key);
parent = NULL;
temp = search(root, key, &parent);
if (temp)
{
printf("Element %d found with parent %d\n", temp->data, parent ? parent->data : -1);
}
else
{
printf("Element %d not found.\n", key);
}
break;
case 3:
printf("Enter the element to delete: ");
scanf("%d", &key);
del(&root, key);
break;
case 4:
if (root == NULL)
{
printf("Tree is not created.\n");
}
else
{
printf("Inorder traversal: ");
inorder(root);
printf("\n");
}
break;
case 5:
printf("Exiting...\n");
break;
default:
printf("Invalid choice. Please try again.\n");
}
} while (choice != 5);
return 0;
}
node *getnode()
{
node *temp = (node *)malloc(sizeof(node));
temp->left = NULL;
temp->right = NULL;
return temp;
}
void insert(node **root, node *newNode)
{
if (*root == NULL)
{
*root = newNode;
}
else if (newNode->data < (*root)->data)
{
insert(&(*root)->left, newNode);
}
else
{
insert(&(*root)->right, newNode);
}
}
node *search(node *root, int key, node **parent)
{
node *temp = root;
*parent = NULL;
while (temp != NULL)
{
if (temp->data == key)
{
return temp;
}
*parent = temp;
if (key < temp->data)
{
temp = temp->left;
}
else
{
temp = temp->right;
}
}
return NULL;
}
void del(node **root, int key)
{
node *temp, *parent;
temp = search(*root, key, &parent);
if (temp == NULL) {
printf("Element %d not found.\n", key);
return;
}
if (temp->left == NULL && temp->right == NULL)
{
if (parent == NULL)
{
*root = NULL;
}
else if (parent->left == temp)
{
parent->left = NULL;
}
else
{
parent->right = NULL;
}
free(temp);
}
else if (temp->left == NULL || temp->right == NULL)
{
node *child = (temp->left != NULL) ? temp->left : temp->right;
if (parent == NULL)
{
*root = child;
}
else if (parent->left == temp)
{
parent->left = child;
}
else
{
parent->right = child;
}
free(temp);
}
else
{
node *succParent = temp;
node *succ = temp->right;
while (succ->left != NULL)
{
succParent = succ;
succ = succ->left;
}
temp->data = succ->data;
if (succParent->left == succ)
{
succParent->left = succ->right;
}
else
{
succParent->right = succ->right;
}
free(succ);
}
printf("Element %d deleted.\n", key);
}
void inorder(node *temp)
{
if (temp != NULL)
{
inorder(temp->left);
printf("%d ", temp->data);
inorder(temp->right);
}
}
