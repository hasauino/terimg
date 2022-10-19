# Terimg

In-terminal ASCII image viewer. 

It can show an image if a path is given, otherwise show video device stream.

![](demo.png)

## Install

- Download `.deb`  compatible with your distro from [releases](https://github.com/hasauino/terimg/releases).

- Install it:

```bash
sudo apt update && sudo apt install ./terimg_ubuntu_<ubuntu version>_x64.deb
```

- Run it:

```bash
terimg  # read from webcam
terimg -p <path to an image>
```

- Other options:

```bash
terimg -h
```



## Usage

```
Usage: terimg [-h] [--width VAR] [--brightness VAR] [--contrast VAR] [--text VAR] [--path VAR] [--video VAR]

Optional arguments:
  -h, --help      	shows help message and exits 
  -v, --version   	prints version information and exits 
  -w, --width     	number of chars in a row of the output string [default: 100]
  -b, --brightness	Number between 0-255 by which pixel intensities are incremented [default: 0]
  -c, --contrast  	Float number defining contrast. 1.0 is no change in contrast, 0.5 decrease 50%, and 1.5 increase by 150% [default: 1]
  -t, --text      	characters used in rendering the images. Ordered from darkest to brightest [default: "   .,:;i80@"]
  -p, --path      	Image input path. If not given, it will read from the video device [default: ""]
  -i, --video     	Index of video device (used in video device mode when image path is not given [default: 0]
```



## From source

- You need to install OpenCV first:

```bash
sudo apt install libopencv-dev
```

-  Then:

```bash
make
```

- then run the binary:

```bash
./build/bin/terimg
```

