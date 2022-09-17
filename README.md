URDF Parser
===========

This is a small URDF (Universal Robot Descriptor File) Parser library. It is intended to be
used to load the most important information needed to display a robot. It was created to
serve as a simple static library to be used in rbdl-toolkit and the rbdl library. One of the main desing goals was to keep it simple and provide a consistent error handling that may be
used to find errors in the URDF files that are loaded.

Insipiration was drawn from the urdfdom library and just as urdfdom it uses tinyxml as
the xml implementation.

Feel free to use it in your own projects.


### How to run
**1)** Creat a folder and Open
```
mkdir build && cd build
```

**2)** Configure with defaults for only building a library
```
cmake ..
```
Or configure with [Catch2](https://github.com/catchorg/Catch2) test. The catch.hpp has been in the repo.
```
cmake .. -DURDF_BUILD_TEST=1
```

**3)** Build library
```
make all
```

**4)** Run test file (step 2 is necessary)
```
./test_library
```

