#include <iostream>
#include <vector>
#include "filter.h"


template <typename T>
std::function<double(std::vector<T>)> mean_arithmatic = [](std::vector<T> input_vec)->double{

    if(input_vec.size()){
        T sum = reduce<T>(
                [](T acc, T val){ return (acc + val);},
                input_vec,
                (T)0
            );
        /**
         * 1. Possible loss of floating point precision if sum is non-float
         * 2. Possible loss of data if sum exceeds double limit
         */
        return ((double)sum/input_vec.size());
    }else{
        return 0.0;
    }
};


template <typename T>
std::function<double(std::vector<T>)>root_mean_square = [](std::vector<T> input_vec)->double{
    if(input_vec.size()){
        auto sum_square = reduce<T>(
                [](T acc, T val)->T{ return (acc + val);},
                map<T, T>(
                    [](T val)->auto{ return (val * val);},
                    input_vec
                ),
                0.0
            );
        double mean_sum_square = (double) sum_square / input_vec.size();
        return sqrt(mean_sum_square);
    }else {
        return 0;
    }
};

template <typename T>
std::function<std::vector<T>(T, T)> range = [](T start, T end)->std::vector<T>{
    std::vector<T> out_vec;
    for (typename std::vector<T>::size_type i = start; i < end; ++i) {
        out_vec.push_back(i);
    }
    return out_vec;
};

template <typename T>
/* not sure of factorial of non integer values */
auto factorial = [](T val)->auto
    {
        if(val == 0 && val == 1){
            return 1;
        }
        return reduce<T>(
            [](T acc, T val) -> auto
            {
                return (acc * val);
            },
            range<T>(1, val + 1),
            1
        );
    }; 

template <typename T>

auto q4 = [](std::vector<T> input_vec)->auto{
    return reduce<T>(
        [](T acc, T val){ return ( acc * val); },
        map<T, T>(
            [](T val)
            {
                return val % 2 == 0 && val >= 1 && val <= 10
                        ? val * val * val
                        : val % 2 != 0 && val >= 1
                            ? (val * val + 1)
                            : 1;
            },
            filter<T>(
                [](T val){ return (val <= 20 ? true: false); }
            )
        )
    );
};


int main(){
    
    std::vector<int> input_vec;

    for (uint8_t i = 1; i != 51; ++i) {
        input_vec.push_back(i);
    }

    int sum = reduce<int>(
            [](int acc, int val) -> int {return (acc + val);},
            map<int, int>(
                [](int val){ return (val * val);},
                filter<int>(
                    [](int val){ return (val % 2 == 0 ? true: false);},
                    input_vec
                )
            ),
            0
        );

    /* Sum of sqares of even numbers [1, 50] */
    std::cout << "Result of Q0: " << sum << std::endl;
    
    std::cout << "Result of Q1: " << mean_arithmatic<int>(input_vec) << std::endl; 

    std::cout << "Result of Q2: " << root_mean_square<int>(input_vec) << std::endl; 
    
    std::cout << "Result of Q3: " << factorial<int>(5) << std::endl; 

    return 0;
}
