/**
 * 
 * 
 * 
 * Marios Pakas
 * Parallel and Distributed Systems Exercise 4
 * 
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "mmio.h"
#include "coo2csc.h"
#include "string.h"
#include <cilk/cilk.h>
#include <pthread.h>
#include <cilk/cilk_api.h>
#include <time.h>

void readfile_stepone(
    FILE *f,
    uint32_t *m, 
    uint32_t *n, 
    uint32_t *nnz_pointer,
    int *i, 
    int *j,
    int binary    
    )
    {

    int ret_code;
    MM_typecode matcode;
    
    if (mm_read_banner(f, &matcode) != 0)
    {
        printf("Could not process Matrix Market banner.\n");
        exit(1);
    }


    /*  This is how one can screen matrix types if their application */
    /*  only supports a subset of the Matrix Market data types.      */

    if (mm_is_complex(matcode) && mm_is_matrix(matcode) && 
            mm_is_sparse(matcode) )
    {
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
        exit(1);
    }

    /* find out size of sparse matrix .... */

    if ((ret_code = mm_read_mtx_crd_size(f, m, n, nnz_pointer)) !=0)
        exit(1);
}

void readfile_steptwo(
    FILE *f,
    uint32_t *m, 
    uint32_t *n, 
    uint32_t *nnz_pointer,
    int *I, 
    int *J,
    double * val,
    int binary    
    )
    {

    uint32_t M = *m;
    uint32_t N = *n;
    uint32_t nnz = *nnz_pointer;
    
    /* Depending on the second argument of the main call our original matrix may be binary or non binary so we read the file accordingly */
    switch (binary) 
    {
    case 0:
        /* use this if the source file is not binary */
        for (uint32_t i=0; i<nnz; i++)
        {
            /* I is for the rows and J for the columns */
            fscanf(f, "%d %d %lg\n", &I[i], &J[i], &val[i]);
            I[i]--;  /* adjust from 1-based to 0-based */
            J[i]--;
        }
        break;

    case 1:
        /* use this if the source file is binary */
        for (uint32_t i=0; i<nnz; i++)
        {
            /* I is for the rows and J for the columns */
            fscanf(f, "%d %d \n", &I[i], &J[i]);
            I[i]--;  /* adjust from 1-based to 0-based */
            J[i]--;
        }
        break;
    
    default:
        printf("Not a valid second argument was passed\n");
        exit(1);
        break;
    }

    if (f !=stdin) fclose(f);

    if(M != N) {
        printf("COO matrix' columns and rows are not the same");
    }
}

int main(int argc, char** argv) {

    FILE *f;
    uint32_t M, N, nnz;   
    int *I, *J;
    double *val;
    int binary = 1;

    struct timeval start, end;

    if (argc < 2)
	{
		fprintf(stderr, "Usage: %s [martix-market-filename] [0 for non binary 1 for binary matrix]\n", argv[0]);
		exit(1);
	}
    else    
    { 
        if ((f = fopen(argv[1], "r")) == NULL) 
            exit(1);
    }

    readfile_stepone(f, &M, &N, &nnz, I, J, binary);

    /* For the COO */
    I = (uint32_t *) malloc(nnz * sizeof(uint32_t));
    J = (uint32_t *) malloc(nnz * sizeof(uint32_t));
    val = (double *) malloc(nnz * sizeof(double));

    readfile_steptwo(f, &M, &N, &nnz, I, J, val, binary);

    /* For the CSC */
    uint32_t* a_cscRow = (uint32_t *) malloc(nnz * sizeof(uint32_t));
    uint32_t* a_cscColumn = (uint32_t *) malloc((N + 1) * sizeof(uint32_t));
    /* For the CSC */
    uint32_t* b_csrColumn = (uint32_t *) malloc(nnz * sizeof(uint32_t));
    uint32_t* b_csrRow = (uint32_t *) malloc((M + 1) * sizeof(uint32_t));

    /* Initialize c3 with zeros*/
    int* c3;
    c3 = malloc(N * sizeof c3);    
    for(int i = 0; i < N; i++){
        c3[i] = 0;
    }

    coo2csc(a_cscRow, a_cscColumn, I, J, nnz, M, 0);
    coo2csc(b_csrColumn, b_csrRow, J, I, nnz, N, 0);

    /* For the C CSC */
    uint32_t* c_cscRow = (uint32_t *) malloc(0 * sizeof(uint32_t));
    uint32_t* c_values = (uint32_t *) malloc(0 * sizeof(uint32_t));
    uint32_t* c_cscColumn = (uint32_t *) malloc((N + 1) * sizeof(uint32_t));

    c_cscColumn[0] = 0;
    c_cscRow = realloc(c_cscRow, 2 * nnz * sizeof(int));
    c_values = realloc(c_values, 2 * nnz * sizeof(int));

    printf("Matrix Loaded, now Searching!\n");    

    // Start measuring time
    gettimeofday(&start,NULL); 

    /* ALGORITHM STARTS HERE */

    // C = A.*(A*A)
    cilk_for(int i = 0; i < N; i++) {
        for(int j = 0; j < a_cscColumn[i+1] - a_cscColumn[i]; j++) {
            int a_row = a_cscRow[a_cscColumn[i] + j];
            int a_col = i;

            // Element of (A*A)[i,j]
            int k_size = a_cscColumn[a_row+1] - a_cscColumn[a_row];  
            int l_size = b_csrRow[a_col+1] - b_csrRow[a_col];    
            int *l = malloc((l_size) * sizeof(int));
            int *k = malloc((k_size) * sizeof(int));
            /* Create the l vector with the appropriate values */
            for(int x = 0; x < k_size; x++) {
                k[x] = a_cscRow[a_cscColumn[a_row] + x];
            }
            for(int x = 0; x < l_size; x++) {
                l[x] = b_csrColumn[b_csrRow[a_col] + x];
            }

            int k_pointer = 0;
            int l_pointer = 0;
            int value = 0;

            while(k_pointer != k_size && l_pointer != l_size) {
                if(k[k_pointer] == l[l_pointer]) {
                    value = 1;
                    break;
                }
                else if(k[k_pointer] > l[l_pointer]) {
                    l_pointer++;
                }
                else
                {
                    k_pointer++;
                }                
            }        

            if(value) {
                c_values[a_cscColumn[i] + j] = 1;
            }
            else {
                c_values[a_cscColumn[i] + j] = 0;
            }
            free(l);
            free(k);
        }
    }
    c_cscColumn = a_cscColumn;
    c_cscRow = a_cscRow;

    gettimeofday(&end,NULL);
    double duration = (end.tv_sec+(double)end.tv_usec/1000000) - (start.tv_sec+(double)start.tv_usec/1000000);
    printf("Duration: %f\n", duration);

    /* Deallocate the arrays */
    free(I);
    free(J);
    free(c3);

    return 0;
}