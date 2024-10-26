#include"callback.h"
#include"common.h"

template <class T>
Callback<T>::Callback(T *pObj, void (T::*pCallback)())
{
    if(!pObj)
    {
        LOG_ERROR("pObj is NULL");
        fatalError("null pointer passed", "Callback<T>::Callback");
    }
    if(!pCallback)
    {
        LOG_ERROR("pCallback is NULL");
        fatalError("null pointer passed", "Callback<T>::Callback");
    }

    this->pObj = pObj;
    this->pCallback = pCallback;
}

template <class T>
void Callback<T>::call()
{
    pObj->pCallback();
}

template <class T>
Callback<T>::~Callback()
{
    ;
}