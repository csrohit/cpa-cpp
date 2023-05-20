#ifndef FILTER_H
#define FILTER_H


#include <functional>
#include <vector>


/**
 * @brief 
 *
 * @tparam T_IN 
 * @tparam T_OUT 
 */
template<typename T_IN, typename T_OUT>
std::function<std::vector<T_OUT>(std::function<T_OUT(T_IN)>, std::vector<T_IN>)> map = [](std::function<T_OUT(T_IN)> kernel, std::vector<T_IN> vec)->std::vector<T_OUT>{
    
    std::vector<T_OUT> ret;

    for (typename std::vector<T_IN>::size_type i = 0; i != vec.size(); ++i ) {
        ret.push_back(kernel(vec[i]));
    }
    return ret;
};

template<typename T_IN>
std::function<std::vector<int>(std::function<bool(int)>, std::vector<int>)> filter = [](std::function<bool(T_IN)> kernel, std::vector<T_IN> vec) ->std::vector<T_IN>{
    std::vector<T_IN> ret;
    
    for (typename std::vector<T_IN>::size_type i = 0; i != vec.size(); ++i ) {
        
        if(true == kernel(vec[i])){
            ret.push_back(vec[i]);
        }
    }
    return ret;
};


template<typename T>
std::function<T(std::function<T(T,T)>, std::vector<T>, T)> reduce = [](std::function<T(T, T)> reducer, std::vector<T> vec, T initial ) -> T{
   for(typename std::vector<T>::size_type i = 0; i != vec.size(); ++i){
        initial = reducer(initial, vec[i]);
    } 
    return initial;
};

#endif // !FILTER_H
