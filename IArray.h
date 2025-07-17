#ifndef IARRAY_H
#define IARRAY_H
#include <cstdint>
#include <cstring>


template <typename T>
class IArray {
    T* m_data = nullptr;
protected:
    uint32_t m_size = 0;
    uint32_t m_capacity = 0;
    virtual uint32_t get_new_capacity() = 0;
public:
    IArray() = default;
    virtual ~IArray() { delete[] m_data; }
    void add(T item, uint32_t index);
    T remove(uint32_t index);
    const T& operator[](uint32_t index) const {return m_data[index];}
    T& operator[](uint32_t index) {return m_data[index];}
    uint32_t size() const {return m_size;}
};

template <typename T>
void IArray<T>::add(T item, uint32_t index)
{
    if (index > m_size) {
        return;
    }
    if (m_capacity - m_size > 0) {
        for (auto i = static_cast<int>(m_size - 1ul); i >= static_cast<int>(index); --i) {
            m_data[i + 1] = m_data[i];
        }
        m_data[index] = item;
        ++m_size;
    } else if (m_size == m_capacity) {
        m_capacity = get_new_capacity();
        auto array = new T[m_capacity];
        std::memcpy(array, m_data, index * sizeof(T));
        std::memcpy(array + index + 1, m_data + index, (m_size - index) * sizeof(T));
        delete[] m_data;
        array[index] = item;
        m_data = array;
        ++m_size;
    }
}

template <typename T>
T IArray<T>::remove(uint32_t index)
{
    if (index < m_size)
    {
        T item = m_data[index];
        auto dst = m_data + index;
        std::memmove(dst, dst + 1, (m_size - index - 1) * sizeof(T));
        --m_size;
        return item;
    }
    return T{};
}
#endif //IARRAY_H
