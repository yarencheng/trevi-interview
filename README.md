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

Enable Profiling mode with additional parameter `filter --profiling`.
A CSV file `report.csv` is generated inside `pwd` in the end.
For more parameters, see `filter --help`.

```
docker run -it --rm \
    --volume `pwd`/:/workdir \
    trevi-interview \
    filter --profiling
```

* Column 1: Number of dirty words
* Column 2: Time consumption(ms) during `add()`
* Column 3: Time consumption(ms) during `filter()`

```
[report.csv]
# dirty words, add() ms, filter() ms
100000,177,150
200000,999365,322
300000,604,999507
400000,999753,999672
500000,1000004,999831
600000,1000236,999998
700000,1999404,1000171
800000,1000592,1999418
900000,1999780,1999563
1000000,2000072,1000718
1100000,2000100,1999889
1200000,2999340,2000104
1300000,2000601,2000250
1400000,2999846,2999343
1500000,3000072,2000649
1600000,3000366,2999760
1700000,3000580,3000125
1800000,3999622,3000092
1900000,4000523,3999699
2000000,4000437,3999832

```


# TODO

- [ ] BUG: wrong time report by profiler