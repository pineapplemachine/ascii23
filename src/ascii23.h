/**  
 * Ascii23 is a header-only library providing ASCII-related functions.
 * It is released under a zlib/libpng license. 
 * See: https://opensource.org/license/zlib/
 * 
 * Copyright (c) 2023 Sophie Kirschner (@pineapplemachine)
 *
 * This software is provided ‘as-is’, without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
 */

#ifndef ASCII23_HEADER_INCLUDED
#define ASCII23_HEADER_INCLUDED

#define ASCII23_VERSION_NAME "1.0.0"
#define ASCII23_VERSION_DATE 2023_09_28

#if defined(_WIN32) && defined(ASCII23_USE_SHARED_LIB)
    #undef ASCII23_HEADER_ONLY
    #undef ASCII23_DEFINE_API
    #define ASCII23_INLINE
    #define ASCII23_API __declspec(dllimport)
#elif defined(ASCII23_USE_COMPILED_LIB)
    #undef ASCII23_HEADER_ONLY
    #undef ASCII23_DEFINE_API
    #define ASCII23_INLINE
    #define ASCII23_API
#elif defined(ASCII23_BUILD_SHARED_LIB)
    #undef ASCII23_HEADER_ONLY
    #define ASCII23_DEFINE_API
    #define ASCII23_INLINE
    #if defined(_WIN32)
        #define ASCII23_API __declspec(dllexport)
    #else
        #define ASCII23_API __attribute__((visibility("default")))
    #endif
#elif defined(ASCII23_BUILD_COMPILED_LIB)
    #undef ASCII23_HEADER_ONLY
    #define ASCII23_DEFINE_API
    #define ASCII23_INLINE
    #define ASCII23_API
#else
    #define ASCII23_HEADER_ONLY
    #define ASCII23_DEFINE_API
    #define ASCII23_INLINE inline
    #define ASCII23_API
#endif

