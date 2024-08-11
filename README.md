# SVG Example for Qt...

## Build like this on linux

1. Set up the cmake environment
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=/home/sr/Qt/6.7.2/gcc_64/lib/cmake -DXKB_INCLUDE_DIR=/usr/include/xkbcommon -DXKB_LIBRARY=/usr/lib/x86_64-linux-gnu/libxkbcommon.so -S . -B build/Desktop-Debug
```

where 
```M̀AKE_PREFIX_PATH```, ```XKB_INCLUDE_DIR``` and ```XKB_LIBRARY``` need to be adjusted.

2. Build using 

```bash
cmake --build build/Desktop-Debug
```

to clean

```bash
cmake --build build/Desktop-Debug --target clean
```



##

The helicopter is from: 

https://www.svgrepo.com/svg/396637/helicopter 

and available under Apache License



