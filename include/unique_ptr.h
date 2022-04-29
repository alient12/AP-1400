#ifndef UNIQUE_PTR
#define UNIQUE_PTR


template <typename T>
class UniquePtr 
{
public:
    UniquePtr(T *p);
    UniquePtr();
    ~UniquePtr();
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;
    T *get() const;
    const T& operator*() const;
    T& operator*();
    T* operator->();
    void reset();
    void reset(T *p);
    T *release();
    explicit operator bool() const;

private:
    T *_p;
};
#include "unique_ptr.hpp"
#endif //UNIQUE_PTR