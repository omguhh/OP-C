#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"


// a structure called BINTTREE that contains a key,value and defines th left + right sections of the tree.
struct BINTREE {
  int key;
  int value;
  bintree *left;
  bintree *right;
} ;
// Need to allocate space within the PC for the new node to be added to the tree.

bintree *mkNode( int key, int value, bintree *left, bintree *right)
{
/*pretty straight forward stuff. allocate memory for the tree being referenced by the pointer,then set the values of the node based on the structure we were given*/

	bintree *tree = malloc(sizeof(bintree));
	tree->key = key;
	tree->value=value;
	tree->left=left;
	tree->right=right;
	return tree;

}
/*free a specific node */

void freeNode( bintree * tree)
{
  free(tree);
}
/*need to remember there's no 'root' node explicitly defined here*/
/*frees everything on the left + right trees*/

/*NULLIFY ALL THE THINGS */
void freeBinTree( bintree *tree)
{
  if(tree->left != NULL) {
	 freeBinTree(tree->left);
	 tree->left=NULL;	
	}

	else if(tree->right != NULL) {
	 freeBinTree(tree->right);
	 tree->right=NULL;	
	}
else {
        /*for the root*/
	freeNode(tree); 
	return;
}


}

static
void indent( int off)
{
  int i;

  for( i=0; i<off; i++) {
    printf( " ");
  }
}
/*gonna make you pretty with ascii printing*/
static
void printBinTreeOff( int off, bintree *tree)
{
  if (tree != NULL) {
    printf( "Node{ key:%d value:%d\n", tree->key, tree->value);
    off += 6;
    indent( off);
    printf( "left: ");
    printBinTreeOff( off+6, tree->left);
    indent( off);
    printf( "right:");
    printBinTreeOff( off+6, tree->right);
    indent( off-2);
    printf( "}\n");
  } else {
    printf( "NULL\n");
  }
}

void printBinTree( bintree *tree)
{
  printBinTreeOff( 0, tree);
}
// tree2's values are more important than tree1's
bintree *mergeBinTrees( bintree *tree1, bintree *tree2)
{
  if(tree2==NULL) return tree1;
  else {
	mergeBinTrees(tree1, tree2->left);
        mergeBinTrees(tree1, tree2->right);
        tree1= insertKey( tree2->key,tree2->value,tree1);
  }
}

bintree *insertKey( int key, int value, bintree *tree)
{
 // 1. If the tree is empty, return a new, single node
  if (tree == NULL) {
    return(mkNode(key, value, NULL, NULL));
  }
  else {
    // 2. Otherwise, recur down the tree
    if (key < tree->key) tree->left = insertKey(key,value,tree->left);
    else if(key == tree->key) tree->value = value;
    else tree->right = insertKey(key,value,tree->right);
    return(tree);
  } 
}

bintree *deleteKey( int key, bintree *tree)
{
    // base case
    if (tree == NULL) return tree;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < tree->key)
        tree->left = deleteKey(key, tree->left);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > tree->key)
        tree->right = deleteKey(key, tree->right);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (tree->left == NULL)
        {
            bintree *temp = tree->right;
            free(tree);
            return temp;
        }
        else if (tree->right == NULL)
        {
            bintree *temp = tree->left;
            free(tree);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
       
       
        bintree* current  = tree->right;
                while (current->left != NULL)
                           current = current->left;                        
                bintree* temp = current;
               
        // Copy the inorder successor's content to this node
        tree->key = temp->key;
 
        // Delete the inorder successor
        tree->right = deleteKey(temp->key, tree->right);
    }
    return tree;
       
}

int findKey( int key, bintree* tree)
{
        if (tree == NULL){
            return 0;
        }
        if (tree->key == key){
                return tree->value;
        }
        if (key < tree->key){
      return findKey(key, tree->left);
        }else{
      return findKey(key, tree->right);
        }
}
