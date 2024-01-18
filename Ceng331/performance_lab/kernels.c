/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/*
 * Please fill in the following team_t struct
 */
team_t team = {
        "McQueen & Sally",    /* Team Name */

        "e2522225",    /* First student ID */
        "Doruk Berke Yurtsızoğlu",    /* First student name */

        "e2448777",        /* Second student ID */
        "Ayşegül Öztürk"         /* Second student name */

};


/*******************************************************
 * BATCHED MATRIX MULTIPLICATION \W SUM REDUCTION KERNEL
 *******************************************************/

/*********************************************************************************
 * Your different versions of the batched matrix multiplication functions go here
 *********************************************************************************/

/*
 * naive_batched_mm - The naive baseline version of batched matrix multiplication
 */
char naive_batched_mm_descr[] = "naive_batched_mm: Naive baseline implementation";
void naive_batched_mm(int dim, int *b_mat, int *mat, int *dst) {
    int i,j,k,l;

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            for (k = 0; k < dim; k++) {
            	if (i == 0){
            	    dst[RIDX(j, k, dim)] = 0;
            	}
            	for (l = 0; l < dim; l++){
                    dst[RIDX(j, k, dim)] += b_mat[RIDX(i*dim+j, l, dim)] * mat[RIDX(l, k, dim)];
                }
            }
        }
    }
}

/*
 * batched_mm - Your current working version of batched matrix multiplication
 * IMPORTANT: This is the version you will be graded on
 */
