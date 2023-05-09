#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    // TODO: or not
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    int i;
    for(i=0;i<elements.size();i++)
    {
        if(elements[i].uniqueId==uniqueId)
            return false;
       
    }
    HeapElement elem;
    elem.uniqueId=uniqueId;
    elem.weight=weight;
    elements.push_back(elem);
    int sizeofheap= HeapSize()-1;
    int hole =sizeofheap;
    while(hole!=0 && elements[(hole-1)/2].weight>elements[hole].weight)
    {
        HeapElement temp=elements[hole];
        elements[hole] = elements[(hole-1)/2];
        elements[(hole-1)/2] = temp;
        hole = (hole-1)/2;
    }
    return true;
    
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    if(HeapSize() == 0) return false;
    
    outUniqueId = elements[0].uniqueId;
    outWeight = elements[0].weight;

    HeapElement temp = elements[0];
    elements[0] = elements[HeapSize()-1];
    elements.pop_back();
    if(elements.size() > 0)
    {
        bubbleDown(0);
    }
    return true;
    
    
    // TODO:
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    int i;
    bool flag = false;
    for(i=0;i<HeapSize();i++)
    {
        if(elements[i].uniqueId ==uniqueId)
        {
            elements[i].weight =newWeight;
            flag = true;
        }
    }
    if(flag)
    {
        buildheap();
        return true;
    }
    return flag;
}

int BinaryHeap::HeapSize() const
{
    return elements.size();
    // TODO:
}