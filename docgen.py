"""
This script reads declarations and documenting comments
from src/ascii23.h and dumps them into a generated
markdown file, because none of the C++ documentation
generator tools that I could find were up to such a
profoundly complicated task.
"""

import dataclasses
import datetime
import re

ascii_namespace = "ascii::"

re_ascii_version = r'#define ASCII23_VERSION_NAME "(.+?)"'
re_doc_comment = r'((?:/\*\*.*\s*)(?:\*.+\s*)*(?:\s*\*/))'
re_constant = re_doc_comment + r'\s*const(.+?([a-zA-Z0-9_]+)\s*)=(.+?);'
re_constant_array = re_doc_comment + r'\s*const(.+?([a-zA-Z0-9_]+)\s*\[.*?\]\s*)=\s*\{'
re_api_function = re_doc_comment + r'\s*ASCII23_API\s*(.+?([a-zA-Z0-9_]+)\(.*?\));'

def format_doc(doc):
    if doc.startswith("/**"):
        doc = doc[3:]
    if doc.endswith("*/"):
        doc = doc[:-2]
    doc_lines = doc.strip().split("\n")
    for i in range(0, len(doc_lines)):
        doc_lines[i] = doc_lines[i].strip()
        if doc_lines[i].startswith("*"):
            doc_lines[i] = doc_lines[i][1:].strip()
    return "\n".join(doc_lines)

def format_id(name):
    return name.lower().replace("::", "")

print("Reading source code from src/ascii23.h")
with open("src/ascii23.h", "rt", encoding="utf-8") as ascii_file:
    ascii_src = ascii_file.read()

ascii_version = re.search(re_ascii_version, ascii_src)

doc_constants = []
@dataclasses.dataclass
class DocConstant:
    match: re.Match
    doc: str
    declaration: str
    name: str
    id: str
    value: str

doc_constant_arrays = []
@dataclasses.dataclass
class DocConstantArray:
    match: re.Match
    doc: str
    declaration: str
    name: str
    id: str

doc_api_functions = []
@dataclasses.dataclass
class DocApiFunction:
    match: re.Match
    doc: str
    declaration: str
    name: str
    id: str

for match in re.finditer(re_constant, ascii_src):
    name = ascii_namespace + match.group(3).strip()
    doc_constants.append(DocConstant(
        match = match,
        doc = format_doc(match.group(1)),
        declaration = match.group(2).strip(),
        name = name,
        id = format_id(name),
        value = match.group(4).strip(),
    ))

for match in re.finditer(re_constant_array, ascii_src):
    name = ascii_namespace + match.group(3).strip()
    doc_constant_arrays.append(DocConstantArray(
        match = match,
        doc = format_doc(match.group(1)),
        declaration = match.group(2).strip(),
        name = name,
        id = format_id(name),
    ))

for match in re.finditer(re_api_function, ascii_src):
    name = ascii_namespace + match.group(3).strip()
    doc_api_functions.append(DocApiFunction(
        match = match,
        doc = format_doc(match.group(1)),
        declaration = match.group(2).strip(),
        name = name,
        id = format_id(name),
    ))

md_toc_template = "* * [%(name)s](#%(id)s)"

md_constant_template = """
### %(name)s

%(doc)s

``` cpp
const %(declaration)s = %(value)s;
```
""".strip()

md_constant_array_template = """
### %(name)s

%(doc)s

``` cpp
const %(declaration)s = {...};
```
""".strip()

md_api_function_template = """
### %(name)s

%(doc)s

``` cpp
%(declaration)s;
```
""".strip()

md_body_template = """
# Ascii23 API Documentation

<!--
This file is automatically generated by the project's
`docgen.py` Python script.

Usage:
$ python docgen.py
-->

The functions and constants defined in the ascii23 library all live
in the `ascii` namespace, e.g. `ascii::is_whitespace_char`.

This documentation file was automatically generated on %(timestamp)s
for version `%(version)s` of the ascii23 library, using the declarations
and comments in `src/ascii23.h`.

For more information about the ascii23 library, see the project's
`readme.md` or visit
[github.com/pineapplemachine/ascii23](https://www.github.com/pineapplemachine/ascii23).

## Contents

* [Functions](#functions)
%(api_functions_toc)s
* [Constants](#constants)
%(constant_arrays_toc)s
%(constants_toc)s

## Functions

%(api_functions)s

## Constants

%(constant_arrays)s

%(constants)s

""".strip()

print("Rendering Markdown")
md_docs = md_body_template % {
    "version": ascii_version.group(1),
    "timestamp": datetime.datetime.strftime(datetime.datetime.now(), "%Y-%m-%d"),
    "constants_toc": "\n".join(map(
        lambda i: md_toc_template % dataclasses.asdict(i),
        doc_constants
    )),
    "constant_arrays_toc": "\n".join(map(
        lambda i: md_toc_template % dataclasses.asdict(i),
        doc_constant_arrays
    )),
    "api_functions_toc": "\n".join(map(
        lambda i: md_toc_template % dataclasses.asdict(i),
        doc_api_functions
    )),
    "constants": "\n\n".join(map(
        lambda i: md_constant_template % dataclasses.asdict(i),
        doc_constants
    )),
    "constant_arrays": "\n\n".join(map(
        lambda i: md_constant_array_template % dataclasses.asdict(i),
        doc_constant_arrays
    )),
    "api_functions": "\n\n".join(map(
        lambda i: md_api_function_template % dataclasses.asdict(i),
        doc_api_functions
    )),
}

print("Writing output to documentation.md")
with open("documentation.md", "wt", encoding="utf-8") as md_file:
    md_file.write(md_docs)

print("All done!")
