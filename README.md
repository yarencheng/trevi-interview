# trevi-interview

A string filter implement by DFA.

# Build

* Clone repository and the submodule.

    ```
    git clone git@github.com:yarencheng/trevi-interview.git
    cd trevi-interview/
    git submodule init
    git submodule update
    ```

* Build and pack the executable binary in to docker image.

    `docker build --tag trevi-interview .`

# Interactive mode

Start interactive mode with docker image.

`docker run -it --rm trevi-interview filter`

## Usage

Input anything.

```
abc
> abc
```

Add dirty word by appending `+`

```
abc
> abc
+b
```

Words is mask by `*` if it contains dirty words.

```
abc
> abc
+b
abc
> a*c
```

`中文` is OK

```
我是中文
> 我是中文
+是中
我是中文
> 我**文
```

Search dirty words by appending `?`

```
+b
+bc
+bcd
?b
>  [b]cd [b] [b]c
```

# Profiling mode

## How to run
Enable Profiling mode with additional parameter `filter --profiling`.
A CSV file `report.csv` is generated inside `pwd` in the end.
For more parameters, see `filter --help`.

```
docker run -it --rm \
    --volume `pwd`/:/workdir \
    trevi-interview \
    filter --profiling
```

## How it works

Use [getrusage()](http://man7.org/linux/man-pages/man2/getrusage.2.html) to record CPU time used by `add()` & `filter()`. To get the CPU time which is spent by `add()` & `filter()`, use [getrusage()](http://man7.org/linux/man-pages/man2/getrusage.2.html) to record current CPU time before and after the execution. It accurate to micro seconds.

## Column in `report.csv`

* Column 1: Number of dirty words
* Column 2: Time consumption(ms) during `add()`
* Column 3: Time consumption(ms) during `filter()`

```
[report.csv]
# dirty words, add() ms, filter() ms
100000,185063,179961
200000,372231,403642
300000,606368,583005
400000,780404,757843
500000,1033700,974128
600000,1250405,1159814
700000,1446695,1414249
800000,1608281,1684150
900000,1814630,1839142
1000000,2134483,2089447
1100000,2496606,2174671
1200000,2633108,2534972
1300000,2818236,2745403
1400000,3015094,2907420
1500000,3172503,3204875
1600000,3445925,3288202
1700000,3563307,3611462
1800000,3669621,3390016
1900000,4321817,4251598
2000000,4454588,4308447

```

# Complexity

## Time complexity

### `DFAFilter::add()`

* n: number of dirty words

* Best case: O( n * log(n) )

    * The first `for` loop costs `n`, if there is no collision on the `std::unordered_map`.
    * The second `for` loop costs `n * log(n)`.

* Worst case: O( n^2 )

    * The first `for` loop costs `n * n`, if there is collision on the `std::unordered_map`.
    * The second `for` loop costs `n * log(n)`.

> According to [cplusplus](http://www.cplusplus.com/reference/unordered_map/unordered_map/), the probability of collision approaching `1.0/std::numeric_limits<size_t>::max()` which is `18446744073709551615` and is fare more than `200000`. Therefore using `std::unsorted_map` is more reasonable than `std::map` here.

### `DFAFilter::filter()`

* a: number of dirty words
* b: length of string to be filtered
* c: length of a dirty word

* Best case: O( a * b * c )
    * if `c << b`
* Worst case: O( a * b^2 )
    * If `c ~ b`

## Space complexity

### `class DFAFilter`

* O(n): `unordered_map _tree`
* O(n): `unordered_set _dirtyWords`
* Total O(n)

### `DFAFilter::add()`

* n: size of the vector `const vector<wstring>& dirtyWords`
* m: length of a dirty word
* O(n*m)

### `DFAFilter::filter()`

* O(n): input parameter `const wstring& in`
* O(n): temporary buffer `wstringstream out;`


