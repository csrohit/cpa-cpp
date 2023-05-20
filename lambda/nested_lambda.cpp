#include <functional>
#include <iostream>


void test();
void factory_function_demo();

int main(){
    // test();
    factory_function_demo();

    return (0);
}


void test()
{
    std::function<std::function<int(int)>()> f = []()->std::function<int(int)>{
        int n = 3;
        
        return [n](int x)->int{
            int rs = 1;
            for(int i = 0; i < n; ++i){
                rs = rs * x;
            }
            return rs;
        };
    };

    std::function<int(int)> cube_func = f();
    std::cout << "cube_func(5) = " << cube_func(5) << std::endl;
    std::cout << "cube_func(7) = " << cube_func(7) << std::endl;
    std::cout << "f()(5) = " << f()(5) << std::endl;
    std::cout << "f()(7) = " << f()(7) << std::endl;
}


void factory_function_demo(){
    
    auto power_function_factory = [](int n)->std::function<int(int)>{

        return [n](int x)-> int{
            int ret = 1;
            for(int i = 0; i < n; ++i){
                ret = ret * x;
            }
            return ret;
        };
    };


    std::function<int(int)> square = power_function_factory(2);
    std::function<int(int)> cube = power_function_factory(3);

    std::cout << "Square of 4: " << square(4) << std::endl;
    std::cout << "Cube of 4: " << cube(4) << std::endl;
    

}
