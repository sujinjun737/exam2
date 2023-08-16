#!/bin/bash

# 交替运行的次数
num_runs=$1

# 参数检查
if [ $# -ne 1 ]; then
    echo "Usage: $0 <num_runs>"
    exit 1
fi

for ((i=1; i<=$num_runs; i++)); do
    echo "Running iteration $i"
    filename=big.pdf
    num_thread=3
    num_reads=10000000
    ./program_a $filename $num_thread $num_reads
    ./program_b $filename $num_thread $num_reads
done
