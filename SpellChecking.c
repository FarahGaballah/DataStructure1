#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef struct TNode
{
    char* data;
    struct TNode *left;
    struct TNode *right;
} TNode;

typedef struct Tree
{

    TNode* root;

} Tree;

 void init(Tree* T)
 {
     T->root=NULL;
 }


void addTNode(TNode **p, char* d) {
if ((*p) == NULL)
{
        TNode* add=(TNode*)malloc(sizeof(TNode));
        add->data=(char*)malloc(50*sizeof(char));
        add->left=NULL;
        add->right=NULL;
        strcpy(add->data,d);
        *p=add;
}

else if (strcasecmp((*p)->data,d)<0)
   addTNode(&((*p)->right), d);
else if (strcasecmp((*p)->data,d)>0)
   addTNode(&((*p)->left), d);
}

int max(int n1,int n2)
{
    if(n1>n2)
        return n1;
    else
        return n2;
}



int height(TNode *root)
{
    return (root == NULL) ? -1: 1 + max(height(root->left), height(root->right));
}

int size(TNode *root)
{
    return (root==NULL)? 0:1 + size(root->left) + size(root->right);
}

TNode* search(TNode *root, char* str)
{


    if ( strcmp(str,root->data)==0 )
        return NULL;

    if (strcmp(str,root->data)<0)
    {
        if(root->left==NULL)
            return root;
        else
        return search(root->left,str);
    }
    else
    {
        if(root->right==NULL)
            return root;
        else
        return search(root->right,str);
    }

}


char* next(TNode *root, TNode* nd) {

if (nd->right!=NULL)
{
   nd=nd->right;
 while(nd->left!=NULL)
        nd=nd->left;
 return nd->data;
}
else
{
  TNode* successor = NULL;
  TNode* ancestor = root;
		while(ancestor != nd) {
			if(strcmp(nd->data,ancestor->data)<0) {
				successor = ancestor;
				ancestor = ancestor->left;
			}
			else
				ancestor = ancestor->right;datadata
		}
		return successor->data;
}


}


char* prev(TNode *root, TNode* nd) {

if (nd->left!=NULL)
{
 nd=nd->left;
 while(nd->right!=NULL)
        nd=nd->right;
 return nd->data;
}
else
{
  TNode* successor = NULL;
  TNode* ancestor = root;
		while(ancestor != nd) {
			if(strcmp(nd->data,ancestor->data)>0) {
				successor = ancestor;
				ancestor = ancestor->right;
			}
			else
				ancestor = ancestor->left;
		}
		return successor->data;
}


}


void readFile(TNode** root ,char* filename)
{
    FILE* fp=fopen(filename,"r");
    assert(fp!=NULL);
    char* str=(char*)malloc(50*sizeof(char));
    while(!feof(fp))
    {
        fscanf(fp,"%s",str);
        addTNode(root,str);
    }
    fclose(fp);
}


int main(int argc, char**argv)
{
    if(argc!=2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    char str[100];
    Tree dict;
    init(&dict);
    readFile(&(dict.root),argv[1]);
    printf("Height of tree: %d\n",height(dict.root));
    printf("Size of tree: %d\n",size(dict.root));
    printf("Please enter sentence:\n");
    scanf("%[^\n]s",str);
    char* token=strtok(str," ");
    TNode* en;
    while(token!=NULL)
    {

    en=search(dict.root,token);
    if(en==NULL)
        printf("%s - CORRECT\n",token);
    else
        printf("%s - %s,%s,%s\n",token,en->data,next(dict.root,en),prev(dict.root,en));

    token = strtok(NULL," ");

    }

}
