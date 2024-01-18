/*******************************************************************
 * 
 * driver.c - Driver program for CS:APP Performance Lab
 * 
 * In kernels.c, students generate an arbitrary number of point 
 * reflect and batched matrix multiplication test functions, 
 * which they then register with the driver program using the 
 * add_reflect_function() and add_batched_mm_function() functions.
 * 
 * The driver program runs and measures the registered test functions
 * and reports their performance.
 * 
 * Copyright (c) 2002, R. Bryant and D. O'Hallaron, All rights
 * reserved.  May not be used, modified, or copied without permission.
 *
 ********************************************************************/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "fcyc.h"
#include "defs.h"
#include "config.h"

/* Team structure that identifies the students */
extern team_t team;

/* Keep track of a number of different test functions */
#define MAX_BENCHMARKS 100
#define DIM_CNT 5

/* Misc constants */
#define BSIZE 32     /* cache block size in bytes */
#define MAX_DIM 640 /* 512 + 128 */
#define ODD_DIM 96   /* not a power of 2 */

/* This struct characterizes the results for one benchmark test */
typedef struct {
    int func_type;
    union func {
        lab_test_reflect tfunctreflect;
        lab_test_batched_mm tfunctbatched_mm;
    } tfunct; /* The test function */
    double cpes[DIM_CNT]; /* One CPE result for each dimension */
    char *description;    /* ASCII description of the test function */
    unsigned short valid; /* The function is tested if this is non zero */
} bench_t;

/* The range of matrix dimensions that we will be testing */
static int test_dim_batched_mm[] = {32, 64, 128};
static int test_dim_reflect[] = {32, 64, 128, 256, 512};

/* Baseline CPEs (see config.h) */
static double batched_mm_baseline_cpes[] = {B32, B64, B128};
static double reflect_baseline_cpes[] = {R32, R64, R128, R256, R512};

/* These hold the results for all benchmarks */
static bench_t benchmarks_batched_mm[MAX_BENCHMARKS];
static bench_t benchmarks_reflect[MAX_BENCHMARKS];

/* These give the sizes of the above lists */
static int batched_mm_benchmark_count = 0;
static int reflect_benchmark_count = 0;

/*
 * A matrix is a dimxdim matrix of ints stored in a 1D array.  The
 * data array holds three matrixs (the input original, a copy of the original,
 * and the output result array. There is also an additional BSIZE bytes
 * of padding for alignment to cache block boundaries.
 */
static int data[(2 * MAX_DIM * MAX_DIM * MAX_DIM + MAX_DIM * MAX_DIM) + (BSIZE / sizeof(int))];
static int data2[(3 * MAX_DIM * MAX_DIM) + (BSIZE / sizeof(int))];
/* Various matrix pointers */
static int *orig = NULL;         /* original matrix */
static int *orig2 = NULL;        /* second matrix original */
static int *copy_of_orig = NULL; /* copy of original for checking result */
static int *copy_of_orig2 = NULL;/* copy of second original for checking result*/
static int *result1 = NULL;       /* result matrix for point reflect*/
static int *result2 = NULL;       /* result matrix for batched matrix multiplication*/

/* Keep track of the best transpose and col_convert score for grading */
double batched_mm_maxmean = 0.0;
char *batched_mm_maxmean_desc = NULL;

double reflect_maxmean = 0.0;
char *reflect_maxmean_desc = NULL;


/******************** Functions begin *************************/
void add_batched_mm_function(lab_test_batched_mm f, char *description) {
    benchmarks_batched_mm[batched_mm_benchmark_count].func_type = 5;
    benchmarks_batched_mm[batched_mm_benchmark_count].tfunct.tfunctbatched_mm = f;
    benchmarks_batched_mm[batched_mm_benchmark_count].description = description;
    benchmarks_batched_mm[batched_mm_benchmark_count].valid = 0;
    batched_mm_benchmark_count++;
}


