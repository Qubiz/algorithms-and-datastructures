#include <array>

#include <boost/ut.hpp>

#include "bubble_sort.hpp"
#include "search.hpp"

int main() {
    using namespace boost::ut;
    {
        // Array linear search
        const std::array<int, 5> array{4, 3, 2, 1, 0};
        const auto span = std::span<const int>(array);
        expect(1_u == linear_search(span, 3).value());
        expect(!linear_search(span, 5).has_value());
    }

    {
        // Binary search regular
        const std::array<std::size_t, 10> array{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        const auto span = std::span<const std::size_t>(array);
        for (std::size_t i = 0; i < array.size(); ++i) {
            expect(i == binary_search(span, i).value());
        }
        expect(!binary_search(span, std::size_t{10}).has_value());
    }

    {
        const std::array<bool, 10> array{false, false, false, false, false, false, false, false, true, true};
        expect(8_i == crystal_balls_linear(array).value());
        expect(8_i == crystal_balls_binary_and_linear(array).value());
        expect(8_i == crystal_balls_general(array).value());


        const std::array<bool, 10> array2{true, true, true, true, true, true, true, true, true, true};
        expect(0_i == crystal_balls_linear(array2).value());
        expect(0_i == crystal_balls_binary_and_linear(array2).value());
        expect(0_i == crystal_balls_general(array2).value());

        const std::array<bool, 10> array3{false, false, false, false, false, false, false, false, false, true};
        expect(9_i == crystal_balls_linear(array3).value());
        expect(9_i == crystal_balls_binary_and_linear(array3).value());
        expect(9_i == crystal_balls_general(array3).value());

        const std::array<bool, 10> array4{false, false, false, false, false, false, false, false, false, false};
        expect(!crystal_balls_linear(array4).has_value());
        expect(!crystal_balls_binary_and_linear(array4).has_value());
        expect(!crystal_balls_general(array4).has_value());

        const std::array<bool, 1> array5{true};
        expect(0_i == crystal_balls_linear(array5).value());
        expect(0_i == crystal_balls_binary_and_linear(array5).value());
        expect(0_i == crystal_balls_general(array5).value());
    }
}