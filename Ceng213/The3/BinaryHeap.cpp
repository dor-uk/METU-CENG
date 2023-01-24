#include "BinaryHeap.h"
#include <iostream>
BinaryHeap::BinaryHeap()
{
    // TODO: or not
    HeapElement dummy;
    elements.push_back(dummy);
    size = 0;
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    // TODO:
    bool flag = false;
    int i;
    
    for(i = 0;i < size; i++)
    {
        if(elements[i].uniqueId == uniqueId)
        {
            flag = true;
            break;
        }
    }
    
    if(flag)
    {
        return false;
    }
    
    
    
    HeapElement temp;
    temp.uniqueId = uniqueId;
    temp.weight = weight;
    
    elements[0] = temp; //intialize the heap
    
    if((size + 1) == ((int) elements.size()))
        elements.resize(elements.size( )*2 + 1);
    
    // Percolate up
    int hole = ++size;
    for( ; temp.weight < elements[hole/2].weight; hole /= 2 )
        elements[hole] = elements[hole/2];
    elements[hole] = temp;
    
    return true;
    
    
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    // TODO:
    
    
    if(size != 0)
    {
        outUniqueId = elements[1].uniqueId;
        outWeight = elements[1].weight;
        
        HeapElement temp = elements[1];
        elements[1] = elements[size--];
        bubbledown(1);
        
        return true;
    }
    
    
    return false;
    
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    // TODO:
    
    
    bool flag = false;
    int i;
    for(i = 1;i <= size;i++)
    {
        if(elements[i].uniqueId == uniqueId)
        {
            elements[i].weight = newWeight;
            flag = true;
            break;
        }
    }
    
    
    buildheap();
    return flag;
    
}

int BinaryHeap::HeapSize() const
{
    // TODO:
    return size;
}

void BinaryHeap::bubbledown(int x)
{
    
    int child;
    HeapElement temp = elements[x];
    
    for( ; x*2 <= size; x = child) {
        child = x * 2;
        if(child != size && elements[child + 1].weight < elements[child].weight)
        {
            child++;
        }
        if(elements[child].weight < temp.weight)
        {
            elements[x] = elements[child];
        }
        else
        {
            break;
        }
    }
    elements[x] = temp;
    
    
}

void BinaryHeap::buildheap()
{
    for(int i = size/2; i > 0; i-- )
        bubbledown(i);
    
    
}