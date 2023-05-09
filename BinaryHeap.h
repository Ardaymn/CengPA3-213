#pragma once

#include <vector>

struct HeapElement
{
    int     uniqueId;
    double  weight;
};

class BinaryHeap
{
    private:
    std::vector<HeapElement> elements;
    void bubbleDown(int hole)
    {
        
        int child;
        HeapElement temp = elements[hole];

        for(; (hole*2) + 1 <= HeapSize()-1; hole = child)
        {
            child = (hole)*2+1;
            if(child != HeapSize()-1 && elements[child+1].weight < elements[child].weight) child++;
            if(elements[child].weight < temp.weight)
                elements[hole] = elements[child];
            else break;
        }
        elements[hole] = temp;
    }
    void buildheap()
    {
        if(elements.size() == 0) return;
        int i;
        for(i= HeapSize()/2 -1 ; i>=0; i--)
        {
            bubbleDown(i);
        }
    }

    // Do not remove this the tester will utilize this
    // to access the private parts.
    friend class HW3Tester;

    protected:
    public:
        // Constructors & Destructor
                            BinaryHeap();
        //
        bool                Add(int uniqueId, double weight);
        bool                PopHeap(int& outUniqueId, double& outWeight);
        bool                ChangePriority(int uniqueId, double newWeight);
        int                 HeapSize() const;
};