void add_reflect_function(lab_test_reflect f, char *description) {
    benchmarks_reflect[reflect_benchmark_count].func_type = 3;
    benchmarks_reflect[reflect_benchmark_count].tfunct.tfunctreflect = f;
    benchmarks_reflect[reflect_benchmark_count].description = description;
    benchmarks_reflect[reflect_benchmark_count].valid = 0;
    reflect_benchmark_count++;
}


/*
 * random_in_interval - Returns random integer in interval [low, high)
 */
static int random_in_interval(int low, int high) {
    int size = high - low;
    return (rand() % size) + low;
}

/*
 * create - creates a dimxdim matrix aligned to a BSIZE byte boundary
 */
static void create(int dim) {
    int i, j, k;

    /* Align the matrixs to BSIZE byte boundaries */
    orig = data;
    orig2 = data2;
    while ((unsigned) orig % BSIZE)
        orig = (int *) (((char *) orig) + 1);
    result1 = orig + dim * dim * dim;
    copy_of_orig = result1 + dim * dim;

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            for (k = 0; k < dim; k++) {
                /* Original data initialized to random ints */
                orig[RIDX(i*dim+j, k, dim)] = random_in_interval(0, 50);


                /* Copy of original data for checking result */ 
                copy_of_orig[RIDX(i*dim+j, k, dim)] = orig[RIDX(i*dim+j, k, dim)];
            }

            /* Result data initialized to all 0 */
            result1[RIDX(i, j, dim)] = 0;

        }
    }

    while ((unsigned) orig2 % BSIZE)
        orig2 = (int *) (((char *) orig2) + 1);
    result2 = orig2 + dim * dim;
    copy_of_orig2 = result2 + dim * dim;

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            /* Original2 matrix initialized to random ints */
            orig2[RIDX(i, j, dim)] = random_in_interval(0, 50);


            /* Copy of original2 matrix for checking result */
            copy_of_orig2[RIDX(i, j, dim)] = orig2[RIDX(i, j, dim)];

            /* Result matrix initialized to 0 */
            result2[RIDX(i, j, dim)] = 0;
        }
    }
}




static int compare_ints(int p1, int p2) {
    return (p1 != p2);
}


/* Make sure the orig array is unchanged */
static int check_orig(int dim) {
    int i, j, k;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            for (k = 0; k < dim; k++)
                if (compare_ints(orig[RIDX(i*dim+j,k,dim)], copy_of_orig[RIDX(i*dim+j,k,dim)])) {
                    printf("\n");
                    printf("Error: Original matrix has been changed!\n");
                    return 1;
                }

    return 0;
}

/* Make sure the orig2 array is unchanged */
static int check_orig2(int dim) {
    int i, j;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            if (compare_ints(orig2[RIDX(i,j,dim)], copy_of_orig2[RIDX(i,j,dim)])) {
                printf("\n");
                printf("Error: Second Original matrix has been changed!\n");
                return 1;
            }

    return 0;
}


/*
 * check_batched_mm - Make sure the batched matrix multiplication actually works.
 * The orig array and orig2 arrays should not  have been tampered with!
 */
static int check_batched_mm(int dim) {
    int err = 0;
    int i, j, k, l;
    int right, wrong;
    int badj, badk;

    /* return 1 if the original matrix has been  changed */
    if (check_orig(dim))
        return 1;
    /* return 1 if the second original matrix has been  changed */
    if (check_orig2(dim))
        return 1;
        
    
    for (j = 0; j < dim; j++) {
        for (k = 0; k < dim; k++) {
            int sum = 0;
            for (i = 0; i < dim; i++){ 
                for (l = 0; l < dim; l++){
                    sum += orig[RIDX(i*dim+j,l,dim)] * orig2[RIDX(l,k,dim)];
                }
            }
            if (compare_ints(sum, result2[RIDX(j,k,dim)])){
                badj = j;
                badk = k;
                wrong = result2[RIDX(j,k,dim)];
                right = sum;
                err++;
            }
        }
    }

    if (err) {
        printf("\n");
        printf("ERROR: Dimension=%d, %d errors\n", dim, err);
        printf("You have dst[%d][%d] = %d\n",
               badj, badk, wrong);
        printf("It should be dst[%d][%d] = %d\n",
               badj, badk, right);
    }
    return err;
}


