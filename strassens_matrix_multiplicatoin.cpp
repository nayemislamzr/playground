#include <iostream>
#include <vector>

// Naive matrix multiplication

/*
    ---------------
    | pseudo code |
    ---------------

    simple_matrix_multiplication(matrix A , matrix B) :
        a_row:= row of matrix A
        a_column:= column of matrix A
        b_row:= row of matrix B
        b_column:= column of matrix B

        let C a matrix of dimention a_row*b_column

        if a_column!=b_row :
            return matrix C;
        
        for i:=0 to a_row :
            for j:=0 to b_column :
                c[i][j]:=0
                for k:=0 to a_column :
                    C[i][j]+= A[i][K]*B[k][j]
        
        return matrix C;
*/

std::vector<std::vector<int>> simple_matrix_multiplication(std::vector<std::vector<int>>& A , std::vector<std::vector<int>>& B)
{
    int a_row = A.size();
    int a_column = A[0].size();
    int b_row = B.size();
    int b_column = B[0].size();
    std::vector<std::vector<int>> C(a_row,std::vector<int>(b_column));

    if(a_column != b_row)
        return C;

    for(int i = 0 ; i < a_row ; i++)
    {
        for(int j = 0 ; j < b_column ; j++)
        {
            C[i][j] = 0;
            for(int k = 0 ; k < a_column ; k++)
            {
                C[i][j]+= A[i][k]*B[k][j];
            }
        }
    }
    return C;
}

int main()
{
    std::vector<std::vector<int>> A({{1,2,3},
                                    {4,5,6}});
    std::vector<std::vector<int>> B({{1,2},
                                    {3,4},
                                    {5,6}});

    //  Naive square matrix multiplication 
    std::vector<std::vector<int>> result_matrix = simple_matrix_multiplication(A,B);
    for(auto& x : result_matrix)
    {
        for(auto& y : x)
        {
            std::cout << y << ' ';
        }
        std::cout << std::endl;
    }
}