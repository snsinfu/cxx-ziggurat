#include <algorithm>
#include <cmath>
#include <iterator>
#include <random>
#include <sstream>
#include <type_traits>
#include <vector>

#include <ziggurat.hpp>

#include <catch.hpp>


TEST_CASE("ziggurat_normal_distribution::result_type - is the template argument")
{
    CHECK(std::is_same<cxx::ziggurat_normal_distribution<float>::result_type, float>::value);
    CHECK(std::is_same<cxx::ziggurat_normal_distribution<double>::result_type, double>::value);
}

TEST_CASE("ziggurat_normal_distribution::param_type - is default constructible")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float>::param_type param;

        CHECK(param.mean() == 0);
        CHECK(param.stddev() == 1);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double>::param_type param;

        CHECK(param.mean() == 0);
        CHECK(param.stddev() == 1);
    }
}

TEST_CASE("ziggurat_normal_distribution::param_type - constructible with mean")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float>::param_type param{3.4F};

        CHECK(param.mean() == 3.4F);
        CHECK(param.stddev() == 1);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double>::param_type param{3.4};

        CHECK(param.mean() == 3.4);
        CHECK(param.stddev() == 1);
    }
}

TEST_CASE("ziggurat_normal_distribution::param_type - constructible with mean and stddev")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float>::param_type param{3.4F, 5.6F};

        CHECK(param.mean() == 3.4F);
        CHECK(param.stddev() == 5.6F);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double>::param_type param{3.4, 5.6};

        CHECK(param.mean() == 3.4);
        CHECK(param.stddev() == 5.6);
    }
}

TEST_CASE("ziggurat_normal_distribution::param_type - is equality comparable")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float>::param_type p1{3.4F, 5.6F};
        cxx::ziggurat_normal_distribution<float>::param_type p2{3.4F, 5.6F};
        cxx::ziggurat_normal_distribution<float>::param_type p3{4.3F, 2.1F};

        CHECK(p1 == p2);
        CHECK(p2 == p1);

        CHECK(p1 != p3);
        CHECK(p3 != p1);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double>::param_type p1{3.4, 5.6};
        cxx::ziggurat_normal_distribution<double>::param_type p2{3.4, 5.6};
        cxx::ziggurat_normal_distribution<double>::param_type p3{4.3, 2.1};

        CHECK(p1 == p2);
        CHECK(p2 == p1);

        CHECK(p1 != p3);
        CHECK(p3 != p1);
    }
}

TEST_CASE("ziggurat_normal_distribution::param_type - exposes distribution type")
{
    SECTION("float")
    {
        using D = cxx::ziggurat_normal_distribution<float>;
        using P = D::param_type;

        CHECK(std::is_same<P::distribution_type, D>::value);
    }

    SECTION("double")
    {
        using D = cxx::ziggurat_normal_distribution<double>;
        using P = D::param_type;

        CHECK(std::is_same<P::distribution_type, D>::value);
    }
}

TEST_CASE("ziggurat_normal_distribution - is default constructible")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float> dist;

        CHECK(dist.mean() == 0);
        CHECK(dist.stddev() == 1);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double> dist;

        CHECK(dist.mean() == 0);
        CHECK(dist.stddev() == 1);
    }
}

TEST_CASE("ziggurat_normal_distribution - is constructible with mean")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float> dist{3.4F};

        CHECK(dist.mean() == 3.4F);
        CHECK(dist.stddev() == 1);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double> dist{3.4};

        CHECK(dist.mean() == 3.4);
        CHECK(dist.stddev() == 1);
    }
}

TEST_CASE("ziggurat_normal_distribution - is constructible with mean and stddev")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float> dist{3.4F, 5.6F};

        CHECK(dist.mean() == 3.4F);
        CHECK(dist.stddev() == 5.6F);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double> dist{3.4, 5.6};

        CHECK(dist.mean() == 3.4);
        CHECK(dist.stddev() == 5.6);
    }
}

TEST_CASE("ziggurat_normal_distribution - is constructible with param_type")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float>::param_type param{3.4F, 5.6F};
        cxx::ziggurat_normal_distribution<float> dist{param};

        CHECK(dist.mean() == 3.4F);
        CHECK(dist.stddev() == 5.6F);
        CHECK(dist.param() == param);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double>::param_type param{3.4, 5.6};
        cxx::ziggurat_normal_distribution<double> dist{param};

        CHECK(dist.mean() == 3.4);
        CHECK(dist.stddev() == 5.6);
        CHECK(dist.param() == param);
    }
}

TEST_CASE("ziggurat_normal_distribution - is equality comarable")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float> d1{1.2F, 3.4F};
        cxx::ziggurat_normal_distribution<float> d2{1.2F, 3.4F};
        cxx::ziggurat_normal_distribution<float> d3{4.3F, 2.1F};

        CHECK(d1 == d2);
        CHECK(d2 == d1);

        CHECK(d1 != d3);
        CHECK(d3 != d1);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double> d1{1.2, 3.4};
        cxx::ziggurat_normal_distribution<double> d2{1.2, 3.4};
        cxx::ziggurat_normal_distribution<double> d3{4.3, 2.1};

        CHECK(d1 == d2);
        CHECK(d2 == d1);

        CHECK(d1 != d3);
        CHECK(d3 != d1);
    }
}