/*
 * check_reflect - Make sure the point reflection actually works.
 * The orig array should not have been tampered with!
 */
static int check_reflect(int dim) {
    int err = 0;
    int i, j;
    int right, wrong;
    int badi, badj;

    /* return 1 if the original matrix has been  changed */
    if (check_orig2(dim))
        return 1;
    
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
	    if (compare_ints(orig2[RIDX(i,j,dim)], result1[RIDX(dim-1-i,dim-1-j,dim)])) {
		err++;
		badi = dim-1-i;
		badj = dim-1-j;
		right = orig2[RIDX(i,j,dim)];
		wrong = result1[RIDX(dim-1-i,dim-1-j,dim)];
	    }
	}
    }

    if (err) {
        printf("\n");
        printf("ERROR: Dimension=%d, %d errors\n", dim, err);
        printf("You have dst[%d][%d] = %d\n",
               badi, badj, wrong);
        printf("It should be dst[%d][%d] = %d\n",
               badi, badj, right);
    }
    return err;
}


void func_wrapper(void *arglist[]) {
    int *src, *src2, *dst1;
    int *dst2;
    int mydim;
    lab_test_reflect f3;
    lab_test_batched_mm f5;
    int type;
    type = *((int *) arglist[0]);
    if (type == 3) {
        f3 = (lab_test_reflect) arglist[1];
        mydim = *((int *) arglist[2]);
        src = (int *) arglist[3];
        dst1 = (int *) arglist[4];
        (*f3)(mydim, src, dst1);

    } else if (type == 5) {
        f5 = (lab_test_batched_mm) arglist[1];
        mydim = *((int *) arglist[2]);
        src = (int *) arglist[3];
        src2 = (int *) arglist[4];
        dst2 = (int *) arglist[5];
        (*f5)(mydim, src, src2, dst2);

    }
}

/*batched_mm benchmark*/
void run_batched_mm_benchmark(int idx, int dim) {
    benchmarks_batched_mm[idx].tfunct.tfunctbatched_mm(dim, orig, orig2, result2);
}

