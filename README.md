# win-argp
Cross platform analog for gnulin argp. The main goal is to make programs more
portable to Windows operation system.

* getopt - sources taken from FreeBSD
* argp - sources taken from argp-standalone project

## Configure and Build
### Build with Visual Studio
```
mkdir build
cd build
cmake ..
cmake --build .
ctest -C Debug
```

### Build with Ninja
```
mkdir build
cd build
cmake -G Ninja ..
ninja
ninja test
```

## Support build setup
| Compliler | Support Status |
|:----------|:--------------:|
| MSVC      |  Full Support  |
| Clang     |  Full Support  |
