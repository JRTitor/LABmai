#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#define COUNT 5

typedef struct numNchar {
  char var;
  int num;
}nc;

typedef struct node {
  nc value;
  struct node *next;
}node;

typedef node * stack;

typedef struct tree {
    nc value;
    struct tree *left;
    struct tree *right;
} tree;

bool push(stack *mystack, nc value) {

    node *newnode = malloc(sizeof(node));
    if (newnode == NULL) return false;

    newnode->value = value;
    newnode->next = *mystack;
    *mystack = newnode;
    return true;
}

nc pop(stack *mystack) {
  nc result;
  result.num = 0;
  result.var ='\0';

  if (*mystack == NULL) return result;

  result = (*mystack)->value;
  node *tmp = *mystack;
  *mystack = (*mystack)->next;
  free(tmp);
  return result;
}

nc peek (stack *mystack) {
  nc ret = (*mystack)->value;
  return  ret;
}

bool isOp(char ch) {
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')');
}

int prior(char ch) {
  if (ch == '+' || ch == '-') return 1;
  if (ch == '*'|| ch == '/') return 2;
  if (ch == '^') return 3;
  if (ch == '(') return 4;
  else return 0;
}

stack InfToPostf(char *exp) {

  stack out = NULL, opers = NULL;
  int res, preRes = 0;
  int preParRes;

  for (int i = 0; exp[i]; i++) {

    if(isalpha(exp[i])) {
      nc inptAl;

      inptAl.var = exp[i];
      inptAl.num = 0;
      push(&out, inptAl);
    }
    else if (isdigit(exp[i])) {
      int numb = 0;
      while (isdigit(exp[i])) {
        numb = 10*numb + (exp[i] - '0');
        i++;
      }
      i--;
      nc inptNu;

      inptNu.var = '\0';
      inptNu.num = numb;

      push(&out, inptNu);
    }

    else if (isOp(exp[i])) {
      res = prior(exp[i]);

      if (res <= preRes && preRes != 4 && exp[i] != ')') {
        push(&out, pop(&opers));

        nc inptOp;
        inptOp.var = exp[i];
        inptOp.num = 0;
        push(&opers, inptOp);
      }

      else if(exp[i] == ')'){
        push(&out, pop(&opers));
        pop(&opers);
      }

      else {
        nc inptOpS;
        inptOpS.num = 0;
        inptOpS.var = exp[i];
        push(&opers, inptOpS);
      }

    }
    preParRes = preRes;
    preRes = res;
  }

  while (opers != NULL) {
    push(&out, pop(&opers));
  }

  return out;
}

nc printNC(nc value) {
  if (value.num)
    printf("%d", value.num);

  else if (value.var)
    printf("%c", value.var);
}


tree *createNode(nc value) {
  tree* result = (tree*)malloc(sizeof(tree));
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

	print2DUtil(root->left, space);
	printf("\n");

	for (int i = COUNT; i < space; i++)
		printf(" ");
	printNC(root->value);

	print2DUtil(root->right, space);
}

void print2D(tree *root) {
  print2DUtil(root, 0);
}

bool ncNull(nc value) {
  if (((value.num) == 0) && ((value.var) =='\0'))
    return true;

  else return false;
}

nc RnullNC() {
  nc out;
  out.num = 0;
  out.var = '\0';
  return out;
}


bool NCisOp(nc ch) {
	return (ch.var == '+' || ch.var == '-' || ch.var == '*' || ch.var == '/' || ch.var == '^' || ch.var == '(' || ch.var == ')');
}
void add(tree **rootptr, nc a[], int *i) {
  nc value = a[(*i)];
  (*i) ++;

  if (ncNull(value))
    return;

  (*rootptr) = createNode(value);

  if (NCisOp(value)) {
    add( &(*rootptr)->left, a, &(*i));

    add( &(*rootptr)->right, a, &(*i));
  }
}