void test_batched_mm(int bench_index) {

    int i;
    int test_num;
    char *description = benchmarks_batched_mm[bench_index].description;
    for (test_num = 0; test_num < 3; test_num++) {
        int dim;
        /* Check for odd dimension */
        create(ODD_DIM);
        run_batched_mm_benchmark(bench_index, ODD_DIM);
        if (check_batched_mm(ODD_DIM)) {
            printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
                   benchmarks_batched_mm[bench_index].description, ODD_DIM);
            return;
        }

        /* Create a test matrix of the required dimension */
        dim = test_dim_batched_mm[test_num];
        create(dim);
#ifdef DEBUG
        printf("DEBUG: Running benchmark \"%s\"\n", benchmarks_batched_mm[bench_index].description);
#endif
        /* Check that the code works */
        run_batched_mm_benchmark(bench_index, dim);
        if (check_batched_mm(dim)) {
            printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
                   benchmarks_batched_mm[bench_index].description, dim);
            return;
        }

        /* Measure CPE */
        {
            double num_cycles, cpe;
            int tmpdim = dim;
            void *arglist[6];
            double dimension = (double) dim;
            double work = dimension * dimension;
#ifdef DEBUG
            printf("DEBUG: dimension=%.1f\n",dimension);
            printf("DEBUG: work=%.1f\n",work);
#endif
            int tmp_type = 5;
            arglist[0] = &tmp_type;
            arglist[1] = (void *) benchmarks_batched_mm[bench_index].tfunct.tfunctbatched_mm;
            arglist[2] = (void *) &tmpdim;
            arglist[3] = (void *) orig;
            arglist[4] = (void *) orig2;
            arglist[5] = (void *) result2;

            create(dim);
            num_cycles = 0;
            num_cycles = fcyc_v((test_funct_v) &func_wrapper, arglist);
            cpe = num_cycles / work;
            benchmarks_batched_mm[bench_index].cpes[test_num] = cpe;
        }
    }


    /*
     * Print results as a table
     */
    printf("Batched MM: Version = %s:\n", description);
    printf("Dim\t");
    for (i = 0; i < 3; i++)
        printf("\t%d", test_dim_batched_mm[i]);
    printf("\tMean\n");

    printf("Your CPEs");
    for (i = 0; i < 3; i++) {
        printf("\t%.1f", benchmarks_batched_mm[bench_index].cpes[i]);
    }
    printf("\n");

    printf("Baseline CPEs");
    for (i = 0; i < 3; i++) {
        printf("\t%.1f", batched_mm_baseline_cpes[i]);
    }
    printf("\n");

    /* Compute Speedup */
    {
        double prod, ratio, mean;
        prod = 1.0; /* Geometric mean */
        printf("Speedup\t");
        for (i = 0; i < 3; i++) {
            if (benchmarks_batched_mm[bench_index].cpes[i] > 0.0) {
                ratio = batched_mm_baseline_cpes[i] /
                        benchmarks_batched_mm[bench_index].cpes[i];
            } else {
                printf("Fatal Error: Non-positive CPE value...\n");
                exit(EXIT_FAILURE);
            }
            prod *= ratio;
            printf("\t%.1f", ratio);
        }

        /* Geometric mean */
        mean = pow(prod, 1.0 / (double) 3);
        printf("\t%.1f", mean);
        printf("\n\n");
        if (mean > batched_mm_maxmean) {
            batched_mm_maxmean = mean;
            batched_mm_maxmean_desc = benchmarks_batched_mm[bench_index].description;
        }
    }


#ifdef DEBUG
    fflush(stdout);
#endif
    return;


}

/*batched_mm benchmark end*/


void run_reflect_benchmark(int idx, int dim) {
    benchmarks_reflect[idx].tfunct.tfunctreflect(dim, orig2, result1);
}

void test_reflect(int bench_index) {

    int i;
    int test_num;
    char *description = benchmarks_reflect[bench_index].description;
    for (test_num = 0; test_num < DIM_CNT; test_num++) {
        int dim;
        /* Check for odd dimension */
        create(ODD_DIM);
        run_reflect_benchmark(bench_index, ODD_DIM);
        if (check_reflect(ODD_DIM)) {
            printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
                   benchmarks_reflect[bench_index].description, ODD_DIM);
            return;
        }

        /* Create a test matrix of the required dimension */
        dim = test_dim_reflect[test_num];
        create(dim);
#ifdef DEBUG
        printf("DEBUG: Running benchmark \"%s\"\n", benchmarks_multip[bench_index].description);
#endif
        /* Check that the code works */
        run_reflect_benchmark(bench_index, dim);
        if (check_reflect(dim)) {
            printf("Benchmark \"%s\" failed correctness check for dimension %d.\n",
                   benchmarks_reflect[bench_index].description, dim);
            return;
        }

        /* Measure CPE */
        {
            double num_cycles, cpe;
            int tmpdim = dim;
            void *arglist[5];
            double dimension = (double) dim;
            double work = dimension * dimension;
#ifdef DEBUG
            printf("DEBUG: dimension=%.1f\n",dimension);
            printf("DEBUG: work=%.1f\n",work);
#endif
            int tmp_type = 3;
            arglist[0] = &tmp_type;
            arglist[1] = (void *) benchmarks_reflect[bench_index].tfunct.tfunctreflect;
            arglist[2] = (void *) &tmpdim;
            arglist[3] = (void *) orig2;
            arglist[4] = (void *) result1;

            create(dim);
            num_cycles = 0;
            num_cycles = fcyc_v((test_funct_v) &func_wrapper, arglist);
            cpe = num_cycles / work;
            benchmarks_reflect[bench_index].cpes[test_num] = cpe;
        }
    }


    /*
     * Print results as a table
     */
    printf("Point Reflect: Version = %s:\n", description);
    printf("Dim\t");
    for (i = 0; i < DIM_CNT; i++)
        printf("\t%d", test_dim_reflect[i]);
    printf("\tMean\n");

    printf("Your CPEs");
    for (i = 0; i < DIM_CNT; i++) {
        printf("\t%.1f", benchmarks_reflect[bench_index].cpes[i]);
    }
    printf("\n");

    printf("Baseline CPEs");
    for (i = 0; i < DIM_CNT; i++) {
        printf("\t%.1f", reflect_baseline_cpes[i]);
    }
    printf("\n");

    /* Compute Speedup */
    {
        double prod, ratio, mean;
        prod = 1.0; /* Geometric mean */
        printf("Speedup\t");
        for (i = 0; i < DIM_CNT; i++) {
            if (benchmarks_reflect[bench_index].cpes[i] > 0.0) {
                ratio = reflect_baseline_cpes[i] /
                        benchmarks_reflect[bench_index].cpes[i];
            } else {
                printf("Fatal Error: Non-positive CPE value...\n");
                exit(EXIT_FAILURE);
            }
            prod *= ratio;
            printf("\t%.1f", ratio);
        }

        /* Geometric mean */
        mean = pow(prod, 1.0 / (double) DIM_CNT);
        printf("\t%.1f", mean);
        printf("\n\n");
        if (mean > reflect_maxmean) {
            reflect_maxmean = mean;
            reflect_maxmean_desc = benchmarks_reflect[bench_index].description;
        }
    }


