# MATRIX
This project provides an implementation of a Matrix library in modern C++.
It supports square matrices with full RAII semantics, and determinant computation using Gaussian elimination.

## Installation:
Clone this repository, then reach the project directory:
```sh
git clone https://github.com/bgclutch/Matrix_Task_cpp.git
cd Matrix_Task_cpp
```

## Building:
1. Build the project:
 ```sh
cmake -B build
cmake --build build
```

## Usage:
1. Navigate to the ```build``` folder:
```sh
cd build
```
2. Run matrix:
```sh
./matirx/matrix
```

## Running tests:
For End To End tests:
1.1 Navigate to the ```tests``` directory:
```sh
cd tests/EndToEnd
```
1.2 Run default tests with the Python script:
```sh
python3 testrun.py
```
1.3 (Optional) Or ```regenerate``` test cases:
```sh
python3 testgen.py
```
And run it as in step 2.

For unit tests:
2.1 Navigate to the ```build``` folder:
```sh
cd build
```
2. Run unit tests:
```sh
./tests/tests
```
