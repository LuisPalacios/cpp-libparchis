all: prepare

prepare:
	rm -rf build
	mkdir build

install-linux:
	sudo apt-get install gcc g++ cmake make doxygen git llvm pkg-config curl zip unzip tar python3-dev clang-format clang-tidy libboost-all-dev
