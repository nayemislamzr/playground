#ifndef _DS_LINKED_LIST_
#define _DS_LINKED_LIST_

#include <climits>

namespace DS {
    template <typename T>
    class LinkedList {
    private :
        struct linkedlist {
            T data ;
            linkedlist* prev = nullptr;
            linkedlist* next = nullptr;
            linkedlist()
                : data(INT_MAX) { }
            linkedlist(T key)
                : data(key) { }
            linkedlist(T key , linkedlist* prevNode) 
                :data(key) , prev(prevNode) { }
            linkedlist(T key , linkedlist* prevNode , linkedlist* nextNode) 
                :data(key) , prev(prevNode) , next(nextNode) { }
            ~linkedlist() {
                // delete 
            }
        };
        unsigned int _size;
        linkedlist* root = nullptr; 
        linkedlist* lastNode = nullptr;
    public :
        LinkedList() 
            :_size(0) {
            root = new linkedlist;
            lastNode = root ;
        }
        LinkedList(const std::initializer_list<T>& keys) 
            :LinkedList() {
            for(auto& key : keys) {
                push(key);
            }
        }
        // void operator= (LinkedList<T>& anotherLinkedList) {
        //     linkedlist* currNode = anotherLinkedList.r
        // }

        inline bool empty() { return (_size == 0)? true : false ;}
        inline unsigned int size() { return _size ;}
        T front() {
            if(_size > 0) 
                return root->next->data ;
            else 
                return INT_MAX ;
        }
        T back() {
            if(_size > 0)
                return lastNode->data ;
            else 
                return INT_MAX ;
        }

        void push(T data) {
            linkedlist* newNode = new linkedlist(data);
            newNode->prev = lastNode ;
            lastNode->next = newNode ;
            lastNode = newNode ;
            _size++ ;
        }

        T pop() {
            if(_size == 0)
                return INT_MAX;
            else {
                T removedData = lastNode->data ;
                linkedlist* prevNodeOfLastNode = lastNode->prev ;
                free(lastNode);
                prevNodeOfLastNode->next = nullptr ;
                lastNode = prevNodeOfLastNode ;
                _size-- ;
                return removedData;
            }
        }

    };
}
#endif