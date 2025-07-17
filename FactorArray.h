//
// Created by googl on 17.07.2025.
//

#ifndef FACTORARRAY_H
#define FACTORARRAY_H

#include "IArray.h"

template <typename T>
class FactorArray : public IArray<T>{
protected:
    uint32_t get_new_capacity() override;
};


template <typename T>
uint32_t FactorArray<T>::get_new_capacity()
{
    return this->m_capacity == 0 ? 1 : this->m_capacity * 2;
}
#endif //FACTORARRAY_H
