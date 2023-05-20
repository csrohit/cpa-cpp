#include <cstdio>
#include <iostream>



void using_outer_functions_locals();
void capture_by_value();
void capture_by_reference();



int main(){
    printf("size of long: %lu\n", sizeof(long));
    using_outer_functions_locals();
    return 0;
}




void using_outer_functions_locals(){

    int m = 100, n=200, p = 300;

    [n, p](){
        std::cout << "Value of n: " << n << std::endl;
        std::cout << "Value of p: " << p << std::endl;
    }();

    capture_by_value();
    capture_by_reference();
}


/**
 * @brief demo for capture_by_value for lambda functions
 */
void capture_by_value(){
    int m = 100, n=200, p = 300;
    auto f = [=](){
        std::cout << "Capture by Value [n]: " <<  n << std::endl;
        std::cout << "Capture by Reference [p]: " << p << std::endl;
    };

    f();
    n = 600;
    p = 400;
    f();
}


/**
 * @brief dmeo for capture by reference function for lambda
 */
void capture_by_reference(){
    int m = 100, n=200, p = 300;

    auto f = [&](){
        std::cout << "Capture by Reference [n]: " <<  n << std::endl;
        std::cout << "Capture by Value [p]: " <<  p << std::endl;
    };

    f();
    n = 600;
    p = 400;
    f();
}
