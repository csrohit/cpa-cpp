#ifndef _SHARED_H

#define _SHARED_H

template <typename T>
class Wrapper{

    template<typename>
    friend class cpa_Shared;
public:
    Wrapper(T* p): ptr(p), rc(1) {}
    ~Wrapper(){ delete ptr; }

private:
    T* ptr;
    unsigned int rc;
};



template <typename T>
class cpa_Shared{
public:
    cpa_Shared(T *p):pW(new Wrapper<T>(p)){}

    /* copy constructor for move semantics */
    cpa_Shared(cpa_Shared &&) = default;

    /* shallow copy constructor */
    cpa_Shared(const cpa_Shared & other){
        pW = other.pW;
        pW->rc += 1;
    };

    /* move semantics */
    cpa_Shared &operator=(cpa_Shared &&) = default;

    T* operator->(){
        return pW->ptr;
    }

    T& operator*(){
        return *pW->ptr;
    }

    /* overload assignement operator */
    cpa_Shared &operator=(const cpa_Shared & other){
        if(--pW->rc == 0){
            delete pW;
        }
        pW = other.pW;
        pW->rc += 1;
        return *this;
    };

    /* destructor */
    ~cpa_Shared(){
        if(--pW->rc == 0){
            delete pW;
        }
    }
    T* get(){ return pW->ptr; }
    unsigned int count(){ return pW->rc; }

private:

   Wrapper<T>* pW; 
    
};


#endif // !_SHARED_H
