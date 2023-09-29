/**
 * This source file runs tests to verify the behavior of
 * functions defined in the ascii header.
 */

#include <ascii23.h>

#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

// Set up a test case, to be completed later with CHECK_CHAR_EPILOGUE.
#define CHECK_CHAR_PROLOGUE(char_fn) \
    const std::string char_fn_name = #char_fn;
    int chars_checked_array[128] = {};

// Conclude a test case, ensuring that every ASCII character is provided
// as an input to a tested function at least once.
#define CHECK_CHAR_EPILOGUE \
    int passed = 0; \
    for(int i = 0; i <= 0x7f; ++i) { \
        CHECK_MESSAGE(0 < chars_checked_array[i], "char: ", i); \
        passed += (0 < chars_checked_array[i] ? 1 : 0); \
    } \
    MESSAGE(char_fn_name, ": Checked ", passed, " ASCII chars"); \
    CHECK(128 == passed);

// Compare expected and actual output of a char function.
// The expected output is explicitly provided.
// Track the input, for later use with CHECK_CHAR_EPILOGUE.
#define CHECK_CHAR(input, expect, char_fn) \
    if(input >= 0 && input <= 0x7f) { \
        chars_checked_array[input]++; \
    } \
    CHECK(expect == char_fn(input));

// Compare expected and actual output of a char function.
// The output is expected to be the same as the input character.
// Track the input, for later use with CHECK_CHAR_EPILOGUE.
#define CHECK_CHAR_EXPECT_INPUT(input, char_fn) \
    CHECK_CHAR(input, input, char_fn)

// Compare expected and actual output for some non-ASCII values.
// The expected output is explicitly provided.
#define CHECK_CHAR_NON_ASCII(expect, char_fn) \
    CHECK_CHAR(-1, expect, char_fn) \
    CHECK_CHAR(-2, expect, char_fn) \
    CHECK_CHAR(-16, expect, char_fn) \
    CHECK_CHAR(-100, expect, char_fn) \
    CHECK_CHAR(-128, expect, char_fn) \
    CHECK_CHAR(-200, expect, char_fn) \
    CHECK_CHAR(-256, expect, char_fn) \
    CHECK_CHAR(-1000, expect, char_fn) \
    CHECK_CHAR(-1000000, expect, char_fn)

// Compare expected and actual output for some non-ASCII values.
// The output is expected to be the same as the input value.
#define CHECK_CHAR_NON_ASCII_EXPECT_INPUT(char_fn) \
    CHECK_CHAR_EXPECT_INPUT(-1, char_fn) \
    CHECK_CHAR_EXPECT_INPUT(-2, char_fn) \
    CHECK_CHAR_EXPECT_INPUT(-16, char_fn) \
    CHECK_CHAR_EXPECT_INPUT(-100, char_fn) \
    CHECK_CHAR_EXPECT_INPUT(-128, char_fn) \
    CHECK_CHAR_EXPECT_INPUT(-200, char_fn) \
    CHECK_CHAR_EXPECT_INPUT(-256, char_fn) \
    CHECK_CHAR_EXPECT_INPUT(-1000, char_fn) \
    CHECK_CHAR_EXPECT_INPUT(-1000000, char_fn)

// Compare expected and actual output for all control characters.
#define CHECK_CHAR_CONTROL(expect, char_fn) \
    CHECK_CHAR_NON_WHITESPACE_CONTROL(expect, char_fn) \
    CHECK_CHAR(0x09, expect, char_fn) \
    CHECK_CHAR(0x0a, expect, char_fn) \
    CHECK_CHAR(0x0b, expect, char_fn) \
    CHECK_CHAR(0x0c, expect, char_fn) \
    CHECK_CHAR(0x0d, expect, char_fn)

