#!/bin/sh

datasize=$DATASIZE_MIN
csv_file="result.csv"

echo "# dirty words,time(ms) of DFAFilter::add()" > $csv_file

while [ "$datasize" -le "$DATASIZE_MAX" ]; do
    filter="Profiler/AddTest.add/$datasize"
    echo ">>> Run $filter ... "
    ./profiler --gtest_filter=$filter

    gprof=`gprof profiler gmon.out -p -b | grep '  interview::DFAFilter::add' | tail -1`
    set -- $gprof
    interval=$6
    echo $interval
    echo ">>> Run $filter ... ($interval)"

    echo "$datasize,$interval" >> $csv_file

    datasize=$((datasize + $DATASIZE_STEP))
done

bash