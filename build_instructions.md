# Build Instructions

## Getting the Code

To retrieve the code from GitHub:

```cmd
git clone https://github.com/TimZoet/common.git source
```

## Exporting to Conan

To export the `common` package to your local Conan cache:

```cmd
conan export --user timzoet --channel v1.0.0 source
```

Make sure to update the channel when the version is different.

## Including the Package

To include the package from your `conanfile.py`:

```py
def requirements(self):
    self.requires("common/1.0.0@timzoet/v1.0.0")
```

To find the package and link it in one of your `CMakeLists.txt`:

```cmake
find_package(common REQUIRED)
target_link_libraries(<target> common::common)
```

## Building Tests

Before building tests, you must first modify the `conanfile.py`. Change the name of the package to something other than
`common`, e.g. `common_test`. This is needed because the `bettertest` package relies on the `common` package, causing a
cyclic dependency.

After fixing the name, invoke `conan install`:

```cmd
conan install -pr:h=source/buildtools/profiles/common-test-vs2022-release -pr:b=source/buildtools/profiles/common-test-vs2022-release -s build_type=Release --build=missing -of=build source
```

Then generate and build with CMake:

```cmd
cmake -S source -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE:FILEPATH=conan_toolchain.cmake
cmake --build build --config Release
```

Finally, run the test application:

```cmd
cd build/bin/tests
.\common_test
```
