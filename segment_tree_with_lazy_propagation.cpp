#include <iostream>
#include <vector>
#define MAX 100

struct s_tree
{
public :
    int64_t sum {0};
    int64_t propagation {0};
};

std::vector<int64_t> arr(MAX);
std::vector<s_tree> tree(MAX*3);

void init(int curr_node, int segment_start, int segment_end)
{
    if(segment_start == segment_end)
    {
        tree[curr_node].sum = arr[segment_start];
        return;
    }
    int left_node = curr_node*2;
    int right_node = curr_node*2+1;
    int segment_mid = segment_start + (segment_end-segment_start)/2 ;
    init(left_node,segment_start,segment_mid);
    init(right_node,segment_mid+1,segment_end);
    tree[curr_node].sum = tree[left_node].sum + tree[right_node].sum ;
}

void update(int curr_node, int segment_start, int segment_end, int query_start, int query_end, int64_t new_val)
{
    if(query_start > segment_end || query_end < segment_start)
    {
        return;
    }
    if(segment_start >= query_start && segment_end <= query_end)
    {
        tree[curr_node].sum += ((segment_end-segment_start+1)*new_val);
        tree[curr_node].propagation += new_val; 
        return;
    }
    int left_node = curr_node*2;
    int right_node = curr_node*2 + 1;
    int segment_mid = segment_start + (segment_end-segment_start)/2;
    update(left_node,segment_start,segment_mid,query_start,query_end,new_val);
    update(right_node,segment_mid+1,segment_end,query_start,query_end,new_val);
    tree[curr_node].sum = tree[left_node].sum + tree[right_node].sum + ((segment_end-segment_start+1)*tree[curr_node].propagation);
}

int64_t query(int curr_node, int segment_start , int segment_end, int query_start, int query_end, int carry)
{
    if(query_start > segment_end || query_end < segment_start)
    {
        return 0;
    }
    if(segment_start >= query_start && segment_end <= query_end)
    {
        return tree[curr_node].sum + ((segment_end - segment_start + 1)*carry);
    }
    int left_node = curr_node*2;
    int right_node = curr_node*2 + 1;
    int segment_mid = segment_start + (segment_end - segment_start)/2;
    int64_t query_on_left = query(left_node,segment_start,segment_mid,query_start,query_end,carry+tree[curr_node].propagation);
    int64_t query_on_right =  query(right_node,segment_mid+1,segment_end,query_start,query_end,carry+tree[curr_node].propagation);
    return query_on_left + query_on_right;
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
    std::cout << query(1,0,6,0,6,0) << ' '; // 8

    update(1,0,6,0,6,5);
    std::cout << query(1,0,6,0,6,0); // 8 + 35 = 43

    return 0;
}