#include <thread>

/*declaration of merge helper function*/
void merge(int * array,unsigned int left, unsigned int mid, unsigned int right);

/*sequential merge sort function*/
void sequential_mege_sort(int*array, unsigned int left, unsigned int right)
{
    if(left<right)
    {
        unsigned int mid = (left+right)/2;      // find the mid
        sequential_mege_sort(array, left, mid); //sort the left half
        sequential_mege_sort(array, mid+1, right); //sort the right half
        merge(array,left,mid, right);
    }
}