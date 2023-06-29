# win-argp
Cross platform analog for gnulin argp. The main goal is to make programs more
portable to Windows operation system.

* getopt - sources taken from FreeBSD
* argp - sources taken from argp-standalone project

## Configure, Build and Install
### With Visual Studio
```
mkdir build
cd build
cmake ..
cmake --build . --config Release
ctest -C Release
cmake --install . --config Release
```

### With Ninja
```
mkdir build
cd build
cmake -G Ninja ..
ninja
ninja test
ninja install
```

## Support build setup
| Compliler | Support Status |
|:----------|:--------------:|
| MSVC      |  Full Support  |
| Clang     |  Full Support  |
