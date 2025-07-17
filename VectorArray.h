//
// Created by googl on 17.07.2025.
//

#ifndef VECTORARRAY_H
#define VECTORARRAY_H

#include "IArray.h"

template <typename T>
class VectorArray : public IArray<T>{
protected:
    uint32_t get_new_capacity();

};


template <typename T>
uint32_t VectorArray<T>::get_new_capacity()
{
    return this->m_capacity + 10;
}
#endif //VECTORARRAY_H
