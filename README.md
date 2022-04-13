## This is a Text Editor

### To build the project the following is needed to be done:

```
mkdir build && cd build/ 
cmake .. && make
```

Adding sanitizers to the main program, if needed (sanitizers are already enabled for the tests):

```
-DADD_SANITIZERS=1
```

To run the main program:

```
make run_main
After that you need to insert the name of your file in text_for_fixing section
```

To run tests:

```
make run_tests
```

To run both main program and tests:

```
make run_all
```

To run clang format:

```
make clang_format
```