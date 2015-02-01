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

	bintree *tree = malloc(sizeof(*tree));
	tree->key = key;
	tree->value=value;
	tree->left=left;
	tree->right=right;
	return tree;

}
/*free the pointer */

void freeNode( bintree * tree)
{
  if(tree== NULL) return;
  freeNode(tree->left);
  freeNode(tree->right);
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

bintree *mergeBinTrees( bintree *tree1, bintree *tree2)
{
  /* fill in here */
}

bintree *insertKey( int key, int value, bintree *tree)
{
  /* fill in here */
}

bintree *deleteKey( int key, bintree *tree)
{
  /* fill in here */
}

int findKey( int key, bintree *tree)
{
  /* fill in here */
}
