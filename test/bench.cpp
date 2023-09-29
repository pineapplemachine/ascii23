#include <ascii23.h>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#define CHAR_BENCHMARK(char_fn) \
    ch = 0; \
    ankerl::nanobench::Bench().run(#char_fn, [&] { \
        const auto i = char_fn((ch++) & 0xff); \
        ankerl::nanobench::doNotOptimizeAway(i); \
    });
    
int main() {
    int ch;
    CHAR_BENCHMARK(ascii::is_char)
    CHAR_BENCHMARK(ascii::is_alpha_char)
    CHAR_BENCHMARK(ascii::is_alpha_lower_char)
    CHAR_BENCHMARK(ascii::is_alpha_upper_char)
    CHAR_BENCHMARK(ascii::is_digit_char)
    CHAR_BENCHMARK(ascii::is_hex_digit_char)
    CHAR_BENCHMARK(ascii::is_hex_digit_lower_char)
    CHAR_BENCHMARK(ascii::is_hex_digit_upper_char)
    CHAR_BENCHMARK(ascii::is_word_char)
    CHAR_BENCHMARK(ascii::is_word_lower_char)
    CHAR_BENCHMARK(ascii::is_word_upper_char)
    CHAR_BENCHMARK(ascii::is_word_start_char)
    CHAR_BENCHMARK(ascii::is_word_lower_start_char)
    CHAR_BENCHMARK(ascii::is_word_upper_start_char)
    CHAR_BENCHMARK(ascii::is_punctuation_char)
    CHAR_BENCHMARK(ascii::is_whitespace_char)
    CHAR_BENCHMARK(ascii::is_blank_char)
    CHAR_BENCHMARK(ascii::is_null_char)
    CHAR_BENCHMARK(ascii::is_control_char)
    CHAR_BENCHMARK(ascii::is_printable_char)
    CHAR_BENCHMARK(ascii::is_graphical_char)
    CHAR_BENCHMARK(ascii::to_lower_char)
    CHAR_BENCHMARK(ascii::to_upper_char)
    return 0;
}