char batched_mm_descr[] = "Batched MM with sum reduction: Current working version";
void batched_mm(int dim, int *b_mat, int *mat, int *dst) {
    int i,j,k,l;
    int dimSq = dim*dim;
    int B = 1024;
    //int new_mat[dimSq];
    int *new_matrix = malloc(sizeof(int)*dimSq);
    for (int i = 0; i < dimSq; i += B) {
        for (int j = 0; j < B; j++) {
            new_matrix[i + j] = 0;
        }
    }

    int dim2 = 2 * dim;
    int dim3 = 3 * dim;
    int dim4 = 4 * dim;
    int dim5 = 5 * dim;
    int dim6 = 6 * dim;
    int dim7 = 7 * dim;

    int dim8 = 8 * dim;
    int dim9 = 9 * dim;
    int dim10 = 10 * dim;
    int dim11 = 11 * dim;
    int dim12 = 12 * dim;
    int dim13 = 13 * dim;
    int dim14 = 14 * dim;
    int dim15 = 15 * dim;

    int dim16 = 16 * dim;
    int dim17 = 17 * dim;
    int dim18 = 18 * dim;
    int dim19 = 19 * dim;
    int dim20 = 20 * dim;
    int dim21 = 21 * dim;
    int dim22 = 22 * dim;
    int dim23 = 23 * dim;

    int dim24 = 24 * dim;
    int dim25 = 25 * dim;
    int dim26 = 26 * dim;
    int dim27 = 27 * dim;
    int dim28 = 28 * dim;
    int dim29 = 29 * dim;
    int dim30 = 30 * dim;
    int dim31 = 31 * dim;

    int var_idimq = 0;
    int var_jdim = 0;
    for (i = 0; i < dim; i++) {
        //int var_idimq;
        var_idimq = i * dimSq;
        for (j = 0; j < dim; j++) {
            var_jdim = dim*j;
            for(l=0; l<dim; l+=32) {


                new_matrix[var_jdim + l] += b_mat[var_idimq + var_jdim + l];
                new_matrix[var_jdim + l + 1] += b_mat[var_idimq + var_jdim + l + 1];
                new_matrix[var_jdim + l + 2] += b_mat[var_idimq + var_jdim + l + 2];
                new_matrix[var_jdim + l + 3] += b_mat[var_idimq + var_jdim + l + 3];
                new_matrix[var_jdim + l + 4] += b_mat[var_idimq + var_jdim + l + 4];
                new_matrix[var_jdim + l + 5] += b_mat[var_idimq + var_jdim + l + 5];
                new_matrix[var_jdim + l + 6] += b_mat[var_idimq + var_jdim + l + 6];
                new_matrix[var_jdim + l + 7] += b_mat[var_idimq + var_jdim + l + 7];

                new_matrix[var_jdim + l + 8] += b_mat[var_idimq + var_jdim + l + 8];
                new_matrix[var_jdim + l + 9] += b_mat[var_idimq + var_jdim + l + 9];
                new_matrix[var_jdim + l + 10] += b_mat[var_idimq + var_jdim + l + 10];
                new_matrix[var_jdim + l + 11] += b_mat[var_idimq + var_jdim + l + 11];
                new_matrix[var_jdim + l + 12] += b_mat[var_idimq + var_jdim + l + 12];
                new_matrix[var_jdim + l + 14] += b_mat[var_idimq + var_jdim + l + 14];
                new_matrix[var_jdim + l + 13] += b_mat[var_idimq + var_jdim + l + 13];
                new_matrix[var_jdim + l + 15] += b_mat[var_idimq + var_jdim + l + 15];

                new_matrix[var_jdim + l + 16] += b_mat[var_idimq + var_jdim + l + 16];
                new_matrix[var_jdim + l + 17] += b_mat[var_idimq + var_jdim + l + 17];
                new_matrix[var_jdim + l + 18] += b_mat[var_idimq + var_jdim + l + 18];
                new_matrix[var_jdim + l + 19] += b_mat[var_idimq + var_jdim + l + 19];
                new_matrix[var_jdim + l + 20] += b_mat[var_idimq + var_jdim + l + 20];
                new_matrix[var_jdim + l + 21] += b_mat[var_idimq + var_jdim + l + 21];
                new_matrix[var_jdim + l + 22] += b_mat[var_idimq + var_jdim + l + 22];
                new_matrix[var_jdim + l + 23] += b_mat[var_idimq + var_jdim + l + 23];

                new_matrix[var_jdim + l + 24] += b_mat[var_idimq + var_jdim + l + 24];
                new_matrix[var_jdim + l + 25] += b_mat[var_idimq + var_jdim + l + 25];
                new_matrix[var_jdim + l + 26] += b_mat[var_idimq + var_jdim + l + 26];
                new_matrix[var_jdim + l + 27] += b_mat[var_idimq + var_jdim + l + 27];
                new_matrix[var_jdim + l + 28] += b_mat[var_idimq + var_jdim + l + 28];
                new_matrix[var_jdim + l + 29] += b_mat[var_idimq + var_jdim + l + 29];
                new_matrix[var_jdim + l + 30] += b_mat[var_idimq + var_jdim + l + 30];
                new_matrix[var_jdim + l + 31] += b_mat[var_idimq + var_jdim + l + 31];

            }

        }
    }
    /*int j1 = 0, k1 = 0, l1 = 0;
    int block = 32;
    int bj = 0, bl = 0, bk = 0;
    int l_dim = 0, var_jldim = 0, var_jkdim = 0, lk_dim = 0;


    for(j = 0; j < dim; j += block){
      bj = block + j;

      for (l = 0; l < dim; l += block){
        bl = block + l;

        for (k = 0; k < dim; k += block){
          bk = block + k;

          for(j1 = j; j1 < bj; j1++){
            var_jdim = dim * j1;

            for (l1 = l; l1 < bl; l1++){
              l_dim = l1 * dim;
              var_jldim = var_jdim + l1;

              for (k1 = k; k1 < bk; k1+=block){
                var_jkdim = var_jdim + k1;
                lk_dim = l_dim + k1;

                dst[var_jkdim] += new_mat[var_jldim] * mat[lk_dim];
                dst[var_jkdim + 1] += new_mat[var_jldim] * mat[lk_dim + 1];
                dst[var_jkdim + 2] += new_mat[var_jldim] * mat[lk_dim + 2];
                dst[var_jkdim + 3] += new_mat[var_jldim] * mat[lk_dim + 3];
                dst[var_jkdim + 4] += new_mat[var_jldim] * mat[lk_dim + 4];
                dst[var_jkdim + 5] += new_mat[var_jldim] * mat[lk_dim + 5];
                dst[var_jkdim + 6] += new_mat[var_jldim] * mat[lk_dim + 6];
                dst[var_jkdim + 7] += new_mat[var_jldim] * mat[lk_dim + 7];
                dst[var_jkdim + 8] += new_mat[var_jldim] * mat[lk_dim + 8];
                dst[var_jkdim + 9] += new_mat[var_jldim] * mat[lk_dim + 9];
                dst[var_jkdim + 10] += new_mat[var_jldim] * mat[lk_dim + 10];
                dst[var_jkdim + 11] += new_mat[var_jldim] * mat[lk_dim + 11];
                dst[var_jkdim + 12] += new_mat[var_jldim] * mat[lk_dim + 12];
                dst[var_jkdim + 13] += new_mat[var_jldim] * mat[lk_dim + 13];
                dst[var_jkdim + 14] += new_mat[var_jldim] * mat[lk_dim + 14];
                dst[var_jkdim + 15] += new_mat[var_jldim] * mat[lk_dim + 15];
                dst[var_jkdim + 16] += new_mat[var_jldim] * mat[lk_dim + 16];
                dst[var_jkdim + 17] += new_mat[var_jldim] * mat[lk_dim + 17];
                dst[var_jkdim + 18] += new_mat[var_jldim] * mat[lk_dim + 18];
                dst[var_jkdim + 19] += new_mat[var_jldim] * mat[lk_dim + 19];
                dst[var_jkdim + 20] += new_mat[var_jldim] * mat[lk_dim + 20];
                dst[var_jkdim + 21] += new_mat[var_jldim] * mat[lk_dim + 21];
                dst[var_jkdim + 22] += new_mat[var_jldim] * mat[lk_dim + 22];
                dst[var_jkdim + 23] += new_mat[var_jldim] * mat[lk_dim + 23];
                dst[var_jkdim + 24] += new_mat[var_jldim] * mat[lk_dim + 24];
                dst[var_jkdim + 25] += new_mat[var_jldim] * mat[lk_dim + 25];
                dst[var_jkdim + 26] += new_mat[var_jldim] * mat[lk_dim + 26];
                dst[var_jkdim + 27] += new_mat[var_jldim] * mat[lk_dim + 27];
                dst[var_jkdim + 28] += new_mat[var_jldim] * mat[lk_dim + 28];
                dst[var_jkdim + 29] += new_mat[var_jldim] * mat[lk_dim + 29];
                dst[var_jkdim + 30] += new_mat[var_jldim] * mat[lk_dim + 30];
                dst[var_jkdim + 31] += new_mat[var_jldim] * mat[lk_dim + 31];
              }
            }
            //var_jdim += dim;
          }
        }
      }
    }*/
    int sum = 0;
    int idx_new_mat = 0, idx_mat = 0, var_jkdim = 0;


    for (j = 0; j < dim; j++) {
        var_jdim = dim * j;

        for (l = 0; l < dim; l += 32) {
            for (k = 0; k < dim; k++) {
                sum = 0;

                idx_new_mat = var_jdim + l;
                idx_mat = dim * l + k;

                sum += new_matrix[idx_new_mat] * mat[idx_mat];
                sum += new_matrix[idx_new_mat + 1] * mat[idx_mat + dim];
                sum += new_matrix[idx_new_mat + 2] * mat[idx_mat + dim2];
                sum += new_matrix[idx_new_mat + 3] * mat[idx_mat + dim3];
                sum += new_matrix[idx_new_mat + 4] * mat[idx_mat + dim4];
                sum += new_matrix[idx_new_mat + 5] * mat[idx_mat + dim5];
                sum += new_matrix[idx_new_mat + 6] * mat[idx_mat + dim6];
                sum += new_matrix[idx_new_mat + 7] * mat[idx_mat + dim7];
                sum += new_matrix[idx_new_mat + 8] * mat[idx_mat + dim8];
                sum += new_matrix[idx_new_mat + 9] * mat[idx_mat + dim9];
                sum += new_matrix[idx_new_mat + 10] * mat[idx_mat + dim10];
                sum += new_matrix[idx_new_mat + 11] * mat[idx_mat + dim11];
                sum += new_matrix[idx_new_mat + 12] * mat[idx_mat + dim12];
                sum += new_matrix[idx_new_mat + 13] * mat[idx_mat + dim13];
                sum += new_matrix[idx_new_mat + 14] * mat[idx_mat + dim14];
                sum += new_matrix[idx_new_mat + 15] * mat[idx_mat + dim15];
                sum += new_matrix[idx_new_mat + 16] * mat[idx_mat + dim16];
                sum += new_matrix[idx_new_mat + 17] * mat[idx_mat + dim17];
                sum += new_matrix[idx_new_mat + 18] * mat[idx_mat + dim18];
                sum += new_matrix[idx_new_mat + 19] * mat[idx_mat + dim19];
                sum += new_matrix[idx_new_mat + 20] * mat[idx_mat + dim20];
                sum += new_matrix[idx_new_mat + 21] * mat[idx_mat + dim21];
                sum += new_matrix[idx_new_mat + 22] * mat[idx_mat + dim22];
                sum += new_matrix[idx_new_mat + 23] * mat[idx_mat + dim23];
                sum += new_matrix[idx_new_mat + 24] * mat[idx_mat + dim24];
                sum += new_matrix[idx_new_mat + 25] * mat[idx_mat + dim25];
                sum += new_matrix[idx_new_mat + 26] * mat[idx_mat + dim26];
                sum += new_matrix[idx_new_mat + 27] * mat[idx_mat + dim27];
                sum += new_matrix[idx_new_mat + 28] * mat[idx_mat + dim28];
                sum += new_matrix[idx_new_mat + 29] * mat[idx_mat + dim29];
                sum += new_matrix[idx_new_mat + 30] * mat[idx_mat + dim30];
                sum += new_matrix[idx_new_mat + 31] * mat[idx_mat + dim31];

                var_jkdim = var_jdim + k;

                if (i == 0) {
                    dst[var_jkdim] = sum;
                } else {
                    dst[var_jkdim] += sum;
                }
            }
        }
    }






    free(new_matrix);
        /*for(i=0; i<dim; i++) {
            for(j=0; j<dim; j++) {
                for(l=0; l<dim; l++) {

                    if(i==0) {
                        new_mat[RIDX(j,l,dim)] = b_mat[RIDX(i*dim+j,l,dim)];
                    }
                    else {
                        new_mat[RIDX(j,l,dim)] += b_mat[RIDX(i*dim+j,l,dim)];
                    }
                }
            }
        }

        for (j = 0; j < dim; j++) {
            for (k = 0; k < dim; k++) {
                if (i == 0){
                    dst[RIDX(j, k, dim)] = 0;
                }
                for (l = 0; l < dim; l++){
                    dst[RIDX(j, k, dim)] += new_mat[RIDX(j, l, dim)] * mat[RIDX(l, k, dim)];
                }
            }
        }*/

}

