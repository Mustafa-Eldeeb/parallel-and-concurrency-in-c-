/*

challenge : to multiply two matrices
*/

#include<thread>
#include<cmath>

/*
sequential func to mat_mul 

mul A and B 
C will hold a result 
*/
void sequential_mat_mul(long **A, size_t num_rows_a, size_t num_cols_a,
                        long **B, size_t num_rows_b, size_t num_cols_b,
                        long **C  )
{
    for(size_t i =0; i<num_rows_a; i++)
    {
        for(size_t j = 0; j<num_cols_b;j++)
        {
            C[i][j]=0; //initialized result cell to zero 
            for(size_t k=0;k<num_cols_a; k++)
            {
                C[i][j]+=A[i][j]*B[k][j];
            }
        }
    }


}

