#!/usr/bin/bash

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 input_directory output_directory"
    exit 1
fi

input_dir=$1
output_dir=$2

mkdir -p "$output_dir"
rm -rf "$output_dir"/*

temp_file="temp_file.txt"
> "$temp_file"

# Traverse through all files and get their name length
find "$input_dir" -type f | while read -r file_name; do
    # Extract the base name (without extension)
    file_name_only=$(basename "$file_name")
    name_without_ext="${file_name_only%.*}"
    
    # Get the length of the file name (without extension)
    file_name_length=${#name_without_ext}
    
    # Save the file name length and file path
    echo "$file_name_length" "$file_name" >> "$temp_file"
done

# Copy files in order of name length
i=0
sort -n "$temp_file" | while read -r name_len file_name; do
    # Get the original file extension
    extension="${file_name##*.}"
    file_name_only=$(basename "$file_name")
    
    # Create a subdirectory based on the name length
    mkdir -p "$output_dir/$name_len"
    
    # Rename the file in ascending order and copy it
    new_file_name="${i}_${file_name_only}"
    cp "$file_name" "$output_dir/$name_len/$new_file_name"
    i=$((i + 1))
done

# Clean up the temporary file
rm "$temp_file"

echo "Files copied and renamed successfully."
