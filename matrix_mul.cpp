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
            //k can be rows of B or cols of A
            for(size_t k=0;k<num_cols_a; k++)
            {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }


}


//function to implement parallel matrix multiplication

void parallel_mat_mul(long **A, size_t num_rows_a, size_t num_cols_a,
                      long **B, size_t num_rows_b, size_t num_cols_b,
                      long ** C)                      
{
    //get num of available processor on this computer
    size_t num_workers = std::thread::hardware_concurrency();
    
    //divide rows of the output matrix into equal size chunks
    size_t chunk_size = ceil((float)num_rows_a/num_workers);

    // array to hold a worker threads
    std::thread workers[num_workers];

    /* start worker threads 
    to independently calc and populate a subset of overall result
    */
    for(size_t i=0;i<num_workers;i++)
    {
        size_t start_row_c = std::min(i* chunk_size,num_rows_a);
        size_t end_row_c = std::min((i+1)*chunk_size, num_rows_b);

        workers[i]= std::thread(parallel_worker, A, num_rows_a,num_cols_a,
                                                B, num_rows_b, num_cols_b,
                                                C, start_row_c, end_row_c);

    }    
    for(auto &w:workers){
        w.join();
    }

}

/*helper function for parallel mat_mul*/
void parallel_worker(long** A, size_t num_rows_a, size_t num_cols_a,
                     long** B, size_t num_rows_b, size_t num_cols_b,
                     long** C, size_t start_row_c, size_t end_row_c)
{
    for(size_t i = start_row_c; i<end_row_c; i++)//subset of rows in A
    {
        for(size_t j=0;j<num_cols_b;j++)
        {
            C[i][j]=0;
            for(size_t k=0;k<num_cols_a;k++)
            {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }

    }

}