TEST_CASE("ziggurat_normal_distribution - is copyable")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float> dist{1.2F, 3.4F};
        cxx::ziggurat_normal_distribution<float> copy = dist;

        CHECK(copy == dist);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double> dist{1.2, 3.4};
        cxx::ziggurat_normal_distribution<double> copy = dist;

        CHECK(copy == dist);
    }
}

TEST_CASE("ziggurat_normal_distribution::reset - is a function")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float> dist;
        dist.reset();
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double> dist;
        dist.reset();
    }
}

TEST_CASE("ziggurat_normal_distribution::param - resets parameters")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float> dist_1{1.2F, 3.4F};
        cxx::ziggurat_normal_distribution<float> dist_2{5.6F, 7.8F};

        CHECK(dist_1 != dist_2);

        dist_1.param(dist_2.param());

        CHECK(dist_1 == dist_2);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double> dist_1{1.2, 3.4};
        cxx::ziggurat_normal_distribution<double> dist_2{5.6, 7.8};

        CHECK(dist_1 != dist_2);

        dist_1.param(dist_2.param());

        CHECK(dist_1 == dist_2);
    }
}

TEST_CASE("ziggurat_normal_distribution::min/max - return infinity ends")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float> dist;

        CHECK(dist.min() < 0);
        CHECK(dist.max() > 0);

        CHECK(std::isinf(dist.min()));
        CHECK(std::isinf(dist.max()));
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double> dist;

        CHECK(dist.min() < 0);
        CHECK(dist.max() > 0);

        CHECK(std::isinf(dist.min()));
        CHECK(std::isinf(dist.max()));
    }
}

TEST_CASE("ziggurat_normal_distribution - generates valid numbers")
{
    SECTION("float")
    {
        std::mt19937_64 random;
        cxx::ziggurat_normal_distribution<float> normal;

        float const sample_1 = normal(random);
        float const sample_2 = normal(random);

        CHECK(sample_1 == sample_1);
        CHECK(sample_2 == sample_2);
    }

    SECTION("double")
    {
        std::mt19937_64 random;
        cxx::ziggurat_normal_distribution<double> normal;

        double const sample_1 = normal(random);
        double const sample_2 = normal(random);

        CHECK(sample_1 == sample_1);
        CHECK(sample_2 == sample_2);
    }
}

TEST_CASE("ziggurat_normal_distribution - generates samples with ad-hoc parameter")
{
    std::mt19937_64 random_1;
    std::mt19937_64 random_2;

    cxx::ziggurat_normal_distribution<double> dist{1.2, 3.4};
    cxx::ziggurat_normal_distribution<double>::param_type param{5.6, 7.8};

    double const sample_1 = dist(random_1);
    double const sample_2 = dist(random_2, param);

    CHECK(sample_2 == Approx((sample_1 - 1.2) / 3.4 * 7.8 + 5.6));
}

TEST_CASE("ziggurat_normal_distribution - generates samples with specified mean")
{
    std::mt19937_64 random;
    cxx::ziggurat_normal_distribution<double> dist{3.2, 1.0};

    constexpr int sample_count = 1000;
    double mean = 0;

    for (int i = 0; i < sample_count; i++) {
        mean += dist(random);
    }
    mean /= sample_count;

    CHECK(mean == Approx(dist.mean()).margin(0.1));
}

TEST_CASE("ziggurat_normal_distribution - generates samples with specified stddev")
{
    std::mt19937_64 random;
    cxx::ziggurat_normal_distribution<double> dist{1.2, 3.4};

    constexpr int sample_count = 1000;
    double var = 0;

    for (int i = 0; i < sample_count; i++) {
        double sample = dist(random);
        var += sample * sample;
    }
    var /= sample_count;

    CHECK(std::sqrt(var) == Approx(dist.stddev()).epsilon(0.1));
}

TEST_CASE("ziggurat_normal_distribution - generates positive and negative numbers")
{
    std::mt19937_64 random;
    cxx::ziggurat_normal_distribution<double> dist;

    constexpr int sample_count = 1000;
    double pos_ratio = 0;

    for (int i = 0; i < sample_count; i++) {
        if (dist(random) >= 0) {
            pos_ratio++;
        }
    }
    pos_ratio /= sample_count;

    CHECK(pos_ratio == Approx(0.5).epsilon(0.1));
}

TEST_CASE("ziggurat_normal_distribution - generates normally distributed numbers")
{
    std::mt19937_64 random;
    cxx::ziggurat_normal_distribution<double> normal;

    // Sampling
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

TEST_CASE("ziggurat_normal_distribution - is serializable and deserializable")
{
    SECTION("float")
    {
        cxx::ziggurat_normal_distribution<float> dist_1{1.2F, 3.4F};
        cxx::ziggurat_normal_distribution<float> dist_2;

        std::stringstream stream;
        stream << dist_1;
        stream >> dist_2;

        CHECK(dist_2 == dist_1);
    }

    SECTION("double")
    {
        cxx::ziggurat_normal_distribution<double> dist_1{1.2, 3.4};
        cxx::ziggurat_normal_distribution<double> dist_2;

        std::stringstream stream;
        stream << dist_1;
        stream >> dist_2;

        CHECK(dist_2 == dist_1);
    }
}

TEST_CASE("ziggurat_normal_distribution - is unchanged upon deserialization failure")
{
    cxx::ziggurat_normal_distribution<double> dist{1.2, 3.4};
    cxx::ziggurat_normal_distribution<double> saved = dist;

    std::istringstream in{"0.0 abc"};
    bool const ok = bool(in >> dist);

    CHECK_FALSE(ok);
    CHECK(dist == saved);
}
