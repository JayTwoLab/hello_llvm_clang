#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <format>
#include <expected>    // C++23 std::expected

// Global Point type using C++23/26 "deducing this" feature.
// This cannot be placed inside a function (local class)
// because template member functions are not allowed in local classes.
struct Point
{
    int x{0};
    int y{0};

    // C++23/26: "deducing this" syntax
    auto move(this Point self, int dx, int dy)
    {
        self.x += dx;
        self.y += dy;
        return self;
    }
};

std::string make_message()
{
    std::string result;

    // ------------------------------------------------------------
    // C++20: ranges + std::format
    // ------------------------------------------------------------
    {
        std::vector<int> nums = {1, 2, 3, 4, 5};

        // Range pipeline: filter even numbers, then square them
        auto even_square_view =
            nums
            | std::views::filter([](int x) { return x % 2 == 0; })
            | std::views::transform([](int x) { return x * x; });

        int sum = 0;
        for (int v : even_square_view)
            sum += v;

        result += std::format("[C++20] Sum of even squares = {}\n", sum);
    }

    // ------------------------------------------------------------
    // C++23: std::expected + views::join
    // ------------------------------------------------------------
    {
        // Safe division using std::expected
        auto safe_div = [](int a, int b) -> std::expected<int, std::string> {
            if (b == 0)
                return std::unexpected("Division by zero");
            return a / b;
        };

        auto r = safe_div(10, 2);

        if (r.has_value())
            result += std::format("[C++23] safe_div OK: {}\n", r.value());
        else
            result += std::format("[C++23] safe_div error: {}\n", r.error());

        // Join view to flatten nested containers
        std::vector<std::vector<int>> nested = {{1, 2}, {3, 4}};
        auto flat = nested | std::views::join;

        int s = 0;
        for (int v : flat)
            s += v;

        result += std::format("[C++23] Flattened vector sum = {}\n", s);
    }

    // ------------------------------------------------------------
    // C++26: deducing this + enhanced formatting
    // ------------------------------------------------------------
    {
        Point p{10, 20};
        Point q = p.move(5, 7);  // Calls deducing-this member function

        result += std::format("[C++26] Point move: ({}, {}) → ({}, {})\n",
                              p.x, p.y, q.x, q.y);

        // Enhanced formatting in C++26 (implementation-dependent)
        result += std::format("[C++26] Formatting example: {:.3f}\n", 3.1415926535);
    }

    return result;
}

int main()
{
    std::cout << make_message();
    return 0;
}
