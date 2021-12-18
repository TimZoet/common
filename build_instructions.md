# Build Instructions

## Dependencies

When using Conan, you will need to have the [pyreq](https://github.com/TimZoet/pyreq) package installed.

When building tests, the [BetterTest](https://github.com/TimZoet/BetterTest) package is needed.

## Cloning

This project uses git submodules. Cloning therefore requires an additional flag:

```cmd
git clone git@github.com:TimZoet/common.git source --recurse-submodules
```

## Exporting to Conan

To export the `common` package to your local Conan cache:

```cmd
cd source
conan export . user/channel
```

## Building and Installing Locally

Generating project files can be done using e.g.:

```cmd
mkdir build && cd build
cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX=..\install ..\source
```

Then build and install using your preferred method.

## Building Tests

Before building tests, you must first modify the `conanfile.py`. Change the name of the package to something other than
`common`, e.g. `common_test`. This is needed because the `BetterTest` package relies on the `common` package, causing a cyclic dependency.

With that done, install the required packages to your build folder and generate the project files:

```cmd
mkdir build && cd build
conan install -s build_type=Release -o build_tests=True --build=missing ..\source
cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" ..\source
```

Then build and run the tests.
