CXX = g++
CXXFLAGS = -Isrc -Iinclude -std=c++11 -Wall -Wextra
CXXFLAGS_RELEASE = -DNDEBUG -O3
CXXFLAGS_DEBUG = -DDEBUG -g -O0
CXXFLAGS_BUILD_LIB = -DASCII23_BUILD_COMPILED_LIB

default: release_lib

clean:
	rm -rf lib/
	rm -rf bin/

release_lib:
	mkdir -p bin
	mkdir -p lib
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_BUILD_LIB) $(CXXFLAGS_RELEASE) \
		-c -x c++ -o bin/ascii23_release.o src/ascii23.h
	ar rcs lib/libascii23.a bin/ascii23_release.o
	echo "Compiled library at lib/libascii23.a"

debug_lib:
	mkdir -p bin
	mkdir -p lib
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_BUILD_LIB) $(CXXFLAGS_DEBUG) \
		-c -x c++ -o bin/ascii23_debug.o src/ascii23.h
	ar rcs lib/libascii23.a bin/ascii23_debug.o
	echo "Compiled debug library at lib/libascii23.a"

release_dll:
	mkdir -p lib
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_BUILD_LIB) $(CXXFLAGS_RELEASE) \
		-DASCII23_BUILD_SHARED_LIB \
		-shared -x c++ -o lib/ascii23.dll src/ascii23.h
	echo "Compiled library at lib/ascii23.dll"

bench_impl:
	mkdir -p bin
	cppcheck --language=c++ test/bench.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_RELEASE) \
		-o bin/bench_impl test/bench.cpp
	echo "Compiled test binary at bin/bench"

test_impl:
	mkdir -p bin
	# negativeIndex false positive with cppcheck 2.10
	cppcheck --language=c++ --suppress=negativeIndex test/test_impl.cpp
	cppcheck --language=c++ src/ascii23.h
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_DEBUG) \
		-o bin/test_impl test/test_impl.cpp
	echo "Compiled test binary at bin/test_impl"

test_header: release_lib
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_RELEASE) \
		-o bin/test_header test/test_header.cpp
	echo "Compiled test binary at bin/test_header"

test_lib: release_lib
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_RELEASE) \
		-o bin/test_lib test/test_lib.cpp \
		-Llib -l:libascii23.a
	echo "Compiled test binary at bin/test_lib"

test_dll: release_dll
	mkdir -p bin
	cp lib/ascii23.dll bin/ascii23.dll
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_RELEASE) \
		-o bin/test_dll test/test_dll.cpp \
		-Llib -l:ascii23.dll
	echo "Compiled test binary at bin/test_dll.exe"

test_all: test_impl test_header test_lib test_dll
