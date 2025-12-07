#ifndef SOL_H
#define SOL_H

#include <stdlib.h>

typedef struct {
  long long p1;
  long long p2;
} sol_t;

sol_t* new_sol() {
  sol_t* sol = malloc(sizeof(*sol));
  sol->p1 = 0;
  sol->p2 = 0;
  return sol;
}

#endif//SOL_H
