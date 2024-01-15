#pragma once

#include <array>
#include <cstddef>

template<typename T, std::size_t N>
constexpr std::array<T, N> bubble_sort(std::array<T, N> array) {
    std::size_t end = array.size();
    for (std::size_t i = end; i > 0; --i) {
        for (std::size_t j = 0; j < i - 1; ++j) {
            T& current = array[j];
            T& next = array[j + 1];
            if (current > next) {
                std::swap(current, next);
            }
        }
    }
    return array;
}

static_assert(bubble_sort(std::array<std::size_t, 3>{3, 2, 1}) == std::array<std::size_t, 3>{1, 2, 3});