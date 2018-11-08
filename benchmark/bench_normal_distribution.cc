#include <chrono>
#include <iostream>
#include <random>

#include <ziggurat.hpp>

#include "jsf.hpp"


constexpr int generation_count = 10000000;

struct measurement_result
{
    double time;
    double mean;
};

std::ostream& operator<<(std::ostream& os, measurement_result result)
{
    return os << result.time * 1e9 << " ns/gen\t" << result.mean;
}

template<typename URNG, typename D>
__attribute__((noinline))
measurement_result measure(URNG& random, D distr)
{
    using value_type = typename D::result_type;
    using clock = std::chrono::steady_clock;

    auto start_time = clock::now();
    auto sum = value_type(0);

    for (int i = 0; i < generation_count; i++) {
        sum += distr(random);
    }

    auto end_time = clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(
        end_time - start_time
    );

    measurement_result result;
    result.time = elapsed_time.count() / generation_count;
    result.mean = sum / generation_count;
    return result;
}

int main()
{
    std::mt19937_64 mt64;
    std::mt19937 mt32;
    jsf64 jsf;

    std::cout << "double\n";
    std::cout << "MT64 std       " << measure(mt64, std::normal_distribution<double>{}) << '\n';
    std::cout << "MT64 ziggurat  " << measure(mt64, cxx::standard_normal_distribution<double>{}) << '\n';
    std::cout << "MT32 std       " << measure(mt32, std::normal_distribution<double>{}) << '\n';
    std::cout << "MT32 ziggurat  " << measure(mt32, cxx::standard_normal_distribution<double>{}) << '\n';
    std::cout << "JSF  std       " << measure(jsf, std::normal_distribution<double>{}) << '\n';
    std::cout << "JSF  ziggurat  " << measure(jsf, cxx::standard_normal_distribution<double>{}) << '\n';
    std::cout << '\n';
    std::cout << "float\n";
    std::cout << "MT64 std       " << measure(mt64, std::normal_distribution<float>{}) << '\n';
    std::cout << "MT64 ziggurat  " << measure(mt64, cxx::standard_normal_distribution<float>{}) << '\n';
    std::cout << "MT32 std       " << measure(mt32, std::normal_distribution<float>{}) << '\n';
    std::cout << "MT32 ziggurat  " << measure(mt32, cxx::standard_normal_distribution<float>{}) << '\n';
    std::cout << "JSF  std       " << measure(jsf, std::normal_distribution<float>{}) << '\n';
    std::cout << "JSF  ziggurat  " << measure(jsf, cxx::standard_normal_distribution<float>{}) << '\n';
}
