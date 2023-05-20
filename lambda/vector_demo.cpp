#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>


void mean(std::vector<int> &ivec);
void rms(std::vector<int> &ivec);
int main(){
    int choice, num;
    std::vector<int> ivec;

    ivec.push_back(100);

    while (1) {
        std::cout << "Do you want to continue? [1: Yes | 0: No]:";
        std::cin >> choice;

        if(choice == 0){
            break;
        }

        std::cout << "Enter next integer: ";
        std::cin >> num;

        ivec.push_back(num);
    }
    
    /* print vector elements */
    
    for (std::vector<int>::size_type i=0; i < ivec.size(); i++) {
        std::cout << ivec.at(i) << " "; 
    }

    std::cout << std::endl;

    for (std::vector<int>::iterator itr = ivec.begin(); itr < ivec.end(); itr++) {
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
    
    mean(ivec);
    rms(ivec);
    return 0;
}


void mean(std::vector<int> &ivec){
    
    double_t m = [](std::vector<int> & v)-> double_t {

        if(v.size() == 0){
            return 0;
        }

        int sum = 0;
        for (std::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr) {
            sum += *itr;
        }
        return ((double_t)sum)/v.size();
    }(ivec);
    std::cout << "mean: " << m << std::endl;
}

void rms(std::vector<int> &ivec){

    double_t val = [](std::vector<int> &vect) -> double_t{
        if(vect.size() == 0){
            return 0;
        }
        int sum = 0;
        for (std::vector<int>::iterator itr = vect.begin(); itr != vect.end(); ++itr) {
            sum += (*itr)*(*itr);
        }
        return sqrt(((double_t)sum)/vect.size());
    }(ivec);
    

    std::cout << "RMS: " << val << std::endl;
}
