// http://burtleburtle.net/bob/rand/smallprng.html

#include <cstddef>
#include <cstdint>
#include <limits>


namespace detail
{
    template<typename Integer>
    inline Integer rotate(Integer x, unsigned n)
    {
        constexpr std::size_t bits = std::numeric_limits<Integer>::digits;

        // (x >> bits) is UB. https://stackoverflow.com/q/18918256
        if (n == 0) {
            return x;
        }
        return Integer(x << n) | Integer(x >> (bits - n));
    }
}

template<
    typename Word,
    unsigned Rotation_1,
    unsigned Rotation_2,
    unsigned Rotation_3,
    Word FixedSeed,
    unsigned long long InitialRound
>
class jenkins_small_fast_engine
{
    static constexpr unsigned rotation_1 = Rotation_1;
    static constexpr unsigned rotation_2 = Rotation_2;
    static constexpr unsigned rotation_3 = Rotation_3;
    static constexpr Word fixed_seed = FixedSeed;
    static constexpr unsigned long long initial_round = InitialRound;

    static constexpr std::size_t word_bits = std::numeric_limits<Word>::digits;
    static_assert(rotation_1 < word_bits, "parameter out of range");
    static_assert(rotation_2 < word_bits, "parameter out of range");
    static_assert(rotation_3 < word_bits, "parameter out of range");

public:
    using result_type = Word;

    static inline constexpr result_type min()
    {
        return 0;
    }

    static inline constexpr result_type max()
    {
        return std::numeric_limits<result_type>::max();
    }

    explicit jenkins_small_fast_engine(result_type seed_val = 0)
    {
        seed(seed_val);
    }

    void seed(result_type seed_val = 0)
    {
        state_a_ = fixed_seed;
        state_b_ = state_c_ = state_d_ = seed_val;
        discard(initial_round);
    }

    inline result_type operator()()
    {
        using detail::rotate;

        auto& a = state_a_;
        auto& b = state_b_;
        auto& c = state_c_;
        auto& d = state_d_;

        auto const e = a - rotate(b, rotation_1);
        a = b ^ rotate(c, rotation_2);
        b = c + rotate(d, rotation_3);
        c = d + e;
        d = e + a;

        return d;
    }

    void discard(unsigned long long z)
    {
        for (; z != 0; --z) {
            (*this)();
        }
    }

    friend bool operator==(
        jenkins_small_fast_engine const& lhs,
        jenkins_small_fast_engine const& rhs
    )
    {
        return lhs.state_a_ == rhs.state_a_ &&
               lhs.state_b_ == rhs.state_b_ &&
               lhs.state_c_ == rhs.state_c_ &&
               lhs.state_d_ == rhs.state_d_;
    }

    friend bool operator!=(
        jenkins_small_fast_engine const& lhs,
        jenkins_small_fast_engine const& rhs
    )
    {
        return !(lhs == rhs);
    }

    template<typename Char, typename CharTraits>
    friend std::basic_ostream<Char, CharTraits>& operator<<(
        std::basic_ostream<Char, CharTraits>& output_stream,
        jenkins_small_fast_engine const& engine
    )
    {
        Char const space = output_stream.widen(' ');

        output_stream << engine.state_a_ << space
                      << engine.state_b_ << space
                      << engine.state_c_ << space
                      << engine.state_d_;

        return output_stream;
    }

    template<typename Char, typename CharTraits>
    friend std::basic_istream<Char, CharTraits>& operator>>(
        std::basic_istream<Char, CharTraits>& input_stream,
        jenkins_small_fast_engine& engine
    )
    {
        result_type tmp[4];
        if (input_stream >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3]) {
            engine.state_a_ = tmp[0];
            engine.state_b_ = tmp[1];
            engine.state_c_ = tmp[2];
            engine.state_d_ = tmp[3];
        }
        return input_stream;
    }

private:
    result_type state_a_ = 0;
    result_type state_b_ = 0;
    result_type state_c_ = 0;
    result_type state_d_ = 0;
};

using jsf32 = jenkins_small_fast_engine<std::uint32_t, 27, 17, 0, 0xf1ea5eed, 20>;
using jsf64 = jenkins_small_fast_engine<std::uint64_t, 39, 11, 0, 0xf1ea5eed, 20>;
