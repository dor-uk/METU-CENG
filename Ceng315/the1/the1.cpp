#include <stdio.h>


void fswap(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, int i, int j)
{
    // function for swap operation
    // keeps the track ofaverage dist and max dist
    
    double total_dist = avg_dist*swap;
    total_dist += j-i;
    swap++;
    avg_dist = total_dist/swap;
    
    if(j-i > max_dist)
    {
        max_dist = j-i;
    }
    
    //swap part
    unsigned short temp = arr[i];
    
    arr[i] = arr[j];
    arr[j] = temp;
}

int standard(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, int size)
{
    // standard partition for given pseudo code
    int pivot = arr[size-1];
    int i = -1;
    
    for(int j=0;j<size-1;j++)
    {
        if(arr[j] >= pivot)
        {
            i++;
            
            fswap(arr,swap,avg_dist,max_dist,i,j);
        }
    }
    
    fswap(arr,swap,avg_dist,max_dist,i+1,size-1);
    
    return i+1;
}

int fhoare(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, int size)
{
    // hoare partition for given pseudo code
    int pivot = arr[(size-1)/2];
    
    int i = -1;
    int j = size;
    
    while(true)
    {
        do
        {
            i++;
        }
        while(arr[i] > pivot);
        
        do
        {
            j--;
        }
        while(arr[j] < pivot);
        
        if(i < j)
        {
            fswap(arr,swap,avg_dist,max_dist,i,j);
        }
        
        else
        {
            return j;
        }
    }
}


int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size){
    //Your code here
    int calls = 1;
    
    if(size < 2)
    {
        return calls;
    }
    //median of 3
    if(median_of_3 == true)
    {
        int first, mid, last;
        first = arr[0];
        mid = arr[(size-1)/2];
        last = arr[size-1];
        
        //applying median of 3 
        
        int which = -1;
        

        // finding the median of 3
        if((first < mid && first>last) || (first > mid && first < last))
        {
            which = 0;
        }
        
        if((mid < first && mid > last) || (mid > first && mid < last))
        {
            which = 1;
        }
        
        if((last < mid && last > first) || (last > mid && last < first))
        {
            which = 2;
        }
        
        //printf("\n\n%d\n\n\n",which);
        
        if(hoare)
        {
            // if hoare, then pivot is the middle element
            // no need to swap if the median is in the middle
            if(which == 0)
            {
                fswap(arr,swap,avg_dist,max_dist,0,(size-1)/2);
            }
            
            if(which == 2)
            {
                fswap(arr,swap,avg_dist,max_dist,(size-1)/2,size-1);
            }
        }
        
        else
        {
            // if not hoare, then pivot is the last element
            // no need to swap if the median is the last element
            if(which == 0)
            {
                fswap(arr,swap,avg_dist,max_dist,0,size-1);
            }
            
            if(which == 1)
            {
                fswap(arr,swap,avg_dist,max_dist,(size-1)/2,size-1);
            }
        }
    }
    
    
    int pivot;
    
    // hoare version
    if(hoare == true)
    {
        // hoare partition
        pivot = fhoare(arr,swap,avg_dist,max_dist,size);
    }
    
    
    //lomuto version
    else
    {
        // lomuto partition
        pivot = standard(arr,swap,avg_dist,max_dist,size);
    }
    
    // first part of the array
    if(!hoare)
    {
        calls += quickSort(arr,swap,avg_dist,max_dist,hoare,median_of_3,pivot);
    }
    
    else
    {
        calls += quickSort(arr,swap,avg_dist,max_dist,hoare,median_of_3,pivot+1);
    }
    
    // second part of the array, different in hoare and lomuto
    calls += quickSort(arr+pivot+1,swap,avg_dist,max_dist,hoare,median_of_3,size-pivot-1);
    
	return calls;
}
