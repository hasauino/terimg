all: build/bin/terimg

build:
	mkdir -p build

build/Makefile: build
	cd build && \
	cmake ..

.PHONY: build/bin/terimg
build/bin/terimg: build/Makefile
	$(MAKE) -C build

.PHONY: clean
clean:
	rm -rf build/
