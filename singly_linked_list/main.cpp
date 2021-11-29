#include <iostream>
#include "singly_linked_list.h"
int main()
{
    singly_linked_list<int>root;
    root=12;
    root.insert_node(24);
    root.insert_node(32);
    root.insert_node(69,24);
    singly_linked_list<int>another(2021);
    another.insert_node(2022);
    root+another;
    root.print();
    std::cout << std::endl;
    root.delete_node();
    root.print();
    std::cout << std::endl;
    root.delete_node(24);
    root.print();
    std::cout << std::endl;
    root.delete_node_by_pos(2);
    root.print();
    std::cout << std::endl;
    return 0;
}
