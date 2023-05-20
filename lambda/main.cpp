#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <utility>

void quadratic_solver();

int main(){

    auto sqr_func = [](double v)-> double{ return v * v; };

    double rs = sqr_func(2);
    
    std::cout << "Square: " << rs << std::endl;
    rs = sqr_func(5);
    std::cout << "Square: " << rs << std::endl;

    quadratic_solver();
    return 0;
}


void quadratic_solver(){

    auto solve = [](double a, double b, double c) -> std::pair<double, double>{
        double num = b*b - 4*a*c;
        std::pair<double, double> ret(NAN, NAN);
        if(num >= 0.0){
            num = sqrt(num);
            ret.first = (-b + num)/(2 *a);
            ret.second = (-b - num)/(2 *a);
        }
        return ret;
    };


    std::pair<double, double> ans = solve(3.0, 5.9, -8.1);
    std::cout << "Roots of first equation are: ";
    std::cout << ans.first << " & " << ans.second << std::endl;
    ans = solve(1.0,-4.0, 4.0);
    std::cout << "Roots of second equation are: ";
    std::cout << ans.first << " & " << ans.second << std::endl;

}