/*********************************************************************
 * register_batched_mm_functions - Register all of your different versions
 *     of the batched matrix multiplication functions  with the driver by calling the
 *     add_batched_mm_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_batched_mm_functions() {
    add_batched_mm_function(&naive_batched_mm, naive_batched_mm_descr);
    add_batched_mm_function(&batched_mm, batched_mm_descr);
    /* ... Register additional test functions here */
}

//var1 = j*dim + l;


/************************
 * POINT REFLECTION KERNEL
 ************************/

/*********************************************************
 * Your different versions of the point reflection go here
 *********************************************************/

/*
 * naive_reflect - The naive baseline version of point reflection
 */
char naive_reflect_descr[] = "Naive Point Reflection: Naive baseline implementation";
void naive_reflect(int dim, int *src, int *dst) {
    int i, j;

    for (i = 0; i < dim; i++) {
	for (j = 0; j < dim; j++) {
	    dst[RIDX(dim-1-i, dim-1-j, dim)] = src[RIDX(i, j, dim)];
	}
    }
}


/*
 * reflect - Your current working version of reflect
 * IMPORTANT: This is the version you will be graded on
 */
char reflect_descr[] = "Point Reflection: Current working version";
void reflect(int dim, int *src, int *dst)
{

  int dimSq = dim * dim;
  int srcIdx = dimSq - 1;
  int i = 0;
  for (; i < dimSq; i=i+32) {
      dst[i] = src[srcIdx--];
      dst[i+1] = src[srcIdx--];
      dst[i+2] = src[srcIdx--];
      dst[i+3] = src[srcIdx--];
      dst[i+4] = src[srcIdx--];
      dst[i+5] = src[srcIdx--];
      dst[i+6] = src[srcIdx--];
      dst[i+7] = src[srcIdx--];
      dst[i+8] = src[srcIdx--];
      dst[i+9] = src[srcIdx--];
      dst[i+10] = src[srcIdx--];
      dst[i+11] = src[srcIdx--];
      dst[i+12] = src[srcIdx--];
      dst[i+13] = src[srcIdx--];
      dst[i+14] = src[srcIdx--];
      dst[i+15] = src[srcIdx--];
      dst[i+16] = src[srcIdx--];
      dst[i+17] = src[srcIdx--];
      dst[i+18] = src[srcIdx--];
      dst[i+19] = src[srcIdx--];
      dst[i+20] = src[srcIdx--];
      dst[i+21] = src[srcIdx--];
      dst[i+22] = src[srcIdx--];
      dst[i+23] = src[srcIdx--];
      dst[i+24] = src[srcIdx--];
      dst[i+25] = src[srcIdx--];
      dst[i+26] = src[srcIdx--];
      dst[i+27] = src[srcIdx--];
      dst[i+28] = src[srcIdx--];
      dst[i+29] = src[srcIdx--];
      dst[i+30] = src[srcIdx--];
      dst[i+31] = src[srcIdx--];
  }

}

/******************************************************************************
 * register_reflect_functions - Register all of your different versions
 *     of the reflect with the driver by calling the
 *     add_reflect_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 ******************************************************************************/

void register_reflect_functions() {
    add_reflect_function(&naive_reflect, naive_reflect_descr);
    add_reflect_function(&reflect, reflect_descr);
    /* ... Register additional test functions here */
}
