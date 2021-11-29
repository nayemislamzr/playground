#include <iostream>
#include <climits>

void swap(int* x , int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

class heap
{
public:
    int capacity;
    int* harr;
    int heap_size;
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return 2*i+1; }
    int right(int i) { return 2*i+2; }
    heap(int cap);
    int insertkey(int i);
    int extractMin();
    void Minheapify(int i);
    void decreasekey(int i,int new_val);
    void deletekey(int i);
    int getMin();
};

heap::heap(int cap)
{
    capacity = cap;
    heap_size = 0;
    harr = new int[capacity];
}

int heap::insertkey(int val)
{
    if (heap_size == capacity)
    {
        std::cout << "buffer overflow !!!\n" ;
        return INT_MAX;
    }
    else
    {
        heap_size++;
        int i = heap_size - 1;
        harr[i] = val ;
        while(i!=0 && harr[parent(i)] > harr[i])
        {
            swap(&harr[parent(i)],&harr[i]);
            i = parent(i);
        }
        return val;
    }    
}

int heap::extractMin()
{
    if(heap_size == 0)
    {
        std::cout << "buffer underflow !!!\n" ; 
        return INT_MIN ;  
    }
    if(heap_size == 1)
    {
        heap_size -- ;
        return harr[0];
    }
    else
    {
        int root = harr[0];
        harr[0] = harr[heap_size-1];
        heap_size--;

        Minheapify(0);
        return root;
    }
}

void heap::Minheapify(int i)
{   
    int l = left (i);
    int r = right (i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[smallest])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i],&harr[smallest]);
        Minheapify(smallest);
    }
}

void heap::decreasekey (int i , int new_val)
{
    harr[i] = new_val ;

    while(i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[parent(i)],&harr[i]);
        i = parent(i);
    } 
}

void heap::deletekey(int i)
{
    decreasekey(i,INT_MIN);
    extractMin();
}

int heap::getMin()
{
    if (heap_size) 
        return harr[0];
    else 
        return INT_MIN ;    
}

int main()
{
    heap h(11); 
    h.insertkey(3); 
    h.insertkey(2); 
    h.deletekey(1); 
    h.insertkey(15); 
    h.insertkey(5); 
    h.insertkey(4); 
    h.insertkey(45); 
    std::cout << h.extractMin() << " "; 
    std::cout << h.getMin() << " "; 
    h.decreasekey(2, 1); 
    std::cout << h.getMin(); 
    return 0; 
}