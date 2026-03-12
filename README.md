# MyList

Test assignment for serialization/deserialization of a doubly linked list with random pointers.

## Task

The program:

1. reads a text file `inlet.in`
2. builds a doubly linked list
3. restores `rand` pointers using indices from the input
4. writes the serialized list to a binary file `outlet.out`

Input format:

```text
<data>;<rand_index>
```

Example:

```text
apple;2
banana;-1
carrot;1
```

Where:

* `data` is the node payload
* `rand_index` is the index of the node referenced by `rand`
* `-1` means `rand == nullptr`

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

Place `inlet.in` near the executable or in the working directory, then run:

```bash
./my_list
```

The program creates `outlet.out`.

## Tests

```bash
cmake -S . -B build
cmake --build build
cd build
ctest
```

Or run the test binary directly:

```bash
./tests
```

## Notes

* Empty input file is treated as an empty list
* Invalid input format causes an exception
* `rand_index` must be `-1` or a valid node index
* Parsing is performed by the last `;` in the line, so `data` may contain `;`

## Binary format

The serialized binary file stores:

* number of nodes
* for each node:

  * string size
  * string bytes
  * `rand` index

`prev` and `next` are restored implicitly from node order.

## Implementation details

The list is built in two passes:

1. nodes are created and linked through `prev` / `next`
2. `rand` pointers are restored using stored indices

During serialization, node positions are computed from the current list state, and `rand` pointers are converted back to indices.

## Project structure

```text
.
├── main.cpp
├── my_list.h
├── test.cpp
├── CMakeLists.txt
└── README.md
```
