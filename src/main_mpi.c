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
#include <mpi.h>

int main(int argc, char** argv) {

    int ret_code;
    MM_typecode matcode;
    FILE *f1, *f2, *f3;
    uint32_t I, J, K, nnz_a, nnz_b, nnz_f; 
    int *I_A, *I_B, *I_F, *J_A, *J_B, *J_F;
    double *val_a;

    // MPI
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int p;
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (argc < 2)
	{
		fprintf(stderr, "Usage: %s [martix-market-filename-A] [martix-market-filename-B] [optional martix-market-filename-F]\n", argv[0]);
		exit(1);
	}
    else    
    {
        if ((f1 = fopen(argv[1], "r")) == NULL) 
            exit(1);
        if ((f2 = fopen(argv[2], "r")) == NULL) 
            exit(1);
        if ((f3 = fopen(argv[3], "r")) == NULL) 
            exit(1);
    }

    /* reseve memory for matrices */
    /* For the COO */
    I_A = (int *) malloc(nnz_a * sizeof(int));
    J_A = (int *) malloc(nnz_a * sizeof(int));
    I_B = (int *) malloc(nnz_b * sizeof(int));
    J_B = (int *) malloc(nnz_b * sizeof(int));
    I_F = (int *) malloc(nnz_f * sizeof(int));
    J_F = (int *) malloc(nnz_f * sizeof(int));
    val_a = (double *) malloc(nnz_a * sizeof(double));


    /* Read A matrix */

    if (mm_read_banner(f1, &matcode) != 0)
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

    if ((ret_code = mm_read_mtx_crd_size(f1, &I, &K, &nnz_a)) !=0)
        exit(1);
    
    printf("I: %d, K: %d, nnz_a: %d\n", I, K, nnz_a);

    uint8_t** a = (uint8_t**) malloc(I * sizeof(uint8_t*));
    for(int i = 0; i < I; i++) {
        a[i] = (uint8_t*) malloc(K * sizeof(uint8_t));
        memset(a[i], 0, I * sizeof(uint8_t));    
    }

    /* Read from the file */
    for (uint32_t i=0; i < nnz_a; i++) {
        /* I is for the rows and J for the columns */
        fscanf(f1, "%d %d\n", &I_A[i], &J_A[i]);
        // printf("I_A[%d] = %d\n", i, I_A[i]);
        // printf("J_A[%d] = %d\n", i, J_A[i]);
        I_A[i]--;  /* adjust from 1-based to 0-based */
        J_A[i]--;

        a[I_A[i]][J_A[i]] = 1;
    }

    if (f1 !=stdin) fclose(f1);
    
    

    /* Read B matrix */

    if (mm_read_banner(f2, &matcode) != 0)
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

    if ((ret_code = mm_read_mtx_crd_size(f2, &K, &J, &nnz_b)) !=0)
        exit(1);
    
    printf("K: %d, J: %d, nnz_b: %d\n", K, J, nnz_b);

   uint8_t** b = (uint8_t**) malloc(K * sizeof(uint8_t*));
    for(int i = 0; i < K; i++) {
        b[i] = (uint8_t*) malloc(J * sizeof(uint8_t));
        memset(b[i], 0, K * sizeof(uint8_t));    
    }

    /* Read from the file */
    for (uint32_t i=0; i < nnz_b; i++) {
        /* I is for the rows and J for the columns */
        fscanf(f2, "%d %d\n", &I_B[i], &J_B[i]);
        I_B[i]--;  /* adjust from 1-based to 0-based */
        J_B[i]--;
        b[I_B[i]][J_B[i]] = 1;
    }

    if (f2 !=stdin) fclose(f2);
    
    
    // /* Read F matrix */

    // if (mm_read_banner(f3, &matcode) != 0)
    // {
    //     printf("hello\n");
    //     printf("Could not process Matrix Market banner.\n");
    //     exit(1);
    // }

    // /*  This is how one can screen matrix types if their application */
    // /*  only supports a subset of the Matrix Market data types.      */

    // if (mm_is_complex(matcode) && mm_is_matrix(matcode) && 
    //         mm_is_sparse(matcode) )
    // {
    //     printf("Sorry, this application does not support ");
    //     printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
    //     exit(1);
    // }
    
    // /* find out size of sparse matrix .... */

    // if ((ret_code = mm_read_mtx_crd_size(f3, &I, &J, &nnz_f)) !=0)
    //     exit(1);
    
    // printf("I: %d, J: %d, nnz_f: %d", I, J, nnz_f);

    // /* Read from the file */
    // for (uint32_t i=0; i < nnz_f; i++) {
    //     /* I is for the rows and J for the columns */
    //     fscanf(f3, "%d %d\n", &I_F[i], &J_F[i]);
    //     printf("I_F[%d] = %d\n", i, I_F[i]);
    //     printf("J_F[%d] = %d\n", i, J_F[i]);
    //     I_F[i]--;  /* adjust from 1-based to 0-based */
    //     J_F[i]--;
    // }

    // if (f3 !=stdin) fclose(f3);

    /* Allocate memory for the result of the multiplication */
    uint8_t** res = (uint8_t**) malloc(I * sizeof(uint8_t*));
    for(int i = 0; i < I; i++) {
        res[i] = (uint8_t*) malloc(J * sizeof(uint8_t));
        memset(res[i], 0, J * sizeof(uint8_t));
    }
    
    // /* Algorithm starts here */

    for(int i = 0; i < I/p; i++) {
        for(int j = 0; j < J; j++) {
            for(int k = 0; k < K; k++) {
                if(a[world_rank * (I/p) + i][k] * b[k][j]) {
                    res[i][j] = 1;
                    goto next_iteration;
                }
            }
        }
        next_iteration: ;
    }

    /* Print result */
    printf("result matrix\n");
    for(int i = 0; i < I; i++) {
        printf("\n");
        for(int j = 0; j < J; j++) {
            printf("%u\t", res[i][j]);
        }
    }

    // Finalize the MPI environment.
    MPI_Finalize();

}

