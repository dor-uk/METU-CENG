/*
 * driver.h - Various definitions for the Performance Lab.
 * 
 * DO NOT MODIFY ANYTHING IN THIS FILE
 */
#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdlib.h>

#define RIDX(i,j,n) ((i)*(n)+(j))

typedef struct {
  char *team_name;
    char *ID1, *name1;
    char *ID2, *name2;
} team_t;

typedef void (*lab_test_batched_mm) (int, int*, int*, int *);

typedef void (*lab_test_reflect) (int, int*, int*);


void batched_mm(int, int *,int *, int *);

void reflect(int, int *,int *);


void register_batched_mm_functions(void);

void register_reflect_functions(void);


void add_batched_mm_function(lab_test_batched_mm, char*);

void add_reflect_function(lab_test_reflect, char*);

#endif /* _DEFS_H_ */