namespace ascii {

/** In `char_flags_array`: No flag. */
const int CHAR_FLAG_NONE = 0x0000;

/** In `char_flags_array`: Set for `a-z` and `A-Z`. */
const int CHAR_FLAG_ALPHA = 0x0001;

/** In `char_flags_array`: Set for `a-z`. */
const int CHAR_FLAG_LOWER = 0x0002;

/** In `char_flags_array`: Set for `A-Z`. */
const int CHAR_FLAG_UPPER = 0x0004;

/** In `char_flags_array`: Set for `0-9`. */
const int CHAR_FLAG_DIGIT = 0x0008;

/** In `char_flags_array`: Set for `0-9`, `a-f`, and `A-F`. */
const int CHAR_FLAG_HEX_DIGIT = 0x0010;

/** In `char_flags_array`: Set for `_`, `0-9`, `a-z`, and `A-Z`. */
const int CHAR_FLAG_WORD = 0x0020;

/** In `char_flags_array`: Set for `_`, `a-z`, and `A-Z`. */
const int CHAR_FLAG_WORD_START = 0x0040;

/** In `char_flags_array`: Set for ``!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~``. */
const int CHAR_FLAG_PUNCTUATION = 0x0080;

/** In `char_flags_array`: Set for ` `, `\t`, `\r`, `\v`, `\f`, and `\n`. */
const int CHAR_FLAG_WHITESPACE = 0x0100;

/** In `char_flags_array`: Set for ` ` and `\t`. */
const int CHAR_FLAG_BLANK = 0x0200;

/** In `char_flags_array`: Set for `0x00-0x1f` and `0x7f` */
const int CHAR_FLAG_CONTROL = 0x0400;

/** In `char_flags_array`: Set for `0x20-0x7e` (space to tilde). */
const int CHAR_FLAG_PRINTABLE = 0x0800;

/** In `char_flags_array`: Set for `0x21-0x7e` (bang to tilde). */
const int CHAR_FLAG_GRAPHICAL = 0x1000;

const int CHAR_FLAGS_0x09_0x0D = (
    CHAR_FLAG_CONTROL |
    CHAR_FLAG_WHITESPACE
);
const int CHAR_FLAGS_0x21_0x7E = (
    CHAR_FLAG_PRINTABLE |
    CHAR_FLAG_GRAPHICAL
);
const int CHAR_FLAGS_0x21_0x2F = (
    CHAR_FLAGS_0x21_0x7E |
    CHAR_FLAG_PUNCTUATION
);
const int CHAR_FLAGS_0x30_0x39 = (
    CHAR_FLAGS_0x21_0x7E |
    CHAR_FLAG_DIGIT |
    CHAR_FLAG_HEX_DIGIT |
    CHAR_FLAG_WORD
);
const int CHAR_FLAGS_0x3A_0x40 = (
    CHAR_FLAGS_0x21_0x7E |
    CHAR_FLAG_PUNCTUATION
);
const int CHAR_FLAGS_0x41_0x5A = (
    CHAR_FLAGS_0x21_0x7E |
    CHAR_FLAG_ALPHA |
    CHAR_FLAG_UPPER |
    CHAR_FLAG_WORD |
    CHAR_FLAG_WORD_START
);
const int CHAR_FLAGS_0x41_0x46 = (
    CHAR_FLAGS_0x41_0x5A |
    CHAR_FLAG_HEX_DIGIT
);
const int CHAR_FLAGS_0x5B_0x60 = (
    CHAR_FLAGS_0x21_0x7E |
    CHAR_FLAG_PUNCTUATION
);
const int CHAR_FLAGS_0x61_0x7A = (
    CHAR_FLAGS_0x21_0x7E |
    CHAR_FLAG_ALPHA |
    CHAR_FLAG_LOWER |
    CHAR_FLAG_WORD |
    CHAR_FLAG_WORD_START
);
const int CHAR_FLAGS_0x61_0x66 = (
    CHAR_FLAGS_0x61_0x7A |
    CHAR_FLAG_HEX_DIGIT
);
const int CHAR_FLAGS_0x7B_0x7E = (
    CHAR_FLAGS_0x21_0x7E |
    CHAR_FLAG_PUNCTUATION
);

/**
 * Array of flags describing the role of all 128 ASCII
 * characters.
 * 
 * See the `CHAR_FLAGS_*` constants for which flags are
 * represented in the array.
 */
const int char_flags_array[128] = {
    /* 0x00 \0  */ CHAR_FLAG_CONTROL,
    /* 0x01 SOH */ CHAR_FLAG_CONTROL,
    /* 0x02 STX */ CHAR_FLAG_CONTROL,
    /* 0x03 ETX */ CHAR_FLAG_CONTROL,
    /* 0x04 EOT */ CHAR_FLAG_CONTROL,
    /* 0x05 ENQ */ CHAR_FLAG_CONTROL,
    /* 0x06 ACK */ CHAR_FLAG_CONTROL,
    /* 0x07 \a  */ CHAR_FLAG_CONTROL,
    /* 0x08 \b  */ CHAR_FLAG_CONTROL,
    /* 0x09 \t  */ CHAR_FLAGS_0x09_0x0D | CHAR_FLAG_BLANK,
    /* 0x0a \r  */ CHAR_FLAGS_0x09_0x0D,
    /* 0x0b \v  */ CHAR_FLAGS_0x09_0x0D,
    /* 0x0c \f  */ CHAR_FLAGS_0x09_0x0D,
    /* 0x0d \n  */ CHAR_FLAGS_0x09_0x0D,
    /* 0x0e SO  */ CHAR_FLAG_CONTROL,
    /* 0x0f SI  */ CHAR_FLAG_CONTROL,
    /* 0x10 DLE */ CHAR_FLAG_CONTROL,
    /* 0x11 DC1 */ CHAR_FLAG_CONTROL,
    /* 0x12 DC2 */ CHAR_FLAG_CONTROL,
    /* 0x13 DC3 */ CHAR_FLAG_CONTROL,
    /* 0x14 DC4 */ CHAR_FLAG_CONTROL,
    /* 0x15 NAK */ CHAR_FLAG_CONTROL,
    /* 0x16 SYN */ CHAR_FLAG_CONTROL,
    /* 0x17 ETB */ CHAR_FLAG_CONTROL,
    /* 0x18 CAN */ CHAR_FLAG_CONTROL,
    /* 0x19 EM  */ CHAR_FLAG_CONTROL,
    /* 0x1a SUB */ CHAR_FLAG_CONTROL,
    /* 0x1b ESC */ CHAR_FLAG_CONTROL,
    /* 0x1c FS  */ CHAR_FLAG_CONTROL,
    /* 0x1d GS  */ CHAR_FLAG_CONTROL,
    /* 0x1e RS  */ CHAR_FLAG_CONTROL,
    /* 0x1f US  */ CHAR_FLAG_CONTROL,
    /* 0x20 ' ' */ CHAR_FLAG_PRINTABLE | CHAR_FLAG_WHITESPACE | CHAR_FLAG_BLANK,
    /* 0x21 '!' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x22 '"' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x23 '#' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x24 '$' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x25 '%' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x26 '&' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x27 '\''*/ CHAR_FLAGS_0x21_0x2F,
    /* 0x28 '(' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x29 ')' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x2a '*' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x2b '+' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x2c ',' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x2d '-' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x2e '.' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x2f '/' */ CHAR_FLAGS_0x21_0x2F,
    /* 0x30 '0' */ CHAR_FLAGS_0x30_0x39,
    /* 0x31 '1' */ CHAR_FLAGS_0x30_0x39,
    /* 0x32 '2' */ CHAR_FLAGS_0x30_0x39,
    /* 0x33 '3' */ CHAR_FLAGS_0x30_0x39,
    /* 0x34 '4' */ CHAR_FLAGS_0x30_0x39,
    /* 0x35 '5' */ CHAR_FLAGS_0x30_0x39,
    /* 0x36 '6' */ CHAR_FLAGS_0x30_0x39,
    /* 0x37 '7' */ CHAR_FLAGS_0x30_0x39,
    /* 0x38 '8' */ CHAR_FLAGS_0x30_0x39,
    /* 0x39 '9' */ CHAR_FLAGS_0x30_0x39,
    /* 0x3a ':' */ CHAR_FLAGS_0x3A_0x40,
    /* 0x3b ';' */ CHAR_FLAGS_0x3A_0x40,
    /* 0x3c '<' */ CHAR_FLAGS_0x3A_0x40,
    /* 0x3d '=' */ CHAR_FLAGS_0x3A_0x40,
    /* 0x3e '>' */ CHAR_FLAGS_0x3A_0x40,
    /* 0x3f '?' */ CHAR_FLAGS_0x3A_0x40,
    /* 0x40 '@' */ CHAR_FLAGS_0x3A_0x40,
    /* 0x41 'A' */ CHAR_FLAGS_0x41_0x46,
    /* 0x42 'B' */ CHAR_FLAGS_0x41_0x46,
    /* 0x43 'C' */ CHAR_FLAGS_0x41_0x46,
    /* 0x44 'D' */ CHAR_FLAGS_0x41_0x46,
    /* 0x45 'E' */ CHAR_FLAGS_0x41_0x46,
    /* 0x46 'F' */ CHAR_FLAGS_0x41_0x46,
    /* 0x47 'G' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x48 'H' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x49 'I' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x4a 'J' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x4b 'K' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x4c 'L' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x4d 'M' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x4e 'N' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x4f 'O' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x50 'P' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x51 'Q' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x52 'R' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x53 'S' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x54 'T' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x55 'U' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x56 'V' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x57 'W' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x58 'X' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x59 'Y' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x5a 'Z' */ CHAR_FLAGS_0x41_0x5A,
    /* 0x5b '[' */ CHAR_FLAGS_0x5B_0x60,
    /* 0x5c '\\'*/ CHAR_FLAGS_0x5B_0x60,
    /* 0x5d ']' */ CHAR_FLAGS_0x5B_0x60,
    /* 0x5e '^' */ CHAR_FLAGS_0x5B_0x60,
    /* 0x5f '_' */ CHAR_FLAGS_0x5B_0x60 | CHAR_FLAG_WORD | CHAR_FLAG_WORD_START,
    /* 0x60 '`' */ CHAR_FLAGS_0x5B_0x60,
    /* 0x61 'a' */ CHAR_FLAGS_0x61_0x66,
    /* 0x62 'b' */ CHAR_FLAGS_0x61_0x66,
    /* 0x63 'c' */ CHAR_FLAGS_0x61_0x66,
    /* 0x64 'd' */ CHAR_FLAGS_0x61_0x66,
    /* 0x65 'e' */ CHAR_FLAGS_0x61_0x66,
    /* 0x66 'f' */ CHAR_FLAGS_0x61_0x66,
    /* 0x67 'g' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x68 'h' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x69 'i' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x6a 'j' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x6b 'k' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x6c 'l' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x6d 'm' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x6e 'n' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x6f 'o' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x70 'p' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x71 'q' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x72 'r' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x73 's' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x74 't' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x75 'u' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x76 'v' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x77 'w' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x78 'x' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x79 'y' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x7a 'z' */ CHAR_FLAGS_0x61_0x7A,
    /* 0x7b '{' */ CHAR_FLAGS_0x7B_0x7E,
    /* 0x7c '|' */ CHAR_FLAGS_0x7B_0x7E,
    /* 0x7d '}' */ CHAR_FLAGS_0x7B_0x7E,
    /* 0x7e '~' */ CHAR_FLAGS_0x7B_0x7E,
    /* 0x7f DEL */ CHAR_FLAG_CONTROL,
};

/**
 * Returns true when the input represents an ASCII
 * chararacter, i.e. a value in the range `0x00-0x7f`.
 */
ASCII23_API bool is_char(const int ch);

/**
 * Returns true when a character is `a-z` or `A-Z`.
 */
ASCII23_API bool is_alpha_char(const int ch);

/**
 * Returns true when a character is `a-z`.
 */
ASCII23_API bool is_alpha_lower_char(const int ch);

/**
 * Returns true when a character is `A-Z`.
 */
ASCII23_API bool is_alpha_upper_char(const int ch);

/**
 * Returns true when a character is `0-9`.
 */
ASCII23_API bool is_digit_char(const int ch);

/**
 * Returns true when a character is `0-9`, `a-f`, or `A-F`.
 */
ASCII23_API bool is_hex_digit_char(const int ch);

/**
 * Returns true when a character is `0-9` or `a-f`.
 */
ASCII23_API bool is_hex_digit_lower_char(const int ch);

/**
 * Returns true when a character is `0-9` or `A-F`.
 */
ASCII23_API bool is_hex_digit_upper_char(const int ch);

/**
 * Returns true when a character is `_`, `a-z`, `A-Z`, or `0-9`.
 */
ASCII23_API bool is_word_char(const int ch);

/**
 * Returns true when a character is `_`, `a-z`, or `0-9`.
 */
ASCII23_API bool is_word_lower_char(const int ch);

/**
 * Returns true when a character is `_`, `A-Z`, or `0-9`.
 */
ASCII23_API bool is_word_upper_char(const int ch);

/**
 * Returns true when a character is `_`, `a-z`, or `A-Z`.
 */
ASCII23_API bool is_word_start_char(const int ch);

/**
 * Returns true when a character is `_` or `a-z`.
 */
ASCII23_API bool is_word_lower_start_char(const int ch);

/**
 * Returns true when a character is `_` or `A-Z`.
 */
ASCII23_API bool is_word_upper_start_char(const int ch);

/**
 * Returns true when a character is a punctuation character,
 * i.e. one of these: ``!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~``
 */
ASCII23_API bool is_punctuation_char(const int ch);

/**
 * Returns true for ASCII whitespace characters:
 * ` ` (space), `\t` (tab), `\r` (line feed), `\v` (vertical tab),
 * `\f` (form feed), and `\n` (carriage return).
 */
ASCII23_API bool is_whitespace_char(const int ch);

/**
 * Returns true when a character is ` ` (space) or `\t` (tab).
 */
ASCII23_API bool is_blank_char(const int ch);

/**
 * Returns true only for the null character `0x00`.
 */
ASCII23_API bool is_null_char(const int ch);

/**
 * Returns true for control characters, i.e. `0x00-0x1f` or `0x7f`.
 */
ASCII23_API bool is_control_char(const int ch);

/**
 * Returns true for printable characters, i.e. `0x20-0x7e`.
 * Printable characters are those which are not control characters.
 */
ASCII23_API bool is_printable_char(const int ch);

/**
 * Returns true for printable characters with a graphical
 * representation, i.e. `0x21-0x7e`, or everything
 * except ` ` (space).
 */
ASCII23_API bool is_graphical_char(const int ch);

/**
 * Returns `a-z` for inputs `A-Z`.
 * Returns the unmodified input character, otherwise.
 */
ASCII23_API int to_lower_char(const int ch);

/**
 * Returns `A-Z` for inputs `a-z`.
 * Returns the unmodified input character, otherwise.
 */
ASCII23_API int to_upper_char(const int ch);

#if defined(ASCII23_DEFINE_API)

ASCII23_INLINE bool is_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f);
}

