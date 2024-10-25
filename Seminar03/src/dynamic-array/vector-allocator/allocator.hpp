#pragma once
#include <stddef.h>
#include <utility>

template <class T>
class allocator
{
public:
    T *allocate(size_t n) const;
    void deallocate(T *ptr, size_t n) const;

    template <class... Args>
    void construct(T *ptr, Args &&...args) const;
    void destroy(T *ptr) const;

    void copy_range(T* begin_destination, T* begin_source, T* end_source) const;
    void move_range(T *begin_destination, T *begin_source, T *end_source) const;

    template <class... Args>
    void construct_range(T *begin, T *end, Args &&...args) const;
    void destroy_range(T *begin, T *end) const;
};

// allocates uninitialized storage 
template <class T>
T *allocator<T>::allocate(size_t n) const
{
    if(n == 0)
        return nullptr;
    
    return static_cast<T *>(::operator new(n * sizeof(T)));
}

// Deallocates the storage referenced by the pointer ptr, 
// which must be a pointer obtained by an earlier call to allocate()
template <class T>
void allocator<T>::deallocate(T *ptr, size_t n) const
{
    if (!n)
        return;

    ::operator delete(ptr, n * sizeof(T));
}

// destructs an object in allocated storage 
template <class T>
void allocator<T>::destroy(T *ptr) const
{
    ptr->~T();
}

template <class T>
template <class... Args>
void allocator<T>::construct(T *ptr, Args &&...args) const
{
    ::new (ptr) T(std::forward<Args>(args)...);
}

// constructs an object in allocated storage 
template <class T>
template <class... Args>
void allocator<T>::construct_range(T *begin, T *end, Args &&...args) const
{
    while (begin != end)
    {
        construct(begin, std::forward<Args>(args)...);
        ++begin;
    }
}

// calls destroy on a range.
template <class T>
void allocator<T>::destroy_range(T *begin, T *end) const
{
    while (begin != end)
    {
        destroy(begin);
        ++begin;
    }
}

// calls construct on a range.
template<class T>
void allocator<T>::copy_range(T* begin_destination, T* begin_source, T* end_source) const
{
    while(begin_source != end_source)
    {
        construct(begin_destination, *begin_source);
        ++begin_source;
        ++begin_destination;
    }
}

// calls construct using std::move on a range.
template <class T>
void allocator<T>::move_range(T *begin_destination, T *begin_source, T *end_source) const
{
    while (begin_source != end_source)
    {
        construct(begin_destination, std::move(*begin_source));
        ++begin_source;
        ++begin_destination;
    }
}