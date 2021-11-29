#ifndef _DS_HEAP_
#define _DS_HEAP

#include <iostream>
#include <memory>
#include <climits>
#include <queue>

#define m_size 1000

namespace DS {
    template <typename T>
    class MinHeap {
    private:
        int _size ;
        int _max_size ;
        T* _heap_array = nullptr;
    public :
        explicit MinHeap() 
            : _size(0) , _max_size(m_size) {
            _heap_array = new T[m_size] ;
        }

        explicit MinHeap(const std::initializer_list<T>& keys) 
            : MinHeap() {
            _heap_array = new T[m_size] ;
            for(auto& key : keys) {
                push(key);
            }
        }

        void operator= (MinHeap& otherOne) {
            _size = otherOne._size ;
            _max_size = otherOne._max_size ;
            _heap_array = otherOne._heap_array ;
        }

        ~MinHeap() {
            delete[] _heap_array ;
        }

        inline int size() { return _size ; }
        inline int max_size() { return _max_size ; }
        inline bool empty() { return _size == 0 ? true : false ;}

        static void swap(T* first_one , T* second_one) {
            T cunning_monkey = *second_one ;
            *second_one = *first_one ;
            *first_one = cunning_monkey ;
        }

        void push(const T& key) {
            if(_size == _max_size) 
                return ;
            int last_index = _size ;
            _heap_array[last_index] = key ;
            while(last_index != 0 && _heap_array[parent(last_index)] > _heap_array[last_index]) {
                swap(&_heap_array[parent(last_index)] , &_heap_array[last_index]);
                last_index = parent(last_index) ;
            }
            _size++ ;
        }

        T pop() {
            _size--;
            return _heap_array[_size];
        }

        void remove(int index) {
            decreaseKey(index , INT_MIN);
            getMinElement();
        }

        void show() {
            if(_size <= 0 )
                return ;
            std::queue<T> q ;
            q.push(0);
            while (!q.empty())
            {
                int currIndex = q.front() ;
                std::cout << _heap_array[currIndex] << " " ;
                q.pop() ;
                int left = leftChild(currIndex) ;
                int right = rightChild(currIndex) ;
                if(left < _size) q.push(left);
                if(right < _size) q.push(right);
            }
            
        }

    private :
        inline static int parent(int i) { return (i-1)/2 ; }
        inline static int leftChild(int i) { return 2*i+1 ;}
        inline static int rightChild(int i) { return 2*i+2 ; }

        void decreaseKey (int index , int newKey) {
            _heap_array[index] = newKey ;
            while(index!=0 && _heap_array[parent(index)] > _heap_array[index]) {
                swap(&_heap_array[parent(index)] , &_heap_array[index]);
                index = parent(index) ;
            }
        }

        T getMinElement() {
            if(_size <= 0)
                return INT_MAX ;
            else if(_size == 1) {
                T root = _heap_array[0] ;
                _size-- ;
                return root ;
            }
            else {
                T root = _heap_array[0] ;
                _heap_array[0] = _heap_array[_size - 1] ;
                MinHeapify(0) ;
                _size-- ;
                return root ;
            }
        }

        void MinHeapify(int index) {
            int left = leftChild(index) ;
            int right = rightChild(index) ;
            int smallest = index ;
            if(left < _size && _heap_array[left] < _heap_array[smallest]) {
                smallest = left ;
            }
            if(left < _size && _heap_array[right] < _heap_array[smallest]) {
                smallest = right ;
            }
            if(smallest != index) {
                swap(&_heap_array[index] , &_heap_array[smallest]) ;
                MinHeapify(smallest) ;
            }
        }
    };
}
#endif