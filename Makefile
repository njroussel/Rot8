.PHONY: help format cleanbuild build all

help:
	@echo "format - format code with clang-format"
	@echo "cleanbuild - clean build executable"
	@echo "build - build executable"
	@echo "all - format > cleanbuild"

format:
	clang-format -i include/**/*.h src/**/*.cpp

build:
	mkdir -p build
	cmake -B build -GNinja . && ninja -C build

cleanbuild:
	rm -rf build
	mkdir build
	cmake -B build -GNinja . && ninja -C build

all: 
	format cleanbuild