// Compare expected and actual output for all control characters
// that are not also whitespace characters.
#define CHECK_CHAR_NON_WHITESPACE_CONTROL(expect, char_fn) \
    CHECK_CHAR(0x00, expect, char_fn) \
    CHECK_CHAR(0x01, expect, char_fn) \
    CHECK_CHAR(0x02, expect, char_fn) \
    CHECK_CHAR(0x03, expect, char_fn) \
    CHECK_CHAR(0x04, expect, char_fn) \
    CHECK_CHAR(0x05, expect, char_fn) \
    CHECK_CHAR(0x06, expect, char_fn) \
    CHECK_CHAR(0x07, expect, char_fn) \
    CHECK_CHAR(0x08, expect, char_fn) \
    CHECK_CHAR(0x0e, expect, char_fn) \
    CHECK_CHAR(0x0f, expect, char_fn) \
    CHECK_CHAR(0x10, expect, char_fn) \
    CHECK_CHAR(0x11, expect, char_fn) \
    CHECK_CHAR(0x12, expect, char_fn) \
    CHECK_CHAR(0x13, expect, char_fn) \
    CHECK_CHAR(0x14, expect, char_fn) \
    CHECK_CHAR(0x15, expect, char_fn) \
    CHECK_CHAR(0x16, expect, char_fn) \
    CHECK_CHAR(0x17, expect, char_fn) \
    CHECK_CHAR(0x18, expect, char_fn) \
    CHECK_CHAR(0x19, expect, char_fn) \
    CHECK_CHAR(0x1a, expect, char_fn) \
    CHECK_CHAR(0x1b, expect, char_fn) \
    CHECK_CHAR(0x1c, expect, char_fn) \
    CHECK_CHAR(0x1d, expect, char_fn) \
    CHECK_CHAR(0x1e, expect, char_fn) \
    CHECK_CHAR(0x1f, expect, char_fn) \
    CHECK_CHAR(0x7f, expect, char_fn)

// Compare expected and actual output for all whitespace characters.
#define CHECK_CHAR_WHITESPACE(expect, char_fn) \
    CHECK_CHAR(' ', expect, char_fn) \
    CHECK_CHAR('\t', expect, char_fn) \
    CHECK_CHAR_NON_BLANK_WHITESPACE(expect, char_fn)

// Compare expected and actual output for all whitespace characters
// that are not also blank characters.
#define CHECK_CHAR_NON_BLANK_WHITESPACE(expect, char_fn) \
    CHECK_CHAR('\r', expect, char_fn) \
    CHECK_CHAR('\v', expect, char_fn) \
    CHECK_CHAR('\f', expect, char_fn) \
    CHECK_CHAR('\n', expect, char_fn)

// Compare expected and actual output for all decimal digit characters.
#define CHECK_CHAR_DIGIT(expect, char_fn) \
    CHECK_CHAR('0', expect, char_fn) \
    CHECK_CHAR('1', expect, char_fn) \
    CHECK_CHAR('2', expect, char_fn) \
    CHECK_CHAR('3', expect, char_fn) \
    CHECK_CHAR('4', expect, char_fn) \
    CHECK_CHAR('5', expect, char_fn) \
    CHECK_CHAR('6', expect, char_fn) \
    CHECK_CHAR('7', expect, char_fn) \
    CHECK_CHAR('8', expect, char_fn) \
    CHECK_CHAR('9', expect, char_fn)

// Compare expected and actual output for all alphabetical characters.
#define CHECK_CHAR_ALPHA(expect, char_fn) \
    CHECK_CHAR_ALPHA_LOWER(expect, char_fn) \
    CHECK_CHAR_ALPHA_UPPER(expect, char_fn)

// Compare expected and actual output for all lower-case alphabetical
// characters.
#define CHECK_CHAR_ALPHA_LOWER(expect, char_fn) \
    CHECK_CHAR_ALPHA_LOWER_HEX(expect, char_fn) \
    CHECK_CHAR_ALPHA_LOWER_NON_HEX(expect, char_fn)

// Compare expected and actual output for all lower-case alphabetical
// characters that are valid as hexadecimal digits.
#define CHECK_CHAR_ALPHA_LOWER_HEX(expect, char_fn) \
    CHECK_CHAR('a', expect, char_fn) \
    CHECK_CHAR('b', expect, char_fn) \
    CHECK_CHAR('c', expect, char_fn) \
    CHECK_CHAR('d', expect, char_fn) \
    CHECK_CHAR('e', expect, char_fn) \
    CHECK_CHAR('f', expect, char_fn)

