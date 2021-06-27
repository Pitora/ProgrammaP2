template<class T>
class DeepPtr {
private:
    T* ptr;
public:
    DeepPtr(const T* x = 0) : ptr(x ? new T(*x) : 0) {}
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
};