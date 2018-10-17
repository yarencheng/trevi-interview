# trevi-interview

A multi-pattern string filter implement by [Aho–Corasick algorithm](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm).

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
>  [bcd, b, bc]
```

Enter a empty string to exit

```
aaa
> aaa


EXIT

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

* class `ACCFilter`


* `ACCFilter::add(dirtyWord)`
    * `n`: length of input `dirtyWord`
    * time complexity: `O(n)`
    * space complexity: `O(n)`

* `ACCFilter::build()`
    * `Dn`
        * `D1`: the length of the 1st dirty word
        * `D2`: the length of the 2nd dirty word
        * ...
        * `Dn`: the length of the nth dirty word
    * time complexity: `O(D1 + D2 + ... + Dn) = O(D)`
    * space complexity: `O((D1 + D2 + ... + Dn)*2) = O(D)`

* `ACCFilter::filter(sentence)`
    * `m`: length of input `sentence`
    * `l`: Total appearance of each dirty word
    * time complexity: `O(m + l)`
    * space complexity: `O(m + m) = O(m)`