// Compare expected and actual output for all lower-case alphabetical
// characters that are not valid as hexadecimal digits.
#define CHECK_CHAR_ALPHA_LOWER_NON_HEX(expect, char_fn) \
    CHECK_CHAR('g', expect, char_fn) \
    CHECK_CHAR('h', expect, char_fn) \
    CHECK_CHAR('i', expect, char_fn) \
    CHECK_CHAR('j', expect, char_fn) \
    CHECK_CHAR('k', expect, char_fn) \
    CHECK_CHAR('l', expect, char_fn) \
    CHECK_CHAR('m', expect, char_fn) \
    CHECK_CHAR('n', expect, char_fn) \
    CHECK_CHAR('o', expect, char_fn) \
    CHECK_CHAR('p', expect, char_fn) \
    CHECK_CHAR('q', expect, char_fn) \
    CHECK_CHAR('r', expect, char_fn) \
    CHECK_CHAR('s', expect, char_fn) \
    CHECK_CHAR('t', expect, char_fn) \
    CHECK_CHAR('u', expect, char_fn) \
    CHECK_CHAR('v', expect, char_fn) \
    CHECK_CHAR('w', expect, char_fn) \
    CHECK_CHAR('x', expect, char_fn) \
    CHECK_CHAR('y', expect, char_fn) \
    CHECK_CHAR('z', expect, char_fn)

// Compare expected and actual output for all upper-case alphabetical
// characters.
#define CHECK_CHAR_ALPHA_UPPER(expect, char_fn) \
    CHECK_CHAR_ALPHA_UPPER_HEX(expect, char_fn) \
    CHECK_CHAR_ALPHA_UPPER_NON_HEX(expect, char_fn)

// Compare expected and actual output for all upper-case alphabetical
// characters that are valid as hexadecimal digits.
#define CHECK_CHAR_ALPHA_UPPER_HEX(expect, char_fn) \
    CHECK_CHAR('A', expect, char_fn) \
    CHECK_CHAR('B', expect, char_fn) \
    CHECK_CHAR('C', expect, char_fn) \
    CHECK_CHAR('D', expect, char_fn) \
    CHECK_CHAR('E', expect, char_fn) \
    CHECK_CHAR('F', expect, char_fn)

// Compare expected and actual output for all upper-case alphabetical
// characters that are not valid as hexadecimal digits.
#define CHECK_CHAR_ALPHA_UPPER_NON_HEX(expect, char_fn) \
    CHECK_CHAR('G', expect, char_fn) \
    CHECK_CHAR('H', expect, char_fn) \
    CHECK_CHAR('I', expect, char_fn) \
    CHECK_CHAR('J', expect, char_fn) \
    CHECK_CHAR('K', expect, char_fn) \
    CHECK_CHAR('L', expect, char_fn) \
    CHECK_CHAR('M', expect, char_fn) \
    CHECK_CHAR('N', expect, char_fn) \
    CHECK_CHAR('O', expect, char_fn) \
    CHECK_CHAR('P', expect, char_fn) \
    CHECK_CHAR('Q', expect, char_fn) \
    CHECK_CHAR('R', expect, char_fn) \
    CHECK_CHAR('S', expect, char_fn) \
    CHECK_CHAR('T', expect, char_fn) \
    CHECK_CHAR('U', expect, char_fn) \
    CHECK_CHAR('V', expect, char_fn) \
    CHECK_CHAR('W', expect, char_fn) \
    CHECK_CHAR('X', expect, char_fn) \
    CHECK_CHAR('Y', expect, char_fn) \
    CHECK_CHAR('Z', expect, char_fn)

// Compare expected and actual output for all punctuation characters.
#define CHECK_CHAR_PUNCTUATION(expect, char_fn) \
    CHECK_CHAR('_', expect, char_fn) \
    CHECK_CHAR_NON_WORD_PUNCTUATION(expect, char_fn)

// Compare expected and actual output for all punctuation characters
// that are not word characters, i.e. except for the underscore.
#define CHECK_CHAR_NON_WORD_PUNCTUATION(expect, char_fn) \
    CHECK_CHAR('!', expect, char_fn) \
    CHECK_CHAR('"', expect, char_fn) \
    CHECK_CHAR('#', expect, char_fn) \
    CHECK_CHAR('$', expect, char_fn) \
    CHECK_CHAR('%', expect, char_fn) \
    CHECK_CHAR('&', expect, char_fn) \
    CHECK_CHAR('\'', expect, char_fn) \
    CHECK_CHAR('(', expect, char_fn) \
    CHECK_CHAR(')', expect, char_fn) \
    CHECK_CHAR('*', expect, char_fn) \
    CHECK_CHAR('+', expect, char_fn) \
    CHECK_CHAR(',', expect, char_fn) \
    CHECK_CHAR('-', expect, char_fn) \
    CHECK_CHAR('.', expect, char_fn) \
    CHECK_CHAR('/', expect, char_fn) \
    CHECK_CHAR(':', expect, char_fn) \
    CHECK_CHAR(';', expect, char_fn) \
    CHECK_CHAR('<', expect, char_fn) \
    CHECK_CHAR('=', expect, char_fn) \
    CHECK_CHAR('>', expect, char_fn) \
    CHECK_CHAR('?', expect, char_fn) \
    CHECK_CHAR('@', expect, char_fn) \
    CHECK_CHAR('[', expect, char_fn) \
    CHECK_CHAR('\\', expect, char_fn) \
    CHECK_CHAR(']', expect, char_fn) \
    CHECK_CHAR('^', expect, char_fn) \
    CHECK_CHAR('`', expect, char_fn) \
    CHECK_CHAR('{', expect, char_fn) \
    CHECK_CHAR('|', expect, char_fn) \
    CHECK_CHAR('}', expect, char_fn) \
    CHECK_CHAR('~', expect, char_fn)

