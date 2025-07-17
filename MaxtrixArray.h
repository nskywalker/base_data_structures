//
// Created by googl on 17.07.2025.
//

#ifndef MAXTRIXARRAY_H
#define MAXTRIXARRAY_H
#include <cstdint>
#include <cstring>
#include <utility>

template <typename T>
class MaxtrixArray {
    T** m_data = nullptr;
    uint32_t m_size = 0;
    uint32_t m_capacity = 0;
    static std::pair<uint32_t, uint32_t> getRowCol(uint32_t index);
    void moveRowRight(uint32_t row_num, uint32_t col_num, uint32_t col);
public:
    static constexpr uint32_t row_length = 10;
    MaxtrixArray() = default;
    ~MaxtrixArray();
    void add(T item, uint32_t index);
    T remove(uint32_t index);
    uint32_t size() const { return m_size; }
    T& operator[](uint32_t index);
    const T& operator[](uint32_t index) const {return static_cast<MaxtrixArray*>(this)->operator[](index);}
};


template <typename T>
std::pair<uint32_t, uint32_t> MaxtrixArray<T>::getRowCol(uint32_t index)
{
    return std::make_pair(index / row_length, index % row_length);
}

template <typename T>
void MaxtrixArray<T>::moveRowRight(uint32_t row_num, uint32_t col_num, uint32_t col)
{
    for (auto i = col_num; i > col; --i) {
        m_data[row_num][i] = m_data[row_num][i - 1];
    }
}

template <typename T>
MaxtrixArray<T>::~MaxtrixArray() {
    for (auto i = 0ul; i < m_size / row_length; ++i) {
        delete[] m_data[i];
    }
    delete[] m_data;
}

template <typename T>
void MaxtrixArray<T>::add(T item, uint32_t index)
{
    if (index > m_size)
    {
        return;
    }
    auto [row, col] = getRowCol(index);
    auto [row_num, col_num] = getRowCol(m_size);
    auto [row_cap, col_cap] = getRowCol(m_capacity);

    if (m_capacity - m_size > 0) {
        if (row_num == row) {
            moveRowRight(row_num, col_num, col);
        } else {
            moveRowRight(row_num, col_num, 0);
            m_data[row_num][0] = m_data[row_num - 1][row_length - 1];
            for (auto r = row_num - 1; r > row; --r) {
                moveRowRight(r, row_length - 1, 0);
                m_data[r][0] = m_data[r - 1][row_length - 1];
            }
            moveRowRight(row, row_length - 1, col);
        }
        m_data[row][col] = item;
    } else if (m_size == m_capacity) {
        auto new_row = new T[row_length];
        auto arr = new T*[row_cap + 1];
        m_capacity += row_length;
        std::memcpy(arr, m_data, row_num * sizeof(T*));
        delete[] m_data;
        m_data = arr;
        m_data[row_cap] = new_row;

        if (m_size == 0) {
            new_row[col] = item;
        } else {
            for (auto r = row_num ; r > row; --r) {
                moveRowRight(r, row_length - 1, 0);
                m_data[r][0] = m_data[r - 1][row_length - 1];
            }
            moveRowRight(row, row_length - 1, col);
            m_data[row][col] = item;
        }
    }
    ++m_size;
}

template <typename T>
T MaxtrixArray<T>::remove(uint32_t index)
{
    if (index < m_size) {
        auto [row, col] = getRowCol(index);
        auto [row_num, col_num] = getRowCol(m_size);
        if (col_num == 0) {
            row_num -= 1;
            col_num = row_length;
        }
        auto dst = m_data[row] + col;
        auto res = *dst;
        if (row_num == row) {
            std::memmove(dst, dst + 1, (col_num - col - 1) * sizeof(T));
        } else {
            std::memmove(dst, dst + 1, (row_length - col - 1) * sizeof(T));
            m_data[row][row_length - 1] = m_data[row + 1][0];
            for (auto r = row + 1; r < row_num; ++r) {
                dst = m_data[r];
                std::memmove(dst, dst + 1, (row_length - 1) * sizeof(T));
                m_data[r][row_length - 1] = m_data[r + 1][0];
            }
            dst = m_data[row_num];
            std::memmove(dst, dst + 1, (col_num - 1) * sizeof(T));
        }
        --m_size;
        return res;
    }
    return T{};
}

template <typename T>
T& MaxtrixArray<T>::operator[](uint32_t index)
{
    auto [row, col] = getRowCol(index);
    return m_data[row][col];
}
#endif //MAXTRIXARRAY_H
