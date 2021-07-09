#ifndef TDEEP_H
#define TDEEP_H

#include<iostream>


template<class T>
class DeepPtr {
private:
    T* ptr;
public:
    DeepPtr(){}
    DeepPtr(const T* x) : ptr(x ? (*x).clone() : 0) {}
    DeepPtr(const DeepPtr& x) : ptr(x.ptr ? (*(x.ptr)).clone() : 0) {}
    ~DeepPtr() {if (ptr != nullptr)delete ptr;}

    DeepPtr& operator= (const DeepPtr& x)
    {
        if (this != &x)
        {
            delete ptr;
            ptr = x.ptr ? (*(x.ptr)).clone() : 0;
        }
        return *this;
    }  

    bool operator== (const DeepPtr& x) const {return ptr == x.ptr;}

    friend std::ostream& operator<<(std::ostream& s, const DeepPtr& o) {
        s<<*(o.ptr)<<std::endl;
        return s;
    }

    T& operator* () const {return *ptr;}

    T* operator->() const {return &(*ptr);}
};

#endif 