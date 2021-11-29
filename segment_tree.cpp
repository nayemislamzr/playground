#include <iostream>
#include <vector>
#define MAX 100

/*
      /-------------/
     /  Operations /   
    /-------------/

    - init() - initializes the segment tree with assigning segment value(here sum) to its coorespoding node
    - query() - reurns query result from a given segment
    - update() - updates value at given index and changes the value for all nodes asociated with this

    ---------------
    | pseudo code |
    ---------------
    let arr be a array of size (n) containing given inputs
    let tree be a array of size (n*3) which is for our segment_tree_implementation

    init(current_node,segment_start,segment_end) :
        if segment_start == segment_end :
            tree[curr_node] = arr[segment_start]
            return
        left_node = 2*current_node
        right_node = 2*current_node + 1
        segment_middle = segment_start + (segment_end-segment_start)/2
        init(left_node,segment_start,segment_middle)
        init(right_node,segment_middle+1,segment_end)
        tree[curr_node] = tree[left_node] + tree[right_node]

    query(current_node,segment_start,segment_end,query_start,query_end) :
        if query_start > segment_end or query_end <  segment_start :
            return 0
        if segment_start >= query_start and segment_end <= query_end :
            return tree[current_node]
        left_node = 2*current_node
        right_node = 2*current_node + 1
        segment_middle = segment_start + (segment_end-segment_start)/2
        query_on_left := query(left_node,segment_start,segment_middle,query_start,query_end)
        query_on_right := query(right_node,segment_middle+1,segment_end,query_statr,query_end)
        return query_on_left + query_on_right

    update(current_node,segment_start,segment_end,index,new_value) :
        if index > segment_end or index < segment_start :
            return
        if index == segment_start and index == segment_end :
            tree[current_node] = new_value
            return
        left_node = 2*current_node
        right_node = 2*current_node + 1
        segment_middle = segment_start + (segment_end-segment_start)/2
        update(left_node,segment_start,segment_middle,index,new_value)
        update(right_node,segment_middle+1,segment_end,index,new_value)
        tree[current_node] = tree[left_node] + tree[right_node]
*/  

std::vector<int> tree(MAX*3);
std::vector<int> arr(MAX);

void init(int node, int segment_start , int segment_end)
{   
    if(segment_start == segment_end)
    {
        tree[node] = arr[segment_start];
        return;
    }
    int left_node = node*2;
    int right_node = node*2+1;
    int segment_mid = segment_start + (segment_end - segment_start)/2;
    init(left_node, segment_start, segment_mid);
    init(right_node, segment_mid+1, segment_end);
    tree[node] = tree[left_node] + tree[right_node];
}

int query(int node, int segment_start, int segment_end, int query_start, int query_end)
{
    if(query_start > segment_end || query_end < segment_start)
        return 0;
    if(segment_start >= query_start && segment_end <= query_end)
        return tree[node];
    int left_node = node*2;
    int right_node = node*2+1;
    int segment_mid = segment_start + (segment_end - segment_start)/2;
    int query_on_left = query(left_node,segment_start,segment_mid,query_start,query_end) ;
    int querys_on_right = query(right_node,segment_mid+1,segment_end,query_start,query_end);
    return  query_on_left + querys_on_right;
}

void update(int node, int segment_start, int segment_end, int index , int new_val)
{
    if(index > segment_end || index < segment_start)
        return;
    if(index == segment_start && index == segment_end)
    {
        tree[node] = new_val;
        return;
    }
    int left_node = node*2;
    int right_node = node*2 + 1;
    int segment_mid = segment_start + (segment_end - segment_start)/2;
    update(left_node, segment_start, segment_mid, index, new_val);
    update(right_node, segment_mid+1, segment_end, index, new_val);
    tree[node] = tree[left_node] + tree[right_node]; 
}

int main()
{
    arr[0] = 4;
    arr[1] = -9;
    arr[2] = 3;
    arr[3] = 7;
    arr[4] = 1;
    arr[5] = 0;
    arr[6] = 2;

    // segment ends at 6 cause here in arr we assigned value upto index 6
    init(1,0,6);
    std::cout << query(1,0,6,0,6) << ' '; // 8

    update(1,0,6,5,5);
    std::cout << query(1,0,6,0,6); // 13

    return 0;
}