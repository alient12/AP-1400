#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr
{
public:
    SharedPtr(T *p);
    SharedPtr();
    ~SharedPtr();
    SharedPtr(const SharedPtr &);
    SharedPtr &operator=(const SharedPtr &);
    T *get() const;
    const T& operator*() const;
    T& operator*();
    T* operator->();
    void reset();
    void reset(T *p);
    T *release();
    explicit operator bool() const;
    int use_count() const;
private:
    T *_p;
    int *_count;
};

#include "shared_ptr.hpp"
#endif //SHARED_PTR