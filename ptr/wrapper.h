#ifndef CPA_WRAPPER
#define CPA_WRAPPER

#include <stdint.h>


template <typename T>
class Wrapper
{
public:
    Wrapper();
    Wrapper(Wrapper &&) = default;
    Wrapper(const Wrapper &) = default;
    Wrapper &operator=(Wrapper &&) = default;
    Wrapper &operator=(const Wrapper &) = default;
    ~Wrapper();

private:
    T * ptr;
    uint32_t rc;
};

Wrapper::Wrapper(T* p): ptr(p)
{
}

Wrapper::~Wrapper()
{
}




#endif // !CPA_WRAPPER