void PT(tree ** root) {
    if (*root == NULL) return;

  if ((*root)->right != NULL) {
    if ((*root)->right->left != NULL) printf("(");
    PT(&(*root)->right);
    if ((*root)->right->left != NULL) printf(")");
  }

  printNC((*root)->value);

  if ((*root)->left != NULL ) {
    if ((*root)->left->left != NULL) printf("(");
    PT(&(*root)->left);
    if ((*root)->left->left != NULL) printf(")");
  }
}


bool findEl(tree *rootAst, nc value) {
  if (rootAst != NULL) {

    nc Rvalue = rootAst->value;
    if ((value.num == Rvalue.num) && (value.var == Rvalue.var) ) {

      if ((rootAst->left->value.var == '+' && rootAst->right->value.var == '-') || (rootAst->left->value.var == '-' && rootAst->right->value.var == '+')) {

        if ((rootAst->left->left->value.var ==  rootAst->right->left->value.var && rootAst->left->left->value.num ==  rootAst->right->left->value.num
            && rootAst->left->right->value.var ==  rootAst->right->right->value.var && rootAst->left->right->value.num ==  rootAst->right->right->value.num)
            ||  (rootAst->left->left->value.var ==  rootAst->right->right->value.var && rootAst->left->left->value.num ==  rootAst->right->right->value.num
            && rootAst->left->right->value.var == rootAst->right->left->value.var && rootAst->left->right->value.num == rootAst->right->left->value.num)) {

          rootAst->value.var = '-';
          rootAst->left->value.var = '^';
          rootAst->right->value.var = '^';

          if (rootAst->left->left->value.var ==  rootAst->right->left->value.var) {
            rootAst->left->left->value.var = '\0';
            rootAst->left->left->value.num = 2;
            rootAst->left->right->value.var = rootAst->right->left->value.var;
            rootAst->left->right->value.num = rootAst->right->left->value.num;
            rootAst->right->left->value.var = '\0';
            rootAst->right->left->value.num = 2;

          }else {
            rootAst->left->left->value.var = '\0';
            rootAst->left->left->value.num = 2;
            rootAst->right->left->value.var = '\0';
            rootAst->right->left->value.num = 2;
            }
          }
        }
      return true;
    }

    else  {
      return (findEl(rootAst->right, value) || findEl(rootAst->left, value) );
    }
  }
}


int main() {

  char exp[256];
  stack out = NULL;
  tree *root = NULL;
  char el;
  nc tmpOut[256];
  int elOut = 0;
  int g = 1;


  while (g == 1) {
    int act;
    printf("\t\t\t\tMENU:\n");
    printf("1.Input the expresson\t2.Print expression\t3.Make expression tree\t4.Print expression from tree\n5.Print expression tree\t6.Do the task\t7.Print the task tree\t8.Exit\n" );
    scanf("%d",&act);
    switch (act) {

      case 1:{
        printf("Input the expression:");
        scanf("%s", exp);
        free(root);
        free(out);
        elOut = 0;
        break;
      }

      case 2:{// print
        printf("%s\n", exp);
        break;
      }

      case 3:{
        out = InfToPostf(exp);
        while(out) {
          tmpOut[elOut] = pop(&out);
          elOut++;
        }
        tmpOut[elOut] = RnullNC();

        int nn = 0;
        add(&root,tmpOut, &nn);
        break;
      }

      case 4:{
        PT(&root);
        putchar('\n');
        break;
      }

      case 5:{
        print2D(root);
        putchar('\n');
        break;

      }

      case 6:{// make (a+b)*(a-b) -> a^2 + b^2
        nc mult;
        mult.var = '*';
        mult.num = 0;
        findEl(root, mult);
        break;
      }

      case 7:{//PRINT CHANGED TREE
        print2D(root);
        putchar('\n');
        break;
      }

      case 8:{
        g = 0;
        break;
      }
      default: {
        printf("Your input is wrong");
        break;
      }

    }
  }
  return 0;
}
