#!/usr/bin/bash
# File name of the C or C++ program
SOURCE_FILE="main.cpp"
OUTPUT_FILE="main"

# Check if the source file exists
if [ ! -f "$SOURCE_FILE" ]; then
  echo "Error: $SOURCE_FILE not found!"
  exit 1
fi

# Determine file extension
FILE_EXTENSION="${SOURCE_FILE##*.}"

# Check if the source file is C or C++ and compile accordingly
if [ "$FILE_EXTENSION" == "c" ]; then
    # Compile C code using gcc
    echo "Compiling C code $SOURCE_FILE..."
    gcc -o $OUTPUT_FILE $SOURCE_FILE -pthread
elif [ "$FILE_EXTENSION" == "cpp" ] || [ "$FILE_EXTENSION" == "cc" ] || [ "$FILE_EXTENSION" == "cxx" ]; then
    # Compile C++ code using g++
    echo "Compiling C++ code $SOURCE_FILE..."
    g++ -o $OUTPUT_FILE $SOURCE_FILE -pthread
else
    echo "Unsupported file extension: $FILE_EXTENSION"
    exit 1
fi

# Check if the compilation was successful
if [ $? -eq 0 ]; then
  echo "Compilation successful. Running $OUTPUT_FILE..."
  # Run the compiled executable
  ./${OUTPUT_FILE} 10 6 2 6 6 3
else
  echo "Compilation failed. Please check your code for errors."
  exit 1
fi