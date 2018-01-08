#include <iostream>
#include <map>
#include "my_allocator.h"
#include "my_container.h"


template<typename T>
T factorial(T n)
{
    T f=1;
    for(T i = 1; i <= n;++i)
        f*=i;
    return f;
};

int main() {
    constexpr int N=10;
    std::map<int,int> m;
    for(int i=0;i<N;++i)
        m.insert(std::make_pair(i,factorial(i)));

    std::map<int,int,std::less<int>, MyAlloc<std::pair<int,int>,N>> nm;
    for(int i=0;i<N;++i)
        nm.insert(std::make_pair(i,factorial(i)));
    for(auto i = nm.begin(); i!=nm.end();++i)
    {
        std::cout<<(*i).first<<" "<<(*i).second<<std::endl;
    }

    MyContainer<int> dc;
    for(int i=0; i<N;++i)
    {
        dc.push_back(i+1);
    }

    MyContainer<int, MyAlloc<int, N>> c;
    for(int i=0; i<N;++i)
    {
        c.push_back(i);
    }

    for(auto i = c.begin();i!=c.end();++i)
    {
        std::cout<<*i<<std::endl;
    }

    //c.walk();
    return 0;
}