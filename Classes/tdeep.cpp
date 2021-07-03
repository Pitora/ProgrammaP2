#ifndef TDEEP_H
#define TDEEP_H


template<class T>
class DeepPtr {
private:
    T* ptr;
public:
    DeepPtr(){}
    DeepPtr(const T* x) : ptr(x ? new T(*x) : 0) {}
    DeepPtr(const DeepPtr& x) : ptr(x.ptr ? new T(*(x.ptr)) : 0) {}
    ~DeepPtr() {delete ptr;}

    DeepPtr& operator= (const DeepPtr& x)
    {
        if (this != &x)
        {
            delete ptr;
            ptr = x.ptr ? new T(*(x.ptr)) : 0;
        }
        return *this;
    }  

    bool operator== (const DeepPtr& x) const {return ptr == x.ptr;}
    T& operator* () const {return *ptr;}

    T* operator->() const {return &(ptr);}
};

#endif 