#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

using StrVec = std::vector<std::string>;
using Ip_Tuple = std::tuple<int,int,int,int>;

Ip_Tuple to_tuple(const std::vector<std::string>& c)
{
    return std::make_tuple(std::stoi(c.at(0)),
                           std::stoi(c.at(1)),
                           std::stoi(c.at(2)),
                           std::stoi(c.at(3)));
};

void print(const StrVec & ip)
{
    std::cout<<ip.at(0)<<"."
             <<ip.at(1)<<"."
             <<ip.at(2)<<"."
             <<ip.at(3)<<std::endl;
}

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void filtered(const StrVec& vs,const std::vector<int>& vi)
{
    for (int i = 0; i < vi.size(); ++i) {
        if (std::stoi((vs).at(i)) != vi.at(i))
            return;
    }
    print(vs);
}

template<typename... Args>
void filter(const std::vector<StrVec>& ip_pool, Args... args)
{
    std::vector<int> filters = {args...};

    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        filtered(*ip, filters);
}


void filter_any(const std::vector<StrVec>& ip_pool, int f)
{
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        if(std::stoi((*ip).at(0))==f || std::stoi((*ip).at(1))==f ||
                std::stoi((*ip).at(2))==f || std::stoi((*ip).at(3))==f)
            print(*ip);
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<StrVec> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            StrVec v = split(line, '\t');
            ip_pool.push_back( split(v.at(0), '.') );
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(),ip_pool.end(),[](auto begin, auto end)
        {
            return to_tuple(begin)>to_tuple(end);
        });

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            print(*ip);
        }
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        filter(ip_pool,1);
        //ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        filter(ip_pool,46,70);
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output

        filter_any(ip_pool,46);
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
