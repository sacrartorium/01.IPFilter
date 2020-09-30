#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    auto start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void lexicographic_reverse_sort(std::vector<std::vector<std::string> >& vec)
{
    std::sort(vec.begin(), vec.end(), [](auto& a, auto& b) 
                                        {
                                            unsigned long ai[] = {std::stoul(a[0]), std::stoul(a[1]), std::stoul(a[2]), std::stoul(a[3])};
                                            unsigned long bi[] = {std::stoul(b[0]), std::stoul(b[1]), std::stoul(b[2]), std::stoul(b[3])};
                                        
                                            if (ai[0] < bi[0]) return false;
                                            else if (ai[0] == bi[0])
                                            {
                                                if (ai[1] < bi[1]) return false;
                                                else if (ai[1] == bi[1])
                                                {
                                                    if (ai[2] < bi[2]) return false;
                                                    else if (ai[2] == bi[2]) return !(ai[3] < bi[3]);                    
                                                }
                                            }
                                            return true;
                                        });
    
    for(auto ip = vec.cbegin(); ip != vec.cend(); ++ip)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
}

void filter(std::vector<std::vector<std::string> >& vec, unsigned short limit1)
{
    const auto limits1 = std::to_string(limit1);
    
    for(auto ip = vec.cbegin(); ip != vec.cend(); ++ip)
        {
            if(*(ip->begin()) != limits1) continue;
            
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
}

void filter(std::vector<std::vector<std::string> >& vec, unsigned short limit1, unsigned short limit2)
{
    const auto limits1 = std::to_string(limit1);
    const auto limits2 = std::to_string(limit2);
    
    for(auto ip = vec.cbegin(); ip != vec.cend(); ++ip)
        {
            if(*(ip->begin()) != limits1) continue;
            if(*(std::next(ip->begin(), 1)) != limits2) continue;
            
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
}

void filter_any(std::vector<std::vector<std::string> >& vec, unsigned short limit)
{
    const auto limits = std::to_string(limit);
    
    for(auto ip = vec.cbegin(); ip != vec.cend(); ++ip)
        if(    (*std::next(ip->begin(), 0) == limits)
            || (*std::next(ip->begin(), 1) == limits)
            || (*std::next(ip->begin(), 2) == limits)
            || (*std::next(ip->begin(), 3) == limits))
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
}

int main()
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        lexicographic_reverse_sort(ip_pool);

        filter(ip_pool, 1);
        
        filter(ip_pool, 46, 70);
        
        filter_any(ip_pool, 46);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
