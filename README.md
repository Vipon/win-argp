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
|       |  Win32  | Mac Os X |
|:------|:-------:|:--------:|
| MSVC  | Support | -------- |
| Clang | Support | Support  |

## Cmake setup
* Change install directory:
    * -DWIN_ARGP_INSTALL_PREFIX="PATH_TO_INSTALL_DIRECTORY"
* Change type of result library:
    * -DWIN_ARGP_LIB_TYPE=[SHARED/STATIC]
    * Default value SHARED (recomended)
    * if WIN_ARGP_LIB_TYPE=STATIC -> produce more necessary static libs. You need to link all of them to result program.