ASCII23_INLINE bool is_alpha_char(const int ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

ASCII23_INLINE bool is_alpha_lower_char(const int ch) {
    return (ch >= 'a' && ch <= 'z');
}

ASCII23_INLINE bool is_alpha_upper_char(const int ch) {
    return (ch >= 'A' && ch <= 'Z');
}

ASCII23_INLINE bool is_digit_char(const int ch) {
    return (ch >= '0' && ch <= '9');
}

ASCII23_INLINE bool is_hex_digit_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        char_flags_array[ch] & CHAR_FLAG_HEX_DIGIT
    );
    // Equivalent behavior, slower benchmark
    // return (
    //     (ch >= '0' && ch <= '9') ||
    //     (ch >= 'a' && ch <= 'f') ||
    //     (ch >= 'A' && ch <= 'F')
    // );
}

ASCII23_INLINE bool is_hex_digit_lower_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        (char_flags_array[ch] & (CHAR_FLAG_HEX_DIGIT | CHAR_FLAG_UPPER)) ==
        CHAR_FLAG_HEX_DIGIT
    );
    // Equivalent behavior, slower benchmark
    // return (
    //     (ch >= '0' && ch <= '9') ||
    //     (ch >= 'a' && ch <= 'f')
    // );
}

ASCII23_INLINE bool is_hex_digit_upper_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        (char_flags_array[ch] & (CHAR_FLAG_HEX_DIGIT | CHAR_FLAG_LOWER)) ==
        CHAR_FLAG_HEX_DIGIT
    );
    // Equivalent behavior, slower benchmark
    // return (
    //     (ch >= '0' && ch <= '9') ||
    //     (ch >= 'A' && ch <= 'F')
    // );
}

