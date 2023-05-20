#include <cmath>
#include <utility>
#include <iostream>



int main(){

    std::pair<double, double> p(100.0, 200.0);


    std::cout << "FIrst number: " << p.first << std::endl;
    std::cout << "Second number: " << p.second<< std::endl;

    p.first = NAN;
    p.second = NAN;



    std::cout << "first number: " << p.first << std::endl;
    std::cout << "Second number: " << p.second << std::endl;

    return 0;

}