#ifdef DEBUG
    fflush(stdout);
#endif
    return;


}


void usage(char *progname) {
    fprintf(stderr, "Usage: %s [-hqg] [-f <func_file>] [-d <dump_file>]\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -h         Print this message\n");
    fprintf(stderr, "  -q         Quit after dumping (use with -d )\n");
    fprintf(stderr, "  -g         Autograder mode: checks only reflect() and batched_mm()\n");
    fprintf(stderr, "  -f <file>  Get test function names from dump file <file>\n");
    fprintf(stderr, "  -d <file>  Emit a dump file <file> for later use with -f\n");
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
    int i;
    int quit_after_dump = 0;
    int skip_teamname_check = 0;
    int autograder = 0;
    int seed = 1729;
    char c = '0';
    char *bench_func_file = NULL;
    char *func_dump_file = NULL;

    /* register all the defined functions */
    register_batched_mm_functions();
    register_reflect_functions();

    /* parse command line args */
    while ((c = getopt(argc, argv, "tgqf:d:s:h")) != -1)
        switch (c) {

            case 't': /* skip ID name check (hidden flag) */
                skip_teamname_check = 1;
                break;

            case 's': /* seed for random number generator (hidden flag) */
                seed = atoi(optarg);
                break;

            case 'g': /* autograder mode (checks only transpose() and col_convert()) */
                autograder = 1;
                break;

            case 'q':
                quit_after_dump = 1;
                break;

            case 'f': /* get names of benchmark functions from this file */
                bench_func_file = strdup(optarg);
                break;

            case 'd': /* dump names of benchmark functions to this file */
                func_dump_file = strdup(optarg);
                {
                    int i;
                    FILE *fp = fopen(func_dump_file, "w");

                    if (fp == NULL) {
                        printf("Can't open file %s\n", func_dump_file);
                        exit(-5);
                    }
                    for (i = 0; i < batched_mm_benchmark_count; i++) {
                        fprintf(fp, "R:%s\n", benchmarks_batched_mm[i].description);
                    }
                    for (i = 0; i < reflect_benchmark_count; i++) {
                        fprintf(fp, "R:%s\n", benchmarks_reflect[i].description);
                    }
                    fclose(fp);
                }
                break;

            case 'h': /* print help message */
                usage(argv[0]);

            default: /* unrecognized argument */
                usage(argv[0]);
        }

    if (quit_after_dump)
        exit(EXIT_SUCCESS);

    /* Print ID info */
    if (!skip_teamname_check) {
        if (strcmp("eXXXXXX", team.ID1) == 0) {
            printf("%s: Please fill in your ID in kernels.c.\n", argv[0]);
            exit(1);
        }
        printf("Team Name: %s\n", team.team_name);
        printf("ID1: %s\n", team.ID1);
        printf("Name1: %s\n", team.name1);
        if (*team.name2 || *team.ID2) {
            printf("ID2: %s\n", team.ID2);
            printf("Name2: %s\n", team.name2);
        }

        printf("\n");
    }

    srand(seed);

    /*
     * If we are running in autograder mode, we will only test
     * the batched_mm() and reflect() functions.
     */
    if (autograder) {
        batched_mm_benchmark_count = 1;
        reflect_benchmark_count = 1;

        benchmarks_batched_mm[0].tfunct.tfunctbatched_mm = batched_mm;
        benchmarks_batched_mm[0].description = "batched_mm() function";
        benchmarks_batched_mm[0].valid = 1;

        benchmarks_reflect[0].tfunct.tfunctreflect = reflect;
        benchmarks_reflect[0].description = "reflect() function";
        benchmarks_reflect[0].valid = 1;
    }

        /*
         * If the user specified a file name using -f, then use
         * the file to determine the versions of reflect and batched_mm to test
         */
    else if (bench_func_file != NULL) {

        char flag;
        char func_line[256];
        FILE *fp = fopen(bench_func_file, "r");

        if (fp == NULL) {
            printf("Can't open file %s\n", bench_func_file);
            exit(-5);
        }

        while (func_line == fgets(func_line, 256, fp)) {
            char *func_name = func_line;
            char **strptr = &func_name;
            char *token = strsep(strptr, ":");
            flag = token[0];
            func_name = strsep(strptr, "\n");
#ifdef DEBUG
            printf("Function Description is %s\n",func_name);
#endif

            if (flag == 'C') {
                for (i = 0; i < batched_mm_benchmark_count; i++) {
                    if (strcmp(benchmarks_batched_mm[i].description, func_name) == 0)
                        benchmarks_batched_mm[i].valid = 1;
                }
            }

            if (flag == 'M') {
                for (i = 0; i < reflect_benchmark_count; i++) {
                    if (strcmp(benchmarks_reflect[i].description, func_name) == 0)
                        benchmarks_reflect[i].valid = 1;
                }
            }


        }

        fclose(fp);
    }

        /*
         * If the user didn't specify a dump file using -f, then
         * test all of the functions
         */
    else { /* set all valid flags to 1 */

        for (i = 0; i < batched_mm_benchmark_count; i++)
            benchmarks_batched_mm[i].valid = 1;

        for (i = 0; i < reflect_benchmark_count; i++)
            benchmarks_reflect[i].valid = 1;

    }

    /* Set measurement (fcyc) parameters */
    set_fcyc_cache_size(1 << 14); /* 16 KB cache size */
    set_fcyc_clear_cache(1); /* clear the cache before each measurement */
    set_fcyc_compensate(1); /* try to compensate for timer overhead */


    for (i = 0; i < batched_mm_benchmark_count; i++) {
        if (benchmarks_batched_mm[i].valid)
            test_batched_mm(i);
    }

    for (i = 0; i < reflect_benchmark_count; i++) {
        if (benchmarks_reflect[i].valid)
            test_reflect(i);
    }


    if (autograder) {
        printf("\nbestscores:%.1f:%.1f:\n", reflect_maxmean, batched_mm_maxmean);
    } else {
        printf("Summary of Your Best Scores:\n");
        printf("  Point Reflect: %3.1f (%s)\n", reflect_maxmean, reflect_maxmean_desc);
        printf("  Batched MM: %3.1f (%s)\n", batched_mm_maxmean, batched_mm_maxmean_desc);
    }

    return 0;
}














