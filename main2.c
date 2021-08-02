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

int main(char argc, char** argv) {

    int ret_code;
    MM_typecode matcode;
    FILE *f1, *f2, *f3;
    uint32_t I, J, K, nnz_a, nnz_b, nnz_f; 
    int *I_A, *I_B, *I_F, *J_A, *J_B, *J_F;
    double *val_a;

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
    
    printf("I: %d, K: %d, nnz_a: %d", I, K, nnz_a);

    /* Read from the file */
    for (uint32_t i=0; i < nnz_a; i++) {
        /* I is for the rows and J for the columns */
        fscanf(f1, "%d %d\n", &I_A[i], &J_A[i]);
        printf("I_A[%d] = %d\n", i, I_A[i]);
        printf("J_A[%d] = %d\n", i, J_A[i]);
        I_A[i]--;  /* adjust from 1-based to 0-based */
        J_A[i]--;
    }

    if (f1 !=stdin) fclose(f1);

    /* For the A_CSC */
    uint32_t* aRow = (uint32_t *) malloc(nnz_a * sizeof(uint32_t));
    uint32_t* aColumn = (uint32_t *) malloc((K + 1) * sizeof(uint32_t));

    coo2csc(aRow, aColumn, I_A, J_A, nnz_a, I, 0);


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
    
    printf("K: %d, J: %d, nnz_b: %d", K, J, nnz_b);

    /* Read from the file */
    for (uint32_t i=0; i < nnz_b; i++) {
        /* I is for the rows and J for the columns */
        fscanf(f2, "%d %d\n", &I_B[i], &J_B[i]);
        printf("I_B[%d] = %d\n", i, I_B[i]);
        printf("J_B[%d] = %d\n", i, J_B[i]);
        I_B[i]--;  /* adjust from 1-based to 0-based */
        J_B[i]--;
    }

    if (f2 !=stdin) fclose(f2);

    /* For the B_CSC */
    uint32_t* bRow = (uint32_t *) malloc(nnz_b * sizeof(uint32_t));
    uint32_t* bColumn = (uint32_t *) malloc((J + 1) * sizeof(uint32_t));

    coo2csc(bRow, bColumn, I_B, J_B, nnz_b, K, 0); 

    
    /* Read F matrix */

    if (mm_read_banner(f3, &matcode) != 0)
    {
        printf("hello\n");
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

    if ((ret_code = mm_read_mtx_crd_size(f3, &I, &J, &nnz_f)) !=0)
        exit(1);
    
    printf("I: %d, J: %d, nnz_f: %d", I, J, nnz_f);

    /* Read from the file */
    for (uint32_t i=0; i < nnz_f; i++) {
        /* I is for the rows and J for the columns */
        fscanf(f3, "%d %d\n", &I_F[i], &J_F[i]);
        printf("I_F[%d] = %d\n", i, I_F[i]);
        printf("J_F[%d] = %d\n", i, J_F[i]);
        I_F[i]--;  /* adjust from 1-based to 0-based */
        J_F[i]--;
    }

    if (f3 !=stdin) fclose(f3);

    /* For the F_CSC */
    uint32_t* fRow = (uint32_t *) malloc(nnz_f * sizeof(uint32_t));
    uint32_t* fColumn = (uint32_t *) malloc((J + 1) * sizeof(uint32_t));

    coo2csc(fRow, fColumn, I_F, J_F, nnz_f, I, 0);


    /* Multiplication starts here */

    printf("\naColumn:\n");
    for(uint32_t i = 0; i < K + 1; i++) {
        printf("%d\t", aColumn[i]);
    }
    printf("\naRow:\n");
    for(uint32_t i = 0; i < nnz_a; i++) {
        printf("%d\t", aRow[i]);
    }

    printf("\nI_A:\n");
    for(uint32_t i = 0; i < nnz_a; i++) {
        printf("%d\t", I_A[i]);
    }
    printf("\nJ_B:\n");
    for(uint32_t i = 0; i < nnz_a; i++) {
        printf("%d\t", J_A[i]);
    }


    printf("\nbColumn:\n");
    for(uint32_t i = 0; i < J + 1; i++) {
        printf("%d\t", bColumn[i]);
    }
    printf("\nbRow:\n");
    for(uint32_t i = 0; i < nnz_b; i++) {
        printf("%d\t", bRow[i]);
    }

    printf("\nI_B:\n");
    for(uint32_t i = 0; i < nnz_b; i++) {
        printf("%d\t", I_B[i]);
    }
    printf("\nJ_B:\n");
    for(uint32_t i = 0; i < nnz_b; i++) {
        printf("%d\t", J_B[i]);
    }


    printf("\nfColumn:\n");
    for(uint32_t i = 0; i < J + 1; i++) {
        printf("%d\t", fColumn[i]);
    }
    printf("\nfRow:\n");
    for(uint32_t i = 0; i < nnz_f; i++) {
        printf("%d\t", fRow[i]);
    }

    printf("\nI_F:\n");
    for(uint32_t i = 0; i < nnz_f; i++) {
        printf("%d\t", I_F[i]);
    }
    printf("\nJ_F:\n");
    for(uint32_t i = 0; i < nnz_f; i++) {
        printf("%d\t", J_F[i]);
    }

    
    /* Algorithm starts here */

    /**
        Divide in 64 different sub arrays
    */
   
    uint8_t** a = (uint8_t**) malloc(I * sizeof(uint8_t*));
    for(int i = 0; i < I; i++) {
        a[i] = (uint8_t*) malloc((K / 64) * sizeof(uint8_t));
        /* Set all values of the array to zero */
        memset(a[i], 0, (K / 64) * sizeof(uint8_t));
    }

    uint8_t** b = (uint8_t**) malloc((K / 64) * sizeof(uint8_t*));
    for(int i = 0; i < (K / 64); i++) {
        b[i] = (uint8_t*) malloc(I * sizeof(uint8_t));
        /* Set all values of the array to zero */
        memset(b[i], 0, I * sizeof(uint8_t));
    }

}

