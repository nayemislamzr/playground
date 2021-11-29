#ifndef SINGLY_LINKED_LIST_H_INCLUDED
#define SINGLY_LINKED_LIST_H_INCLUDED
template<typename T>
class singly_linked_list
{
public:
    T data;
    singly_linked_list<T>* next;
    singly_linked_list(const T& value)
        :data{value}, next{NULL}
    {
        //nothing here only initialization
    }
    singly_linked_list(void)
        : data{0},next{NULL}
    {
        //nothing here only initialization
    }
    /*<!--------------------------------Operators----------------------------------!>*/
    void operator+(singly_linked_list<T>& that);        // merges two linked list
    /*<!--------------------------------Functions----------------------------------!>*/
    //<!---insert functions---!>
    void insert_node(const T& value);     // inserts at the last
    void insert_node(const T& value , const T& want_to_add_after);       // inserts after desired node with data = value
    void insert_node_by_pos(const T&value , const int& position); // insert by position
    void edit(const T& value,const int& position);    // edit value on the position
    //<!---delete function---!>
    void delete_node(void);    // deletes last node but you can not delete root node
    void delete_node(const T& value);  // delete by value but you can not delete root node
    void delete_node_by_pos(const int& position); //delete by position but you can not delete root node
    //<!---print function---!>
    void print(void);    // printing with memory details
    void print_val(void); // printing only values
};
/*<!-----------------------------------------Operators-----------------------------------------!>*/
template<typename T>
void singly_linked_list<T>::operator+(singly_linked_list<T>& that)
{
    singly_linked_list<T>*head = this;
    while(head->next!=NULL)
        head= head->next;
    head->next = &that;
}
/*<!------------------------------------Insert Functions-----------------------------------!>*/
template<typename T>
void singly_linked_list<T>::insert_node(const T& value)
{
    singly_linked_list<T>*head = this;
    while(head->next!=NULL)
        head=head->next;
    singly_linked_list<T>*new_node = new singly_linked_list<T>(value);
    head->next = new_node;
}
template<typename T>
void singly_linked_list<T>::insert_node(const T& value , const T& want_to_add_after)
{
    singly_linked_list<T>* head= this;
    while(head->data!=want_to_add_after)
    {
         head=head->next;
         if(head==NULL)
            return;
    }
    singly_linked_list<T>*new_node = new singly_linked_list<T>(value);
    singly_linked_list<T>* temp = head->next;
    head->next = new_node;
    new_node->next = temp;
}
template<typename T>
void singly_linked_list<T>::insert_node_by_pos(const T&value,const int& position)
{
    int temp_pos = 1;
    singly_linked_list<T>* head = this;
    if(position<=0)
        return;
    while(temp_pos!=position)
    {
        temp_pos++;
        head = head->next;
        if(head==NULL)
            return;
    }
    singly_linked_list<T>*new_node = new singly_linked_list<T>(value);
    singly_linked_list<T>* temp = head->next;
    head->next = new_node;
    new_node->next = temp;
}
template<typename T>
void singly_linked_list<T>::edit(const T& value,const int& position)
{
    int temp_pos = 1;
    singly_linked_list<T>* head = this;
    if(position<=0)
        return;
    while(temp_pos!=position)
    {
        temp_pos++;
        head = head->next;
        if(head==NULL)
            return;
    }
    head->data = value;
}
/*<!----------------------------------------Delete functions-----------------------------------!>*/
template<typename T>
void singly_linked_list<T>::delete_node(void)
{
    singly_linked_list<T>*head = this;
    if(head->next==NULL)
        return ;
    while(head->next->next!=NULL)
        head=head->next;
    head->next = NULL;
}
template<typename T>
void singly_linked_list<T>::delete_node(const T& value)
{
    singly_linked_list<T>*head = this;
    if(head->next==NULL)
        return ;
    while(head->next->data!=value)
    {
        head = head -> next;
        if(head==NULL)
            return;
    }
    head->next = head->next->next;
}
template<typename T>
void singly_linked_list<T>::delete_node_by_pos(const int& position)
{
    if(position<=0)
        return;
    singly_linked_list<T>* head = this;
    if(this->next==NULL)
        return;
    int temp_pos = 2;
    while(temp_pos!=position)
    {
        temp_pos++;
        head=head->next;
        if(head==NULL)
            return;
    }
    head->next= head->next->next;
}
/*<!---------------------------------------printing function--------------------------------------!>*/
template<typename T>
void singly_linked_list<T>::print(void)
{
    singly_linked_list<T>*head = this;
    while(head!=NULL)
    {
        std::cout << "|" << head << " | " << head->data << " | " << head->next << "| --> ";
        head = head->next;
    }
    std::cout << "|" << "NULL" << " | " << "0" << " | " << "NULL" << "|";
}
template<typename T>
void singly_linked_list<T>::print_val(void)
{
    singly_linked_list<T>*head = this;
    while(head!=NULL)
    {
        std::cout << head->data << " ";
        head = head->next;
    }
}
#endif // SINGLY_LINKED_LIST_H_INCLUDED
