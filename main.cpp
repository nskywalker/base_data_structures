#include <iostream>
#include "SingleArray.h"
#include "FactorArray.h"
#include "VectorArray.h"
#include "MaxtrixArray.h"

int main()
{
    MaxtrixArray<int> va;
    for (int i = 0; i < 10; i++)
        va.add(i, i);
    va.add(99, 5);
    for (auto i = 0ul; i < va.size(); i++)
        std::cout << va[i] << std::endl;
}