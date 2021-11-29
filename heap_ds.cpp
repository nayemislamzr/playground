#include <iostream>
#include <climits>

void swap(int* a ,int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp ;
}

class heap
{
public:
    int heap_size;
    int* harr;
    int capacity;
    int left(int i) { return 2*i+1 ;}
    int right(int i) { return 2*i+2 ;}
    int parent(int i) { return (i-1)/2;}
    heap(int cap);
    void insert_key(int value);
    int extractMin();
    void Minheapify(int i);
    void delete_key(int i);
    void decreasevalue(int i ,int val);
};

heap::heap(int cap)
{
    heap_size = 0;
    capacity=cap;
    harr = new int[cap];
}

void heap::insert_key(int value)
{
    if (heap_size >= capacity)
        {
            std::cout << "heap overflow !!!\n" ;
            return;
        }
    heap_size++;
    int i = heap_size - 1;
    harr[i] = value ;
    while (i!=0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i],&harr[parent(i)]);
        i = parent(i);
    }   
}

int heap::extractMin()
{
    if (heap_size == 0)
        return INT_MAX;
    else if (heap_size == 1)
    {
        heap_size--;
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
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[smallest])
        smallest = l;
    if (l < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if(smallest != i )
    {
        swap(&harr[smallest],&harr[i]);
        Minheapify(smallest);
    }       
}

void heap::delete_key(int i)
{
    decreasevalue(i,INT_MIN);
    extractMin();
}

void heap::decreasevalue(int i ,int val)
{
    harr[i] = val ;
    while(i!=0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[parent(i)],&harr[i]);
        i = parent(i);
    }
}

int main()
{
    heap a(10);
    a.insert_key(5);
    a.insert_key(8);
    a.insert_key(6);
    a.insert_key(4);
    a.insert_key(9);
    a.insert_key(2);
    for (int i = 0 ; i < a.heap_size ; i++)
        std::cout << a.harr[i] << " " ;
}