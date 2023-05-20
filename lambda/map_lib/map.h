#ifndef MAP_H
#define MAP_H

#include <functional>
#include <vector>

template<typename T_IN, typename T_OUT>

auto map = [](std::function<T_OUT(T_IN)> kernel, std::vector<T_IN> vec)->std::vector<T_OUT>{
    
    std::vector<T_OUT> ret;

    for (std::vector<T_IN> i = 0; i != vec.size(); ++i ) {
        ret.push_back(kernel(vec[i]));
    }
    return ret;
};

#endif // !MAP_H
