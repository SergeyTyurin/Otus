#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <typeinfo>

using std::cout;
using std::endl;

std::tuple<int,int,int,int> make_tuple(std::vector<std::string>& c)
{
    return std::make_tuple(std::stoi(c.at(0)),
                           std::stoi(c.at(1)),
                           std::stoi(c.at(2)),
                           std::stoi(c.at(3)));
};

void print(const std::tuple<int,int,int,int>& address)
{
    std::cout<<std::get<0>(address)<<"."
             <<std::get<1>(address)<<"."
             <<std::get<2>(address)<<"."
             <<std::get<3>(address)<<std::endl;
}

template<typename... Args>
void filter(const std::tuple<int,int,int,int>& t, Args... args)
{
    const int arg_size = sizeof...(args);
    std::vector<int> filters = {args...};
    std::vector<int> address = {std::get<0>(t),std::get<1>(t),std::get<2>(t),std::get<3>(t),};
    for(int i=0;i< arg_size;++i)
    {
        if(address.at(i)!=filters.at(i))
            return;
    }
    print(t);
}


int main()
{
    using StrVec = std::vector<std::string>;
    std::vector<StrVec> s;

//    std::vector<std::vector<std::string>> s;
//    std::vector<std::string> v = {"1","2","9","10"};
//    std::vector<std::string> v1 = {"11","3","111","9"};
//    s.push_back(v);
//    s.push_back(v1);
//    auto t = std::make_tuple(v.at(0),v.at(1),v.at(2),v.at(3));
//    auto t1 = make_tuple(v);
//    std::sort(s.begin(),s.end(), [](auto a, auto b)
//    {
//        return make_tuple(a)>make_tuple(b);
//    });
//    for(auto&& is: s)
//        for(auto&& it: is)
//            std::cout<<it<<std::endl;
//    int a,b,c,d;
//    std::tie(a,b,c,d) = t1;
//
////    cout<< a <<endl;
////    cout<< b <<endl;
////    cout<< c <<endl;
////    cout<< d <<endl;

//    auto t1 = std::make_tuple(1,24,33,2);
//    auto t2 = std::make_tuple(1,24);
//    auto t3 = std::make_tuple(1,5,2,3);
//
//    filter(t1,1,24);
//    filter(t3,1);
//    filter(t3,1,4);
    return 0;
}