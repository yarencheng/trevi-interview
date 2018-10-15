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
# dirty words, add() ms, filter() ms
100000,208716,48446
200000,424993,53898
300000,673326,52605
400000,862585,51553
500000,1241880,52417
600000,1370359,52642
700000,1578414,57690
800000,1799462,51109
900000,2019286,52063
1000000,2325842,51698
1100000,2654198,52717
1200000,2953958,58391
1300000,2992349,53074
1400000,3253307,54117
1500000,3473581,55512
1600000,3666539,52594
1700000,3852485,47672
1800000,4167544,55829
1900000,4780916,51982
2000000,5012406,49030


```

# Complexity

## Time complexity

### `DFAFilter::add()`

* n: number of dirty words

* Best case
    * `O(n)`: The first `for` loop
        * `O(1)`: if there is no collision inside the `std::unordered_set`.
        * `O(log(n))`: add a string into sorted `std::map`.
    * Total: `O(n*log(n))`

* Worst case: O( n^2 )
    * `O(n)`: The first `for` loop
        * `O(n)`: if there a collision inside the `std::unordered_map`.
        * `O(log(n))`: add a string into sorted `std::map`.
    * Total: `O(n*n)`

> According to [cplusplus](http://www.cplusplus.com/reference/unordered_set/unordered_set/), the probability of collision approaching `1.0/std::numeric_limits<size_t>::max()` which is `18446744073709551615` and is more than `200000`. Therefore, using `std::unordered_set` is more reasonable than `std::set` here.

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

* n: size of the vector `const vector<wstring>& dirtyWords`
* m: length of a dirty word
* O(n*m): `unordered_map _tree`
* O(n*m): `unordered_set _dirtyWords`
* Total O(n*m)

### `DFAFilter::add()`

* n: size of the vector `const vector<wstring>& dirtyWords`
* m: length of a dirty word
* O(n*m)

### `DFAFilter::filter()`

* O(n): input parameter `const wstring& in`
* O(n): temporary buffer `wstringstream out;`
* Total O(n)