ASCII23_INLINE bool is_word_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        char_flags_array[ch] & CHAR_FLAG_WORD
    );
    // Equivalent behavior, slower benchmark
    // return ch == '_' || (
    //     (ch >= '0' && ch <= '9') ||
    //     (ch >= 'a' && ch <= 'z') ||
    //     (ch >= 'A' && ch <= 'Z')
    // );
}

ASCII23_INLINE bool is_word_lower_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        (char_flags_array[ch] & (CHAR_FLAG_WORD | CHAR_FLAG_UPPER)) ==
        CHAR_FLAG_WORD
    );
    // Equivalent behavior, slower benchmark
    // return ch == '_' || (
    //     (ch >= '0' && ch <= '9') ||
    //     (ch >= 'a' && ch <= 'z')
    // );
}

ASCII23_INLINE bool is_word_upper_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        (char_flags_array[ch] & (CHAR_FLAG_WORD | CHAR_FLAG_LOWER)) ==
        CHAR_FLAG_WORD
    );
    // Equivalent behavior, slower benchmark
    // return ch == '_' || (
    //     (ch >= '0' && ch <= '9') ||
    //     (ch >= 'A' && ch <= 'Z')
    // );
}

ASCII23_INLINE bool is_word_start_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        char_flags_array[ch] & CHAR_FLAG_WORD_START
    );
    // Equivalent behavior, slower benchmark
    // return ch == '_' || (
    //     (ch >= 'a' && ch <= 'z') ||
    //     (ch >= 'A' && ch <= 'Z')
    // );
}

