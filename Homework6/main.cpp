#include <iostream>
#include <cassert>
#include "matrix.h"

void printFragment(Matrix<int,0>& matrix)
{
    for(int i=1;i<9;++i)
    {
        for( int j=1;j<9;++j)
            std::cout<<matrix[i][j]<<" ";
        std::cout<<std::endl;
    }
    std::cout<<matrix.size()<<std::endl;
        for(auto c: matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << "["<< x << "][" << y << "] " << v << std::endl;
    }
};

int main()
{
    Matrix<int, 0> matrix;
    int n=9;
    for(int i=0;i<=n;++i)
    {
        matrix[i][i] = i;
        matrix[i][n-i] = n-i;
    }

    printFragment(matrix);

    return 0;
}