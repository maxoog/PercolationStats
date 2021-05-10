#include "Percolation.h"

#include <cmath>
#include <iostream>

Percolation::Percolation(const size_t dimension)
    : size(dimension)
    , data(pow(dimension, 2), 'c')
{
}

void Percolation::open(const size_t row, const size_t column)
{
    if (!is_open(row, column)) {
        data[row * size + column] = 'o';
        open_sells_num++;
        if (row == 0 || near_full(row, column)) {
            enfull_nearest(row, column);
        }
    }
}

bool Percolation::is_open(const size_t row, const size_t column) const
{
    return data[row * size + column] == 'o' || is_full(row, column);
}

bool Percolation::is_full(const size_t row, const size_t column) const
{
    if (!valid(row, column)) {
        return false;
    }
    return data[row * size + column] == 'f';
}

size_t Percolation::get_numbet_of_open_cells() const
{
    return open_sells_num;
}

bool Percolation::has_percolation() const
{
    return has_leaked;
}

void Percolation::print() const
{
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            std::cout << data[i * size + j];
        }
        std::cout << '\n';
    }
    std::cout << open_sells_num << '\n';
}

bool Percolation::valid(const size_t row, const size_t column) const
{
    return row >= 0 && row < size &&
            column >= 0 && column < size;
}

void Percolation::enfull_nearest(const size_t row, const size_t column)
{
    if (valid(row, column) && data[row * size + column] == 'o') {
        enfull(row, column);
        enfull_nearest(row + 1, column);
        enfull_nearest(row - 1, column);
        enfull_nearest(row, column + 1);
        enfull_nearest(row, column - 1);
    }
}

void Percolation::enfull(const size_t row, const size_t column)
{
    data[row * size + column] = 'f';
    if (row == size - 1) {
        has_leaked = true;
    }
}

bool Percolation::near_full(const size_t row, const size_t column) const
{
    return is_full(row - 1, column) || is_full(row + 1, column) || is_full(row, column - 1) || is_full(row, column + 1);
}
