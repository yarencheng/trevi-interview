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

Add a dirty word by add a prefix `+` in front of the line.

```
abc
> abc
+b
```

Input with dirty words is masked with `*`

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



# TODO

- [ ] BUG: wrong time report by profiler