#!/bin/sh

datasize=$DATASIZE_MIN
csv_file="result.csv"

echo "# dirty words,time(ms) of DFAFilter::add()" > $csv_file

while [ "$datasize" -le "$DATASIZE_MAX" ]; do
    filter="Profiler/Profiler.test/$datasize"
    echo ">>> [$filter] Run ... "
    ./profiler --gtest_filter=$filter

    gprof profiler gmon.out -p -b | grep '  interview::DFAFilter::add\|  interview::DFAFilter::filter' > gprof_result
    add_result=$(cat gprof_result | grep '  interview::DFAFilter::add' | tail -1)
    filter_result=$(cat gprof_result | grep '  interview::DFAFilter::filter')

    echo $add_result
    echo $filter_result

    set -- $add_result
    add_time=$6
    set -- $filter_result
    filter_time=$6

    echo ">>> [$filter] DFAFilter::add()    spent $add_time ms"
    echo ">>> [$filter] DFAFilter::filter() spent $filter_time ms"

    echo "$datasize,$add_time,$filter_time" >> $csv_file

    datasize=$((datasize + $DATASIZE_STEP))
done

bash