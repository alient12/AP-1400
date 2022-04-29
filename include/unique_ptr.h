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

private:
    T *_p;
};
#include "unique_ptr.hpp"
#endif //UNIQUE_PTR