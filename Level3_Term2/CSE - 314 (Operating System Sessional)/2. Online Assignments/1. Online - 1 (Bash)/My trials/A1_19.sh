#!/usr/bin/bash

if [[ $# -ne 2 ]]; then
    echo "Invalid number of arguments"
    exit 1
fi

input_dir=$1
output_dir=$2

mkdir -p $output_dir
rm -rf $output_dir/*

> temp.txt

# for file_name in "$input_dir"/*; -> this will not give any file in subdirectories
# for file_name in $(find "$input_dir" -type f); -> this will give all files in subdirectories

find "$input_dir" -typen f | while read -r file_name;
do
    if file $file_name | grep -q "ASCII text"; then
        line_count=$(wc -l < $file_name)
        echo "$line_count" "$file_name" >> temp.txt
    fi
done

i=0
sort -n temp.txt | while read -r line_count file_name;
do
    bName=$(basename $file_name)
    new_file="${i}_${bName}"
    cp $file_name "$output_dir/$new_file"
    i=$((i+1))
done

rm temp.txt