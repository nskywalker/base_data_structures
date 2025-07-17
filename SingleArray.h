//
// Created by googl on 17.07.2025.
//

#ifndef SINGLEARRAY_H
#define SINGLEARRAY_H

#include "IArray.h"

template <typename T>
class SingleArray : public IArray<T> {
protected:
   uint32_t get_new_capacity() override;
public:
    SingleArray();
    ~SingleArray() override = default;
};


template <typename T>
uint32_t SingleArray<T>::get_new_capacity()
{
    return this->m_capacity + 1;
}

template <typename T>
SingleArray<T>::SingleArray() : IArray<T>()
{
}
#endif //SINGLEARRAY_H
