#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <type_traits>
#include <utility>


namespace
{
    template<typename F, typename T, typename P>
    std::pair<T, T> bisect(F func, T min, T max, P stop)
    {
        T fmin = func(min);
        T fmax = func(max);

        while (!stop(min, max)) {
            T const mid = (min + max) / 2;
            T const fmid = func(mid);

            if (fmid * fmin < 0) {
                max = mid;
                fmax = fmid;
            } else {
                min = mid;
                fmin = fmid;
            }
        }

        return std::make_pair(min, max);
    }

    template<typename F, typename T>
    std::pair<T, T> find_bracket(
        F func,
        T seed,
        typename std::common_type<T>::type delta,
        typename std::common_type<T>::type scale
    )
    {
        T min = seed;
        T max = seed;

        do {
            min = (min - delta) / scale;
            max = (max + delta) * scale;
        } while (func(min) * func(max) >= 0);

        return std::make_pair(min, max);
    }
}

namespace
{
    constexpr auto reciprocal_gauss = double(0.39894228040143267793994605993438186847585863116493);
    constexpr auto reciprocal_sqrt2 = double(0.70710678118654752440084436210484903928483593768847);
    constexpr auto tau = double(6.2831853071795864769252867665590057683943387987502);

    double density(double x)
    {
        return reciprocal_gauss * std::exp(-x * x / 2);
    }

    double inverse_density(double p)
    {
        return std::sqrt(-std::log(tau * p * p));
    }

    double tail_mass(double x)
    {
        return std::erfc(reciprocal_sqrt2 * x) / 2;
    }

    template<typename URNG>
    double sample_from_tail(double a, URNG& engine)
    {
        std::exponential_distribution<double> expdist;
        double x;
        double y;
        do {
            x = expdist(engine) / a;
            y = expdist(engine);
        } while (2 * y < x * x);
        return a + x;
    }
}

int main()
{
    constexpr int table_bits = 7;
    constexpr int strip_count = (1 << table_bits) + 1;

    double table[strip_count] = {};

    // Build the table of strip edges.

    auto build_table = [&](double edge) {
        auto const strip_area = edge * density(edge) + tail_mass(edge);

        table[0] = strip_area / density(edge);
        table[1] = edge;

        auto const upper_bound = density(0);
        auto current_top = density(edge);

        for (int i = 1; i < strip_count - 1; i++) {
            current_top += strip_area / table[i];
            if (current_top > upper_bound) {
                return false;
            }

            table[i + 1] = inverse_density(current_top);
        }

        return true;
    };

    auto objective = [&](double x) {
        return build_table(x) ? table[strip_count - 1] : -1;
    };

    auto stop_condition = [&](double min, double max) {
        return std::nextafter(min, max) >= max;
    };

    constexpr auto bracket_seed = double(1);
    constexpr auto extension_rate = double(1.1);

    auto const bracket = find_bracket(objective, bracket_seed, 0, extension_rate);
    auto const roots = bisect(objective, bracket.first, bracket.second, stop_condition);

    build_table(roots.second);

    for (int i = 0; i < strip_count; i++) {
        if (i > 0 && i % 4 == 0) {
            std::cout << '\n';
        }
        std::cout << "T(" << std::setprecision(18) << table[i] << "), ";
    }
    std::cout << '\n';
}
