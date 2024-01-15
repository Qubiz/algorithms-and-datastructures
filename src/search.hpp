#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <optional>

/**
 * Perform a linear search on an array
 * Time complexity: O(N)
 */
template<typename T>
constexpr std::optional<std::size_t> linear_search(std::span<const T> haystack, const T &needle) {
    for (std::size_t i = 0; i < haystack.size(); ++i) {
        if (haystack[i] == needle) {
            return i;
        }
    }
    return std::nullopt;
}

/**
 * Calculates the midpoint
 * @param low
 * @param high
 * @return
 */
constexpr std::size_t midpoint(std::size_t low, std::size_t high) {
    return low + (high - low) / 2;
}
static_assert(midpoint(0, 0) == 0);
static_assert(midpoint(0, 1) == 0);
static_assert(midpoint(0, 2) == 1);
static_assert(midpoint(0, 10) == 5);

/**
 * Perform a binary search on an array
 * Time complexity: O(log N)
 *
 * [low, high]
 */
template<typename T>
constexpr auto binary_search(std::span<const T> haystack, T needle) -> std::optional<std::size_t> {
    std::size_t low = 0;
    std::size_t high = haystack.size();
    do {
        std::size_t m = midpoint(low, high);
        const T &value = haystack[m];
        if (needle == value) {
            return m;
        } else if (needle > value) {
            low = m + 1;
        } else {
            high = m;
        }
    } while (low < high);
    return std::nullopt;
}

// --- The two crystal ball problem ---
// Given two crystal balls that will break if dropped from high enough
// distance, determine the exact spot in which it will break in the most
// optimal way.
// [f,f,f,f,f,f,f,t,t,t,t,t,t,t,t]

/**
 * Linear search the first floor on which the crystal ball breaks
 * Time complexity: O(N)
 */
constexpr auto crystal_balls_linear(std::span<const bool> floors) -> std::optional<std::size_t> {
    return linear_search(floors, true);
}

/**
 * Use two balls: binary search then linear search
 * Time complexity: O(N)
 */
constexpr auto crystal_balls_binary_and_linear(std::span<const bool> floors) -> std::optional<std::size_t> {
    const auto first_ball = binary_search(floors, true);
    if (!first_ball) {
        return std::nullopt;
    }

    const auto second_ball = linear_search(floors.subspan(0, first_ball.value()), true);
    if (!second_ball) {
        return first_ball.value();
    }

    return second_ball.value();
}

/**
 * Jump sqrt(N) until we find the first point where we encounter 'true'.
 * Then jump backwards sqrt(N) and walk forwards until we encounter another 'true'.
 * Time complexity: O(sqrt(N))
 */
constexpr auto crystal_balls_general(std::span<const bool> floors) -> std::optional<std::size_t> {
    if (floors.empty()) {
        return std::nullopt;
    }

    if (floors.size() == 1 && floors[0]) {
        if (floors[0]) {
            return 0;
        } else {
            return std::nullopt;
        }
    }

    const std::size_t jump_size = std::floor(std::sqrt(floors.size()));
    std::size_t i = jump_size;
    for (; i < floors.size(); i += jump_size) {
        if (floors[i + jump_size]) {
            break;
        }
    }

    if (i >= floors.size()) {
        return std::nullopt;
    }

    // Found a floor where it breaks
    // Walk backwards sqrt(N)
    i -= jump_size;

    for (; i < i + jump_size; ++i) {
        if (floors[i]) {
            return i;
        }
    }

    return std::nullopt;
}
