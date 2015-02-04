   #include <stdio.h>
    #include <stdlib.h>
    #include "bintree.h"
     
    struct BINTREE {
      int key;
      int value;
      bintree *left;
      bintree *right;
      int height;
    } ;
     
    bintree *mkNode( int key, int value, bintree *left, bintree *right)
    {       /* create node */
           
            bintree *tree = (malloc(sizeof(bintree)));
           
            tree -> key = key;                              // node key
            tree -> value = value;                  // node value
            tree -> left = left;                    // left child
            tree -> right = right;                  // right child
            tree -> height = 1;                             // height of the node
            return tree;                                    // return the new tree
    }
     
    void freeNode( bintree *tree) {
            // delete node
           
            free(tree);                                             // delete the node
    }
     
    void freeBinTree( bintree *tree) {
            // delete entire tree
           
            if(tree != NULL) {                              // if node exists
                    freeBinTree(tree->left);        // delete left branch
                    freeBinTree(tree->right);       // delete right branch
                    free(tree);                                     // delete node
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
    {       // merge tree2 into tree1
           
            mergeBinTrees(tree1, tree2->left);                                      // merge left branch
            mergeBinTrees(tree1, tree2->right);                                     // merge right branch
            tree1 = insertKey(tree2->key, tree2->value, tree1);     // insert tree2 into tree1
            return tree1;                                                                           // return the merged tree
    }
     
    bintree *insertKey( int key, int value, bintree *tree)
    {       // insert a mode with a value
           
            if (tree==NULL) {                                                               // if tree is empty,
                    return (mkNode(key, value, NULL, NULL));        // return the new node
            }
            else {
                    if (key < tree->key)                                                                    // if new node smaller than existing node,
                            tree->left = insertKey(key, value, tree->left);         // put it on the left
                    else if (key > tree->key)                                                               // if new node larger than existing node,
                            tree->right = insertKey(key, value, tree->right);       // put it on the right
                    else                                                                                                    // if new node equal to existing node,
                            tree->value = value;                                                            // change value to new value (replaces existing node)
                           
                    tree->height = max(findHeight(tree->left), findHeight(tree->right))+1;  // update height of node
                   
                    int balance = getBalance(tree);                 // get the balance factor
                   
                    // if tree is unbalanced, fix it!
                    // Case 1 - left left
                    if (balance > 1 && key < tree->left->key) {
                            printf( "Case 1 - left left %d\n", balance);
                            return rightRotate(tree);
                    }
                    // Case 2 - left right
                    if (balance > 1 && key > tree->left->key) {
                            tree->left = leftRotate(tree->left);
                            printf( "Case 2 - right right %d\n", balance);
                            return rightRotate(tree);
                    }
                    // Case 3 - right right
                    if (balance < -1 && key > tree->right->key) {
                            printf( "Case 3 - left right %d\n", balance);
                            return leftRotate(tree);
                    }
                    // Case 4 - right left
                    if (balance < -1 && key < tree->right->key) {
                            printf( "Case 4 - right left %d\n", balance);
                            tree->right = rightRotate(tree->right);
                            return leftRotate(tree);
                    }
     
            }
            return(tree);                                                           // return the altered tree
    }
     
    bintree *deleteKey( int key, bintree *tree)
    {       // Delete a key from the tree
     
        if (tree == NULL) return tree;                              // check tree exists
     
            else if (key < tree->key)                                               // if node to delete less than base node,
                    tree->left = deleteKey(key, tree->left);        // it is on the left
            else if (key > tree->key)                                               // if node to delete is more than base node,
                    tree->right = deleteKey(key, tree->right);      // it is on the right
     
            else {                                                                                  // if node equals base node, delete base node:
            if((tree->left == NULL) || (tree->right == NULL)) {                     // If node has one or no child
                            bintree *temp = tree->left ? tree->left : tree->right;  // save child if it exists
     
                if(temp == NULL) {  // if no child
                    temp = tree;    // save tree
                    tree = NULL;    // delete node
                }
               
                else                                // if one child case
                *tree = *temp;              // copy the child
     
                            free(temp);                     // delete node
            }
            else {                          // if node has two children, get the inorder successor:
                bintree *temp = minValueNode(tree->right);                  // in the right subtree
                            tree->key = temp->key;                                                          // Copy the successor to this node
                tree->right = deleteKey(temp->key, tree->right);    // Delete the successor
            }
        }
            if (tree == NULL) return tree;  // if only 1 node, return it
     
        tree->height = max(findHeight(tree->left), findHeight(tree->right)) + 1;// update height
            int balance = getBalance(tree);         // get balance factor
        // if unbalanced, fix it!
       
        // Case 1 - left left
        if (balance > 1 && getBalance(tree->left) >= 0) {
                    printf( "Case 1 - left left %d\n", balance);
            return rightRotate(tree);
            }
        // Case 2 - left right
        if (balance > 1 && getBalance(tree->left) < 0) {
            tree->left =  leftRotate(tree->left);
            printf( "Case 2 - left right %d\n", balance);
            return rightRotate(tree);
        }
     
        // Case 3 - right right
        if (balance < -1 && getBalance(tree->right) <= 0) {
                    printf( "Case 3 - right right %d\n", balance);
            return leftRotate(tree);
            }
        // Case 4 - right left
        if (balance < -1 && getBalance(tree->right) > 0) {
            tree->right = rightRotate(tree->right);
                    printf( "Case 4 - right left %d\n", balance);
            return leftRotate(tree);
        }
     
        return tree; // return the final tree
    }
     
    int findKey( int key, bintree *tree) {
            // return the key value of the node, or 0 if not found
            if (tree != NULL) {                                                                                             // check the tree exists
                    if (tree->key == key) return tree->value;                                       // if key = node, return its value
                    else if (key > tree->key) return findKey(key, tree->right);     // if key > node, check right branch
                    else return findKey(key, tree->left);                                           // if key < node, check left branch
            }
            else return 0;                                                                                                  // if key doesn't exist, return 0
    }
     
    int findHeight(bintree *tree) {
            // return the height of the current node
            if (tree == NULL) return 0;
            return tree->height;
    }
     
    bintree *rightRotate(bintree *tree) {// y=tree, x=x, T2=y
            // rotate right
            bintree *x = tree->left;
            bintree *y = x->right;
           
            x->right = tree;
            tree->left = y;
           
            tree->height = max(findHeight(tree->left), findHeight(tree->right))+1;
            x->height = max(findHeight(x->left), findHeight(x->right))+1;
           
            return x;
    }
     
    bintree *leftRotate(bintree *tree) {// x=tree, y=x, T2=y
            // rotate left
            bintree *x = tree->right;
            bintree *y = x->left;
           
            x->left = tree;
            tree->right = y;
           
            tree->height = max(findHeight(tree->left), findHeight(tree->right))+1;
            x->height = max(findHeight(x->left), findHeight(x->right))+1;
           
            return x;
    }
     
    int max(int a, int b) {
            // return max of two integers
            return (a > b)? a:b;
    }
     
    int getBalance(bintree *tree) {
            // return balance factor of a node
            if (tree == NULL) return 0;
            return findHeight(tree->left) - findHeight(tree->right);
    }
     
    bintree *minValueNode(bintree *tree)
    {       // Find the lowest key in this branch
        bintree *current = tree;
     
        while (current->left != NULL)
            current = current->left;
     
        return current;
    }

