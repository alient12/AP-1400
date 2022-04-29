template <typename T>
SharedPtr<T>::SharedPtr(T *p)
{
    _p = p;
    _count = new int(1);
}

template <typename T>
SharedPtr<T>::SharedPtr()
{
    _p = nullptr;
    _count = new int(1);
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    if (_count != nullptr)
    {
        if (*_count == 1)
        {
            delete _p;
            _p = nullptr;
            delete _count;
            _count = nullptr;
        }
        else
        {
            *_count -= 1;
        }
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &sp)
{
    _p = sp._p;
    _count = sp._count;
    (*_count)++;
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr &sp)
{
    if (this != &sp)
    {
        if (_count != nullptr)
        {
            if (*_count == 1)
            {
                delete _p;
                _p = nullptr;
                delete _count;
                _count = nullptr;
            }
            else
            {
                *_count -= 1;
            }
        }
        _p = sp._p;
        _count = sp._count;
        (*_count)++;
    }
    return *this;
}

template <typename T>
T *SharedPtr<T>::get() const
{
    return _p;
}

template <typename T>
const T &SharedPtr<T>::operator*() const
{
    return *_p;
}

template <typename T>
T &SharedPtr<T>::operator*()
{
    return *_p;
}

template <typename T>
T *SharedPtr<T>::operator->()
{
    return _p;
}

template <typename T>
void SharedPtr<T>::reset()
{
    if (_count != nullptr)
    {
        if (*_count == 1)
        {
            delete _p;
            _p = nullptr;
            delete _count;
            _count = nullptr;
        }
        else
        {
            *_count -= 1;
        }
    }
}

template <typename T>
void SharedPtr<T>::reset(T *p)
{
    if (_count != nullptr)
    {
        if (*_count == 1)
        {
            delete _p;
            _p = nullptr;
            delete _count;
            _count = nullptr;
        }
        else
        {
            *_count -= 1;
        }
    }
    _p = p;
    _count = new int(1);
}

template <typename T>
T *SharedPtr<T>::release()
{
    if (_count != nullptr)
    {
        if (*_count == 1)
        {
            delete _p;
            _p = nullptr;
            delete _count;
            _count = nullptr;
        }
        else
        {
            *_count -= 1;
        }
    }
    return _p;
}

template <typename T>
SharedPtr<T>::operator bool() const
{
    return _p != nullptr;
}

template <typename T>
int SharedPtr<T>::use_count() const
{
    if (_count != nullptr)
    {
        return *_count;
    }
    else
    {
        return 0;
    }
}

template <typename T>
SharedPtr<T> make_shared(T t)
{
    return SharedPtr<T>(new T(t));
}