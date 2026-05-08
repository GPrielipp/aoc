#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "../sol.h"

typedef struct range {
  unsigned long min, max;
  struct range *next;
} range_t;

range_t* new_range(range_t* range, unsigned long min, unsigned long max) 
{
  range_t *newrange = malloc(sizeof(*newrange));
  newrange->next = range;
  newrange->min = min;
  newrange->max = max;
  return newrange;
}

void free_range(range_t* range) {
  if(range == NULL) return;
  
  range_t* next = range->next;
  free(range);
  free_range(next);
}

bool check_range(range_t* range, unsigned long val) {
  if(range == NULL) return false;

  if(val >= range->min && val <= range->max) return true;
  else return check_range(range->next, val);
}

// GLOBAL STUFF + SOLUTION

char peek(FILE* file) {
  char c = getc(file);
  if(c != EOF) {
    ungetc(c, file);
  }

  return c;
}

// using a Binary search tree - because I don't know how to write a hash function :)
// Define a structure for a binary tree node
struct Node
{
    unsigned long key;
    struct Node *left, *right;
};

// Function to create a new node with a given value
struct Node *newNodeCreate(unsigned long value)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->key = value;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to search for a node with a specific key in the tree
struct Node *searchNode(struct Node *root, unsigned long target)
{
    if (root == NULL || root->key == target)
        return root;
    if (root->key < target)
        return searchNode(root->right, target);
    return searchNode(root->left, target);
}

// Function to insert a node with a specific value in the tree
struct Node *insertNode(struct Node *node, unsigned long value)
{
    if (node == NULL)
        return newNodeCreate(value);
    if (value < node->key)
        node->left = insertNode(node->left, value);
    else if (value > node->key)
        node->right = insertNode(node->right, value);
    return node;
}

void free_tree(struct Node *node) 
{
  if(node == NULL) return;
  free_tree(node->left);
  free_tree(node->right);
  free(node);
}

void solve(FILE* file, sol_t* sol) {
  range_t *RANGE = NULL;
  //stage 1 -> read the ranges
  unsigned long min, max; 
  while(!feof(file) && peek(file) != '\n') 
  {
    fscanf(file, "%lu-%lu%*1[\n]", &min, &max);
    printf("read: %lu-%lu\n", min, max);
    RANGE = new_range(RANGE, min, max);
  }

  // get rid of the empty line
  getc(file);

  // stage 2 -> check the ranges
  unsigned long item;
  while(!feof(file)) {
    fscanf(file, "%lu", &item);
    
    if(check_range(RANGE, item)) {
      //printf("in range: %d\n", item);
      sol->p1++;
    }
  }

  // stage 3 -> count how many fresh ID's there are
  range_t *iter = RANGE;
  struct Node *set = NULL; 
  while(iter != NULL) {
    for(unsigned long i = iter->min; i <= iter->max; i++) {
      if(i >= ULONG_MAX) { printf("%lu is too big\n", i); }
      else if(searchNode(set, i) == NULL) {
        //printf("%lu not in set\n", i);
        sol->p2++;
        set = insertNode(set, i);
      }
    }
    iter = iter->next;
  }
  free_tree(set);

  free_range(RANGE);
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("usage: %s <input filepath>\n", argv[0]);
    return 1;
  }

  FILE* file = fopen(argv[1], "r");

  if(!file) {
    printf("file '%s' not found.\n", argv[1]);
    exit(1);
  }

  printf("ULONG MAX = %lu\n", ULONG_MAX);

  sol_t* sol = new_sol();
  solve(file, sol);
  fclose(file);
  
  printf("part1: %lld\n", sol->p1);
  printf("part2: %lld\n", sol->p2);
  
  free(sol);

  return 0;
}
