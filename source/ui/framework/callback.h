#pragma once

class _DefaultCallback
{
    public:
        _DefaultCallback();
        ~_DefaultCallback();
    private:
        ;
};

template <class T = _DefaultCallback>
class Callback
{
    public:
        Callback(T*, void (T::*)());
        ~Callback();
        void call();
    private:
        T *pObj;
        void (*pCallback)();
};