TEST_CASE("is_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_char)
    for(int i = 0; i <= 0x7f; ++i) {
        CHECK_CHAR(i, true, ascii::is_char)
    }
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_alpha_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_alpha_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_alpha_char)
    CHECK_CHAR_CONTROL(false, ascii::is_alpha_char)
    CHECK_CHAR_DIGIT(false, ascii::is_alpha_char)
    CHECK_CHAR_ALPHA(true, ascii::is_alpha_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_alpha_char)
    CHECK_CHAR_PUNCTUATION(false, ascii::is_alpha_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_alpha_lower_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_alpha_lower_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_alpha_lower_char)
    CHECK_CHAR_CONTROL(false, ascii::is_alpha_lower_char)
    CHECK_CHAR_DIGIT(false, ascii::is_alpha_lower_char)
    CHECK_CHAR_ALPHA_LOWER(true, ascii::is_alpha_lower_char)
    CHECK_CHAR_ALPHA_UPPER(false, ascii::is_alpha_lower_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_alpha_lower_char)
    CHECK_CHAR_PUNCTUATION(false, ascii::is_alpha_lower_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_alpha_upper_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_alpha_upper_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_alpha_upper_char)
    CHECK_CHAR_CONTROL(false, ascii::is_alpha_upper_char)
    CHECK_CHAR_DIGIT(false, ascii::is_alpha_upper_char)
    CHECK_CHAR_ALPHA_LOWER(false, ascii::is_alpha_upper_char)
    CHECK_CHAR_ALPHA_UPPER(true, ascii::is_alpha_upper_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_alpha_upper_char)
    CHECK_CHAR_PUNCTUATION(false, ascii::is_alpha_upper_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_digit_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_digit_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_digit_char)
    CHECK_CHAR_CONTROL(false, ascii::is_digit_char)
    CHECK_CHAR_DIGIT(true, ascii::is_digit_char)
    CHECK_CHAR_ALPHA(false, ascii::is_digit_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_digit_char)
    CHECK_CHAR_PUNCTUATION(false, ascii::is_digit_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_hex_digit_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_hex_digit_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_hex_digit_char)
    CHECK_CHAR_CONTROL(false, ascii::is_hex_digit_char)
    CHECK_CHAR_DIGIT(true, ascii::is_hex_digit_char)
    CHECK_CHAR_ALPHA_LOWER_HEX(true, ascii::is_hex_digit_char)
    CHECK_CHAR_ALPHA_LOWER_NON_HEX(false, ascii::is_hex_digit_char)
    CHECK_CHAR_ALPHA_UPPER_HEX(true, ascii::is_hex_digit_char)
    CHECK_CHAR_ALPHA_UPPER_NON_HEX(false, ascii::is_hex_digit_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_hex_digit_char)
    CHECK_CHAR_PUNCTUATION(false, ascii::is_hex_digit_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_hex_digit_lower_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_hex_digit_lower_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_hex_digit_lower_char)
    CHECK_CHAR_CONTROL(false, ascii::is_hex_digit_lower_char)
    CHECK_CHAR_DIGIT(true, ascii::is_hex_digit_lower_char)
    CHECK_CHAR_ALPHA_LOWER_HEX(true, ascii::is_hex_digit_lower_char)
    CHECK_CHAR_ALPHA_LOWER_NON_HEX(false, ascii::is_hex_digit_lower_char)
    CHECK_CHAR_ALPHA_UPPER(false, ascii::is_hex_digit_lower_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_hex_digit_lower_char)
    CHECK_CHAR_PUNCTUATION(false, ascii::is_hex_digit_lower_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_hex_digit_upper_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_hex_digit_upper_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_hex_digit_upper_char)
    CHECK_CHAR_CONTROL(false, ascii::is_hex_digit_upper_char)
    CHECK_CHAR_DIGIT(true, ascii::is_hex_digit_upper_char)
    CHECK_CHAR_ALPHA_LOWER(false, ascii::is_hex_digit_upper_char)
    CHECK_CHAR_ALPHA_UPPER_HEX(true, ascii::is_hex_digit_upper_char)
    CHECK_CHAR_ALPHA_UPPER_NON_HEX(false, ascii::is_hex_digit_upper_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_hex_digit_upper_char)
    CHECK_CHAR_PUNCTUATION(false, ascii::is_hex_digit_upper_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_word_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_word_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_word_char)
    CHECK_CHAR_CONTROL(false, ascii::is_word_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_word_char)
    CHECK_CHAR_NON_WORD_PUNCTUATION(false, ascii::is_word_char)
    CHECK_CHAR_DIGIT(true, ascii::is_word_char)
    CHECK_CHAR_ALPHA(true, ascii::is_word_char)
    CHECK_CHAR('_', true, ascii::is_word_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_word_lower_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_word_lower_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_word_lower_char)
    CHECK_CHAR_CONTROL(false, ascii::is_word_lower_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_word_lower_char)
    CHECK_CHAR_NON_WORD_PUNCTUATION(false, ascii::is_word_lower_char)
    CHECK_CHAR_DIGIT(true, ascii::is_word_lower_char)
    CHECK_CHAR_ALPHA_LOWER(true, ascii::is_word_lower_char)
    CHECK_CHAR_ALPHA_UPPER(false, ascii::is_word_lower_char)
    CHECK_CHAR('_', true, ascii::is_word_lower_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_word_upper_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_word_upper_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_word_upper_char)
    CHECK_CHAR_CONTROL(false, ascii::is_word_upper_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_word_upper_char)
    CHECK_CHAR_NON_WORD_PUNCTUATION(false, ascii::is_word_upper_char)
    CHECK_CHAR_DIGIT(true, ascii::is_word_upper_char)
    CHECK_CHAR_ALPHA_LOWER(false, ascii::is_word_upper_char)
    CHECK_CHAR_ALPHA_UPPER(true, ascii::is_word_upper_char)
    CHECK_CHAR('_', true, ascii::is_word_upper_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_word_start_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_word_start_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_word_start_char)
    CHECK_CHAR_CONTROL(false, ascii::is_word_start_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_word_start_char)
    CHECK_CHAR_NON_WORD_PUNCTUATION(false, ascii::is_word_start_char)
    CHECK_CHAR_DIGIT(false, ascii::is_word_start_char)
    CHECK_CHAR_ALPHA(true, ascii::is_word_start_char)
    CHECK_CHAR('_', true, ascii::is_word_start_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_word_lower_start_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_word_lower_start_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_word_lower_start_char)
    CHECK_CHAR_CONTROL(false, ascii::is_word_lower_start_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_word_lower_start_char)
    CHECK_CHAR_NON_WORD_PUNCTUATION(false, ascii::is_word_lower_start_char)
    CHECK_CHAR_DIGIT(false, ascii::is_word_lower_start_char)
    CHECK_CHAR_ALPHA_LOWER(true, ascii::is_word_lower_start_char)
    CHECK_CHAR_ALPHA_UPPER(false, ascii::is_word_lower_start_char)
    CHECK_CHAR('_', true, ascii::is_word_lower_start_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_word_upper_start_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_word_upper_start_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_word_upper_start_char)
    CHECK_CHAR_CONTROL(false, ascii::is_word_upper_start_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_word_upper_start_char)
    CHECK_CHAR_NON_WORD_PUNCTUATION(false, ascii::is_word_upper_start_char)
    CHECK_CHAR_DIGIT(false, ascii::is_word_upper_start_char)
    CHECK_CHAR_ALPHA_LOWER(false, ascii::is_word_upper_start_char)
    CHECK_CHAR_ALPHA_UPPER(true, ascii::is_word_upper_start_char)
    CHECK_CHAR('_', true, ascii::is_word_upper_start_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_punctuation_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_punctuation_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_punctuation_char)
    CHECK_CHAR_CONTROL(false, ascii::is_punctuation_char)
    CHECK_CHAR_DIGIT(false, ascii::is_punctuation_char)
    CHECK_CHAR_ALPHA(false, ascii::is_punctuation_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_punctuation_char)
    CHECK_CHAR_PUNCTUATION(true, ascii::is_punctuation_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_whitespace_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_whitespace_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_whitespace_char)
    CHECK_CHAR_NON_WHITESPACE_CONTROL(false, ascii::is_whitespace_char)
    CHECK_CHAR_DIGIT(false, ascii::is_whitespace_char)
    CHECK_CHAR_ALPHA(false, ascii::is_whitespace_char)
    CHECK_CHAR_WHITESPACE(true, ascii::is_whitespace_char)
    CHECK_CHAR_PUNCTUATION(false, ascii::is_whitespace_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_blank_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_blank_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_blank_char)
    CHECK_CHAR_NON_WHITESPACE_CONTROL(false, ascii::is_blank_char)
    CHECK_CHAR_DIGIT(false, ascii::is_blank_char)
    CHECK_CHAR_ALPHA(false, ascii::is_blank_char)
    CHECK_CHAR_NON_BLANK_WHITESPACE(false, ascii::is_blank_char)
    CHECK_CHAR_PUNCTUATION(false, ascii::is_blank_char)
    CHECK_CHAR(' ', true, ascii::is_blank_char)
    CHECK_CHAR('\t', true, ascii::is_blank_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_null_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_null_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_null_char)
    CHECK_CHAR(0, true, ascii::is_null_char)
    for(int i = 1; i <= 0x7f; ++i) {
        CHECK_CHAR(i, false, ascii::is_null_char)
    }
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_control_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_control_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_control_char)
    CHECK_CHAR_CONTROL(true, ascii::is_control_char)
    CHECK_CHAR_DIGIT(false, ascii::is_control_char)
    CHECK_CHAR_ALPHA(false, ascii::is_control_char)
    CHECK_CHAR_PUNCTUATION(false, ascii::is_control_char)
    CHECK_CHAR(' ', false, ascii::is_control_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_printable_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_printable_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_printable_char)
    CHECK_CHAR_CONTROL(false, ascii::is_printable_char)
    CHECK_CHAR_DIGIT(true, ascii::is_printable_char)
    CHECK_CHAR_ALPHA(true, ascii::is_printable_char)
    CHECK_CHAR_NON_BLANK_WHITESPACE(false, ascii::is_printable_char)
    CHECK_CHAR_PUNCTUATION(true, ascii::is_printable_char)
    CHECK_CHAR(' ', true, ascii::is_printable_char)
    CHECK_CHAR('\t', false, ascii::is_printable_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("is_graphical_char") {
    CHECK_CHAR_PROLOGUE(ascii::is_graphical_char)
    CHECK_CHAR_NON_ASCII(false, ascii::is_graphical_char)
    CHECK_CHAR_CONTROL(false, ascii::is_graphical_char)
    CHECK_CHAR_DIGIT(true, ascii::is_graphical_char)
    CHECK_CHAR_ALPHA(true, ascii::is_graphical_char)
    CHECK_CHAR_WHITESPACE(false, ascii::is_graphical_char)
    CHECK_CHAR_PUNCTUATION(true, ascii::is_graphical_char)
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("to_lower_char") {
    CHECK_CHAR_PROLOGUE(ascii::to_lower_char)
    CHECK_CHAR_NON_ASCII_EXPECT_INPUT(ascii::to_lower_char)
    for(int i = 0; i <= 0x7f; ++i) {
        if(i >= 'A' && i <= 'Z') {
            CHECK_CHAR(i, i + ('a' - 'A'), ascii::to_lower_char)
        }
        else {
            CHECK_CHAR_EXPECT_INPUT(i, ascii::to_lower_char)
        }
    }
    CHECK_CHAR_EPILOGUE
}

TEST_CASE("to_upper_char") {
    CHECK_CHAR_PROLOGUE(ascii::to_upper_char)
    CHECK_CHAR_NON_ASCII_EXPECT_INPUT(ascii::to_upper_char)
    for(int i = 0; i <= 0x7f; ++i) {
        if(i >= 'a' && i <= 'z') {
            CHECK_CHAR(i, i - ('a' - 'A'), ascii::to_upper_char)
        }
        else {
            CHECK_CHAR_EXPECT_INPUT(i, ascii::to_upper_char)
        }
    }
    CHECK_CHAR_EPILOGUE
}
