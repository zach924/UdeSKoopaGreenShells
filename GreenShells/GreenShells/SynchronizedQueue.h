#pragma once

#include <mutex>
#include <vector>

using namespace std;

// http://h-deb.clg.qc.ca/Sources/zone_transit.html
//Modified to allow pushing a single object

template <class T>
class SynchronizedQueue
{
    mutex mut;
    vector<T> data;
    unique_lock<mutex> lockMutex() volatile
    {
        unique_lock<mutex> lock{ const_cast<mutex&>(mut) };
        return std::move(lock);
    }
public:
    template <class C>
    void push(const C &src)
    {
        push(begin(src), end(src));
    }
    void push(const T &src)
    {
        data.push_back(src);
    }
    template <class Itt>
    void push(Itt begin, Itt end)
    {
        data.insert(end(data), begin, end);
    }
    vector<T> pop()
    {
        using std::swap;
        vector<T> resultat;
        swap(resultat, data);
        return std::move(resultat);
    }
    template <class C>
    C pop() volatile
    {
        vector<T> res = pop();
        return C(begin(res), end(res));
    }
    template <class C>
    void push(const C &src) volatile
    {
        auto lock = lockMutex();
        const_cast<SynchronizedQueue<T>&>(*this).push(src);
    }
    template <class Itt>
    void push(Itt begin, Itt end) volatile
    {
        auto lock = lockMutex();
        const_cast<SynchronizedQueue<T>&>(*this).push(begin, end);
    }
    void push(const T &src) volatile
    {
        auto lock = lockMutex();
        const_cast<SynchronizedQueue<T>&>(*this).push(src);
    }
    vector<T> pop() volatile
    {
        auto lock = lockMutex();
        return const_cast<SynchronizedQueue<T>&>(*this).pop();
    }
    bool IsEmtpy()
    {
        return data.empty();
    }
};
