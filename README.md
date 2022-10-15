# Terimg

In-terminal ASCII image viewer. 

It can show an image if a path is given, otherwise show video device stream.

![](demo.png)

## How to run

- Download binary from the [releases](https://github.com/hasauino/terimg/releases).

- Give it execution permission:

```bash
chmod +x terimg
```

- Run it:
```bash
./terimg
./terimg -h # for other options
```



## From source

- You need to install OpenCV. Then:

```bash
make
```

- then run the binary:

```bash
./build/bin/terimg
```

