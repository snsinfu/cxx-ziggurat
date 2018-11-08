#include <algorithm>
#include <iterator>
#include <random>
#include <type_traits>
#include <vector>

#include <ziggurat.hpp>

#include <catch.hpp>


TEST_CASE("standard_normal_distribution - is usable with float type")
{
    std::mt19937_64 random;
    cxx::standard_normal_distribution<float> normal;

    float sample = normal(random);

    CHECK(sample == sample);
}

TEST_CASE("standard_normal_distribution - is usable with double type")
{
    std::mt19937_64 random;
    cxx::standard_normal_distribution<double> normal;

    double sample = normal(random);

    CHECK(sample == sample);
}

TEST_CASE("standard_normal_distribution - generates zero-centered samples")
{
    std::mt19937_64 random;
    cxx::standard_normal_distribution<double> normal;

    constexpr int sample_count = 1000;
    double mean = 0;

    for (int i = 0; i < sample_count; i++) {
        mean += normal(random);
    }
    mean /= sample_count;

    CHECK(mean == Approx(0).margin(0.1));
}

TEST_CASE("standard_normal_distribution - generates unit variance samples")
{
    std::mt19937_64 random;
    cxx::standard_normal_distribution<double> normal;

    constexpr int sample_count = 1000;
    double var = 0;

    for (int i = 0; i < sample_count; i++) {
        double sample = normal(random);
        var += sample * sample;
    }
    var /= sample_count;

    CHECK(var == Approx(1).epsilon(0.1));
}

TEST_CASE("standard_normal_distribution - generates positive and negative numbers")
{
    std::mt19937_64 random;
    cxx::standard_normal_distribution<double> normal;

    constexpr int sample_count = 1000;
    double pos_ratio = 0;

    for (int i = 0; i < sample_count; i++) {
        if (normal(random) >= 0) {
            pos_ratio++;
        }
    }
    pos_ratio /= sample_count;

    CHECK(pos_ratio == Approx(0.5).epsilon(0.1));
}

TEST_CASE("standard_normal_distribution - generates normally distributed numbers")
{
    std::mt19937_64 random;
    cxx::standard_normal_distribution<double> normal;

    constexpr int sample_count = 5000;

    std::vector<double> samples;
    std::generate_n(std::back_inserter(samples), sample_count, [&] {
        return normal(random);
    });
    std::sort(samples.begin(), samples.end());

    // KS test (two-sided, 1%)
    double const critical_value = 1.63 / std::sqrt(sample_count);

    double D = 0;
    int rank = 0;
    for (double x : samples) {
        rank++;
        double const sample_cdf = rank / double(sample_count);
        double const normal_cdf = 1 - std::erfc(x / std::sqrt(2)) / 2;
        D = std::max(D, std::fabs(sample_cdf - normal_cdf));
    }

    CHECK(D < critical_value);
}

TEST_CASE("standard_normal_distribution::result_type - is the template argument")
{
    using D1 = cxx::standard_normal_distribution<float>;
    using D2 = cxx::standard_normal_distribution<double>;

    CHECK(std::is_same<D1::result_type, float>::value);
    CHECK(std::is_same<D2::result_type, double>::value);
}

TEST_CASE("standard_normal_distribution::param_type - is empty and comparable")
{
    using D = cxx::standard_normal_distribution<double>;
    using P = D::param_type;

    P p1;
    P p2;

    CHECK(p1 == p2);
    CHECK_FALSE(p1 != p2);

    CHECK(std::is_same<P::distribution_type, D>::value);
}
