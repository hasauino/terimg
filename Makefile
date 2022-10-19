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

%.dep:
	@echo "hi"


.PHONY: build/terimg_amd64/DEBIAN/control
build/terimg_amd64/DEBIAN/control: build/bin/terimg
	mkdir -p build/terimg_amd64/DEBIAN
	mkdir -p build/terimg_amd64/usr/local/bin
	cp build/bin/terimg build/terimg_amd64/usr/local/bin/terimg
	cp control build/terimg_amd64/DEBIAN/	


build/terimg_amd64.deb: build/terimg_amd64/DEBIAN/control
	/usr/bin/dpkg-deb --build --root-owner-group build/terimg_amd64


