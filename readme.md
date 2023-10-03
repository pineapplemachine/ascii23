# ascii23

![GitHub automated test workflow status](https://github.com/pineapplemachine/ascii23/actions/workflows/test.yml/badge.svg)

Ascii23 is a header-only C++ library offering ASCII-related functionality. It may be used as an alternative to the `<cctype>` header. Unlike cctype, ascii23 has the same behavior regardless of locale, and it behaves sensibly and predictably with UTF-8 and other Unicode text inputs. (Neither non-ASCII Unicode code points nor UTF-8 code units belonging to non-ASCII code points should ever produce false positives.)
    
Ascii23 is released under the permissive [zlib/libpng license](https://opensource.org/license/zlib/).

## Documentation

For complete API documentation, please refer either to the commented source code in `src/ascii23.h` or to the [documentation.md](https://github.com/pineapplemachine/ascii23/blob/master/documentation.md) Markdown file in the root directory of this repository.

Here is a summary of the functions implemented by ascii23, which are defined in the `ascii` namespace:

``` cpp
bool ascii::is_char(const int ch); // Return true if input is 0x00-0x7f.
bool ascii::is_alpha_char(const int ch); // True if a-z, A-Z.
bool ascii::is_alpha_lower_char(const int ch); // True if a-z.
bool ascii::is_alpha_upper_char(const int ch); // True if A-Z.
bool ascii::is_digit_char(const int ch); // True if 0-9.
bool ascii::is_hex_digit_char(const int ch); // True if 0-9, a-f, A-F.
bool ascii::is_hex_digit_lower_char(const int ch); // True if 0-9, a-f.
bool ascii::is_hex_digit_upper_char(const int ch); // True if 0-9, A-F.
bool ascii::is_word_char(const int ch); // True if _, 0-9, a-z, A-Z.
bool ascii::is_word_lower_char(const int ch); // True if _, 0-9, a-z.
bool ascii::is_word_upper_char(const int ch); // True if _, 0-9, A-Z.
bool ascii::is_word_start_char(const int ch); // True if _, a-z, A-Z.
bool ascii::is_word_lower_start_char(const int ch); // True if _, a-z.
bool ascii::is_word_upper_start_char(const int ch); // True if _, A-Z.
bool ascii::is_punctuation_char(const int ch); // !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
bool ascii::is_whitespace_char(const int ch); // True if \t, \r, \v, \f, \n, or space.
bool ascii::is_blank_char(const int ch); // True if \t or space.
bool ascii::is_null_char(const int ch); // True if input is 0x00.
bool ascii::is_control_char(const int ch); // True if 0x00-0x1f or 0x7f.
bool ascii::is_printable_char(const int ch); // True if 0x20-0x7e.
bool ascii::is_graphical_char(const int ch); // True if 0x21-0x7e.
int ascii::to_lower_char(const int ch); // Convert A-Z to a-z, all others unchanged.
int ascii::to_upper_char(const int ch); // Convert a-z to A-Z, all others unchanged.
```

## Using ascii23

**As a header-only library:**

To use ascii23 as a header-only library (recommended):

1. Copy `src/ascii23.h` from this repository into your project's include directory. 
2. Write `#include <ascii23.h>` in your source files to include it.

**Static linking:**

To compile `libascii23.a` and link with it statically:

1. Run `make release_lib` in this repository's root directory.
2. Copy the newly created `lib/libascii23.a` file into your project's lib directory.
3. Copy `src/ascii23.h` from this repository into your project's include directory. 
4. Configure your project to link with `libascii23.a`, e.g. by adding `-lascii23` to your linker flags.
5. Define `ASCII23_USE_COMPILED_LIB` in your project before including `ascii23.h`, e.g. by adding `-DASCII23_USE_COMPILED_LIB` to your compiler flags.
6. Write `#include <ascii23.h>` in your source files to include declarations only.

**Dynamic linking on Windows:**

To compile `ascii23.dll` and link with it dynamically:

1. Run `make release_dll` in this repository's root directory.
2. Copy the newly created `lib/ascii23.dll` file into your project's lib directory.
3. Copy the newly created `lib/ascii23.dll` file additionally to a path where your system will search for DLLs when running your compiled project, e.g. in the same directory as your project's compiled *.exe.
4. Copy `src/ascii23.h` from this repository into your project's include directory. 
5. Configure your project to link with `ascii23.dll`, e.g. by adding `-lascii23` to your linker flags.
6. Define `ASCII23_USE_SHARED_LIB` in your project before including `ascii23.h`, e.g. by adding `-DASCII23_USE_SHARED_LIB` to your compiler flags.
7. Write `#include <ascii23.h>` in your source files to include declarations only.
