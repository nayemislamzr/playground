#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#define MAX 1000

std::vector<int> input_array;
std::vector<std::vector<int>> sparse_tree(MAX, std::vector<int> (MAX));

void build_sparse_tree(std::vector<int>& i_arr)
{
    for(int i = 0 ; i < i_arr.size() ; i++)
    {
        sparse_tree[i][0] = i;
    }
    for(int j = 1 ; (1<<j) <= i_arr.size() ; j++)
    {
        for(int i = 0 ; (i+(1<<j)-1) < i_arr.size() ; i++)
        {
            sparse_tree[i][j] = (i_arr[sparse_tree[i][j-1]] < i_arr[sparse_tree[i+(1<<(j-1))][j-1]]) ? sparse_tree[i][j-1] : sparse_tree[i+(1<<(j-1))][j-1];
        }
    }
}

int query(int left, int right, std::vector<int>& i_arr)
{
    int l = right - left +1;
    int k = floor(log2(l)) ;
    return std::min(input_array[sparse_tree[left][k]] , input_array[sparse_tree[left+l-(1<<k)+1][k]]);
}

int main()
{
    input_array.assign({3,1,2,6,5,1});
    build_sparse_tree(input_array);
    std::cout << query(3,4,input_array);
}