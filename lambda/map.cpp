#include <functional>
#include <iostream>
#include <vector>
        

void map_lambda_demo();
void filter_demo();

int main(){
    
    // map_lambda_demo();

    filter_demo();

    return (0);
}



void map_lambda_demo(){

    std::function<std::vector<int>(std::function<int(int)>, std::vector<int>)> f = [](std::function<int(int)> map_kernel, std::vector<int> vec)->std::vector<int>{
        std::vector<int> ret;
        for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++) {
            ret.push_back(map_kernel(*itr));
        }
        return ret;
    };

    std::vector<int> vec = f([](int x)->int{return x*x;}, std::vector<int>{1,2,3,4,5});


    for (std::vector<int>::size_type i = 0; i != vec.size(); ++i) {
        std::cout << vec.at(i) << std::endl;
    }
}

void filter_demo(){

    std::function<std::vector<int>(std::function<bool(int)>, std::vector<int>)> f= [](std::function<bool(int)> kernel, std::vector<int> vec)->std::vector<int>{
       std::vector<int> ret;

        for (std::vector<int>::size_type i = 0; i != vec.size(); ++i) {
            if(kernel(vec[i]) == true){
                ret.push_back(vec[i]);
            }
        }
        return ret;
    };

    std::vector<int> vec = f([](int x)->bool{ return (x % 2 == 0 ? true: false);}, std::vector<int>{1,2,3,4,5});


    for (std::vector<int>::size_type i = 0; i != vec.size(); ++i) {
        std::cout << vec.at(i) << std::endl;
    }

}

