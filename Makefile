all: build/bin/terimg

build:
	mkdir -p build

build/Makefile: build
	cd build && \
	cmake ..

build/bin/terimg: build/Makefile
	$(MAKE) -C build

.PHONY: clean
clean:
	rm -rf build/
