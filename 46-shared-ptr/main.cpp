#include "iostream"
#include "shared.h"
class Date
{
    private:
        int day, month, year;
    public:
        Date(int init_day, int init_month, int init_year) : day(init_day),
                                                            month(init_month),
                                                            year(init_year)
        {

        }

        void show() const
        {
            std::cout << day << "-" << month << "-" << year << std::endl; 
        }
}; 

int main(){

    cpa_Shared<Date> sp1(new Date(5, 4, 2023));
    cpa_Shared<Date> sp5(new Date(6, 7, 2026));
    cpa_Shared<Date> sp2(sp1);
    cpa_Shared<Date> sp3(sp2);

    std::cout << "Reference count sp1: " << sp1.count() << std::endl;
    if(sp1.get() == sp3.get()){
        std::cout << "sp1 and sp2 are shared" << std::endl;
    }
    sp2 = sp5;
    std::cout << "Reference count sp1: " << sp1.count() << std::endl;
    std::cout << "Reference count sp2: " << sp2.count() << std::endl;
    sp2->show();
    (*sp1).show();

    return 0;
}
