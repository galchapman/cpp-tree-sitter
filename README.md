# Tree Sitter C++ binding

This is a cpp binding for [tree sitter](https://tree-sitter.github.io/tree-sitter/)

## Usage

### 1. Build the core binding

Run `make` in the root directory by defult the c version is c99 and c++ version is 20

### 2. Add a language

Inside the [languages](languages) run `make \<language>-lang.o`  
To install and build your language.

### 3. Run your program

When you run your compiler include the folowing directories:
[project root](.), [src](src) and [src/core/lib/include](src/core/lib/include).

And don't forget to add the library files: `libtree-sitter-cpp.a` and your language
library (for example cpp-lang.o).

## Step by step guide

Clone this repositry

```sh
git clone https://github.com/galchapman/cpp-tree-sitter
```

Build the respoitry

```sh
make
```

Install a language

```sh
cd languages
make cpp-lang.o
```

Write your main program

```cpp
#include <iostream>
#include <memory>
#include <parser.hpp>
#include <languages/cpp.hpp>

const char* source = \
"#include <iostream>\n" \
"\n" \
"using namespace std;\n" \
"\n" \
"int main(void) {\n" \
"    cout << \"Hello, World\";\n" \
"    return 0;\n" \
"}\n";

int main(void) {
    ts::Parser parser;
    parser.setLanguage(ts::cpp::language());
    
    std::shared_ptr<ts::Tree> tree = parser.parse(source);

    ts::Node rootNode = tree->rootNode();

    std::cout << rootNode.sexp() << std::endl;

    return 0;
}
```

Than compile your program

```sh
g++ -I. -Isrc -Isrc/core/lib/include libtree-sitter-cpp.o languages/cpp-lang.o main.cpp -o main
```

Than run it

```sh
./main.exe
```