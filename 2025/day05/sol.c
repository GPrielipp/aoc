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

void solve(FILE* file, sol_t* sol) {
  range_t *RANGE = NULL;
  //stage 1 -> read the ranges
  unsigned long min, max; 
  while(!feof(file) && peek(file) != '\n') 
  {
    fscanf(file, "%lu-%lu%*1[\n]", &min, &max);
    /*printf("read: %lu-%lu\n", min, max);*/
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
  int merge_count = 0; 
  int prev_merge_count = -1;
  while(merge_count != prev_merge_count) {
    prev_merge_count = merge_count;
    merge_count = 0;

    range_t *i1 = RANGE;
    range_t *i2 = RANGE->next;

    // new ranges
    range_t* newRange = NULL;
    while(i1 != NULL) {
      unsigned long min = i1->min, max = i1->max;
      while(i2 != NULL) {
        if((i2->min >= min && i2->min <= max) ||
            (i2->max >= min && i2->max <= max))
        {
          min = i2->min < min ? i2->min : min;
          max = i2->max > max ? i2->max : max;
        }

        i2 = i2->next;
      } 

      if(!check_range(newRange, min) || !check_range(newRange, max))
      {
        newRange = new_range(newRange, min, max); 
        merge_count++;
      }

      i1 = i1->next;
    }
    free_range(RANGE);
    RANGE = newRange; 
  } 

  // count the ID's
  range_t *iter = RANGE;
  while(iter != NULL)
  {
    printf("new range: %lu - %lu\n", iter->min, iter->max);
    sol->p2 += iter->max - iter->min + 1;
    iter = iter->next;
  }

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

  /*printf("ULONG MAX = %lu\n", ULONG_MAX);*/

  sol_t* sol = new_sol();
  solve(file, sol);
  fclose(file);

  printf("part1: %lld\n", sol->p1);
  printf("part2: %lld\n", sol->p2);

  free(sol);

  return 0;
}
