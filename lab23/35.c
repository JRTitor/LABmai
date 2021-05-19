#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define COUNT 10

typedef struct tree {
  char value;
  struct tree *left;
  struct tree *right;
} tree;

tree *createNode(char value) {
  tree* result = malloc(sizeof(tree));
  if (result != NULL) {
    result->left = NULL;
    result->right = NULL;
    result->value = value;
  }
  return result;
}

void print2DUtil(tree *root, int space) {
	if (root == NULL)
		return;

	space += COUNT;

	print2DUtil(root->right, space);
	printf("\n");

	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%c\n", root->value);

	print2DUtil(root->left, space);
}

void print2D(tree *root) {
  print2DUtil(root, 0);
}


bool insertNumber(tree **rootptr, char value) {

  tree *root = *rootptr;
  if (root == NULL) {
    *(rootptr) = createNode(value);
    return true;
  }

  else if (value == root->value) {
    return false;
  }

  else if (value <  root->value) {
    return insertNumber( &(root->left), value);
  }
  else {
    return insertNumber( &(root->right), value);
  }

}

tree *minValueNode(tree *node) {
    tree *current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}


tree *deleteNode(tree *root, char value) {

    if (root == NULL)
        return root;

    if (value < root->value)
        root->left = deleteNode(root->left, value);

    else if (value > root->value)
        root->right = deleteNode(root->right, value);

    else {

        if (root->left == NULL) {
            tree *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            tree *temp = root->left;
            free(root);
            return temp;
        }

        tree *temp = minValueNode(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

int nodeLvl(tree *root, int level) {
  if( root == NULL ) return 0;
  if( level == 0 ) return 1;
  return nodeLvl(root->left, level - 1) + nodeLvl(root->right, level - 1);
}

void maxNodeLvl(tree *root) {
  int lvl = 0, res = -1, resmax = 0;
  int keeplvl ;

  while (res != 0) {
    res = nodeLvl(root, lvl);
    if (res > resmax) {

      resmax = res;
      keeplvl = lvl;
    }
    lvl++;
  }
  printf("Max amount of nodes:%d\nOn the level :%d\n",resmax, keeplvl);
}


int main() {

  int a, g = 1;
  tree *root = NULL;

  while (g == 1) {

    printf("1.Add node 2.Print tree 3.Delete node 4.Do the task 5.Exit \n");
    scanf("%d", &a);
    putchar('\n');


    switch (a) {

      case 1:
        printf("Input:" );
        char value ;
        scanf(" %c", &value);
        insertNumber(&root, value);
        break;

      case 2:{
        print2D(root);
      }break;

      case 3:
        printf("Input:" );
        char element ;
        scanf(" %c", &element);
        deleteNode(root, element);
        break;

      case 4:
        maxNodeLvl(root);
        break;


      case 5:
        g = 0;
        break;
    }
  }
  return 0;
}
