#ifndef _CPA_SHARED_PTR_

#define _CPA_SHARED_PTR_
#include <stdint.h>
template <typename T>
class cpa_SharedPtr
{

   private:
        T* ptr;
        uint32_t rc;

public:
    cpa_SharedPtr( T*p): ptr(p), rc(1){};

    cpa_SharedPtr(cpa_SharedPtr<T> &&) = default;
    cpa_SharedPtr(const cpa_SharedPtr<T> &) = default;
    cpa_SharedPtr &operator=(cpa_SharedPtr<T> &&) = default;
    cpa_SharedPtr &operator=(const cpa_SharedPtr<T> &) = default;
    ~cpa_SharedPtr(){
            delete ptr;
        }

};


#endif // !_CPA_SHARED_PTR_
