#include<iostream>

template <typename T>
UniquePtr<T>::UniquePtr(T *p)
{
    _p = p;
}

template <typename T>
UniquePtr<T>::UniquePtr()
{
    _p = nullptr;
}

template <typename T>
UniquePtr<T>::~UniquePtr()
{
    delete _p;
    _p = nullptr;
}

template <typename T>
T * UniquePtr<T>::get() const
{
    return _p;
}

template <typename T>
const T& UniquePtr<T>::operator*() const
{
  return *_p;
}

template <typename T>
T& UniquePtr<T>::operator*()
{
  return *_p;
}