ASCII23_INLINE bool is_word_lower_start_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        (char_flags_array[ch] & (CHAR_FLAG_WORD_START | CHAR_FLAG_UPPER)) ==
        CHAR_FLAG_WORD_START
    );
    // Equivalent behavior, slower benchmark
    // return ch == '_' || (ch >= 'a' && ch <= 'z');
}

ASCII23_INLINE bool is_word_upper_start_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        (char_flags_array[ch] & (CHAR_FLAG_WORD_START | CHAR_FLAG_LOWER)) ==
        CHAR_FLAG_WORD_START
    );
    // Equivalent behavior, slower benchmark
    // return ch == '_' || (ch >= 'A' && ch <= 'Z');
}

ASCII23_INLINE bool is_punctuation_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        char_flags_array[ch] & CHAR_FLAG_PUNCTUATION
    );
    // Equivalent behavior, slower benchmark
    // return (
    //     (ch >= '!' && ch <= '/') ||
    //     (ch >= ':' && ch <= '@') ||
    //     (ch >= '[' && ch <= '`') ||
    //     (ch >= '{' && ch <= '~')
    // );
}

ASCII23_INLINE bool is_whitespace_char(const int ch) {
    return (ch >= 0 && ch <= 0x7f) && (
        char_flags_array[ch] & CHAR_FLAG_WHITESPACE
    );
    // Equivalent behavior, slower benchmark
    // return ch == ' ' || (ch >= '\t' && ch <= '\r');
}

ASCII23_INLINE bool is_blank_char(const int ch) {
    return ch == ' ' || ch == '\t';
}

ASCII23_INLINE bool is_null_char(const int ch) {
    return ch == 0x00;
}

ASCII23_INLINE bool is_control_char(const int ch) {
    return (ch >= 0x00 && ch <= 0x1f) || ch == 0x7f;
}

ASCII23_INLINE bool is_printable_char(const int ch) {
    return ch >= 0x20 && ch <= 0x7e;
}

ASCII23_INLINE bool is_graphical_char(const int ch) {
    return ch >= 0x21 && ch <= 0x7e;
}

ASCII23_INLINE int to_lower_char(const int ch) {
    return (ch >= 'A' && ch <= 'Z') ? ch | 0x20 : ch;
}

ASCII23_INLINE int to_upper_char(const int ch) {
    return (ch >= 'a' && ch <= 'z') ? ch & 0xdf : ch;
}

#endif // #if defined(ASCII23_DEFINE_API)

} // namespace ascii

#endif // #if defined(ASCII23_HEADER_INCLUDED)
