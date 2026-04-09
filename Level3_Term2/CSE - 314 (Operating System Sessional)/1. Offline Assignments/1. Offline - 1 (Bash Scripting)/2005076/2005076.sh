#!/usr/bin/bash

if [ $# -lt 2 ]; then
    echo "Use: $0 -i input_file.txt"
    exit 1
fi

#for checking whether the input file is in valid format

isDirectory() {
    [[ -d $1 ]]
}

isFile() {
    [[ -f $1 ]]
}

isNumber() {
    [[ $1 =~ ^[0-9]+$ ]]
}

isBoolean() {
    [[ $1 == "true" || $1 == "false" ]]
}

checkInputFile(){
    input_file=$1
    while IFS= read -r line;
    do
        input_array+=("$line")
    done < $input_file

    IFS=$' '

    if [[ ${#input_array[@]} -ne 11 ]]; then
        echo "Error: The input file must contain exactly 11 lines."
        exit 1
    fi

    if ! isBoolean ${input_array[0]}; then
        echo "Error: Invalid value for 'Use Archive'. Expected 'true' or 'false'."
        exit 1
    fi

    if [[ ${input_array[0]} == "true" ]]; then
        allowed_archives="${input_array[1]}"
        for archive in $allowed_archives;
        do 
            if [[ $archive != "zip" && $archive != "tar" && $archive != "rar" ]]; then
                echo "Error: Invalid archive type '$archive'."
                exit 1
            fi
        done
    fi

    allowed_languages="${input_array[2]}"
    for language in $allowed_languages;
    do
        if [[ $language != "c" && $language != "cpp" && $language != "py" && $language != "sh" ]]; then
            echo "Error: Invalid programming language '$language'."
            exit 1
        fi
    done

    if ! isNumber ${input_array[3]}; then
        echo "Error: Invalid value for 'Total Mark'. Expected a number."
        exit 1
    fi

    if ! isNumber ${input_array[4]}; then
        echo "Error: Invalid value for 'Mismatch Penalty'. Expected a number."
        exit 1
    fi

    if ! isDirectory ${input_array[5]}; then
        echo "Error: Invalid value for 'Working Directory'. Expected a directory."
        exit 1
    fi

    sId_range=(${input_array[6]})
    if [ ${#sId_range[@]} -ne 2 ] || ! isNumber ${sId_range[0]} || ! isNumber ${sId_range[1]}; then
        echo "Error: Invalid value for 'Student ID Range'. Expected two numbers."
        exit 1
    fi

    if ! isFile ${input_array[7]}; then
        echo "Error: Invalid value for 'Expected Output File'. Expected a file."
        exit 1
    fi

    if ! isNumber ${input_array[8]}; then
        echo "Error: Invalid value for 'Guideline Violation Penalty'. Expected a number."
        exit 1
    fi

    if ! isFile ${input_array[9]}; then
        echo "Error: Invalid value for 'Plagiarism File'. Expected a file."
        exit 1
    fi

    if ! isNumber ${input_array[10]}; then
        echo "Error: Invalid value for 'Plagiarism Penalty'. Expected a number."
        exit 1
    fi

    echo "Input file is in valid format."


}


inputFile=""
while getopts ":i:" opt; 
do
    case $opt in
        i)
            inputFile=$OPTARG
            ;;
        \?)
            echo "Invalid option: -$OPTARG";
            exit 1
            ;;
    esac
done

if [[ ! -f $inputFile ]]; then
    echo "Input file does not exist."
    exit 1
fi

checkInputFile $inputFile

IFS=$'\n'
read -d '' -r -a inputLines < $inputFile

# for line in "${inputLines[@]}"; do                      # @ -> all elements of array
#     echo $line
# done

IFS=$' '                                                  

isArchived=${inputLines[0]}                               # ${} -> variable expansion  -> no $ inside ${}
allowedArchives=(${inputLines[1]})                        # () -> array
allowedLanguages=(${inputLines[2]})
allMark=${inputLines[3]}
mismatchPenalty=${inputLines[4]}
workingDirectory=${inputLines[5]}
idRange=(${inputLines[6]})
expectedOutput=${inputLines[7]}
guideline_violation_penalty=${inputLines[8]}
plagiarismFile=${inputLines[9]}
plagiarismPenalty=${inputLines[10]}
 

workingDirectory=$(echo "$workingDirectory" | tr -d '\r' | xargs)
if [[ ! -d $workingDirectory ]]; then
    echo "$workingDirectory"
    echo "Working directory does not exist."
    exit 1
fi
if [[ ! -f $expectedOutput ]]; then
    echo $expectedOutput
    echo "Expected output file does not exist."
    exit 1
fi
if [[ ! -f $plagiarismFile ]]; then
    echo "Plagiarism file does not exist."
    exit 1
fi


declare -A plagiarizedId;
while read line || [[ -n "$line" ]];
do
    plagiarizedId[$line]=1
    #echo $line
done < "$plagiarismFile"


mkdir -p issues checked 
rm -rf issues/* checked/*


echo "id,marks,marks_deducted,total_marks,remarks" > marks.csv


for submission in $workingDirectory/*;
do  
    archiveExtension="${submission##*.}"                                   # ## -> remove longest match from start; * -> match any character; . -> untill found dot (including dot)
    if [[ $archiveExtension == "txt" ]]; then                                
        continue
    fi

    # echo "Processing $submission"
    sId=$(basename $submission | cut -d "." -f1)                           # $()-> command substitution 
    sId=$(echo "$sId" | tr -d '\r' | xargs)                                # Clean up any whitespace or carriage returns

    marks=$allMark
    deductedMarks=0
    remarks=""
    if (( sId < idRange[0] || sId > idRange[1] )); then
        remarks+="Issue case #5: The submitted file is not in the valid student id range. "
        deductedMarks=$guideline_violation_penalty
        totalMarks=$(( 0 - deductedMarks ))
        echo "$sId,0,$deductedMarks,$totalMarks,\"$remarks\"" >> marks.csv
        cp -r $submission issues/
        continue
    fi

    submissionDirectory="$workingDirectory/$sId"
    folderFlag="false"
    if [[ $isArchived == "true" ]]; then                                   # [[ ]] -> for advanced string comparison
        if [ -d $submission ]; then
            deductedMarks=$guideline_violation_penalty
            remarks+="Issue case #1: Submission is a folder. "
            submissionDirectory="$workingDirectory/$sId";
            folderFlag="true"
            # mv $submission "$submissionDirectory/"

        else
            if [[ ! ${allowedArchives[@]} =~ $archiveExtension ]]; then       # =~ -> regex match; string =~ pattern
                deductedMarks=$guideline_violation_penalty
                cp -r $submission issues/
                remarks+="Issue case #2: Archive type not allowed. "
                totalMarks=$(( 0 - deductedMarks ))
                echo "$sId,0,$deductedMarks,$totalMarks,\"$remarks\"" >> marks.csv
                continue
            fi

            submissionDirectory="$workingDirectory/$sId"
            case $archiveExtension in
                "zip") 
                    unzip -n -q  $submission -d $workingDirectory
                    ;;

                "tar")
                    # mkdir -p "$submissionDirectory"
                    tar -xf $submission -C $workingDirectory
                    ;;

                "rar") 
                    # mkdir -p "$submissionDirectory"
                    unrar x -inul $submission $workingDirectory
                ;;
            esac
        fi
    
    else
        submissionDirectory="$workingDirectory/$sId"
        mkdir -p $submissionDirectory
        mv $submission "$submissionDirectory/"
    fi

    validLanguage=false
    fileLang=""
    for language in ${allowedLanguages[@]}; 
    do
        #echo "$submissionDirectory/$sId/$sId.$language"
        if [[ -f "$submissionDirectory/$sId.$language" ]]; then
            validLanguage=true
            fileLang=$language
            submittedFile="$submissionDirectory/$sId.$language"
            #echo $submittedFile
            break
        fi
    done

    # extractedFolder=$(basename $submissionDirectory)
    # if [[ $extractedFolder != $sId ]]; then
    #     deductedMarks=$guideline_violation_penalty
    #     remarks+="Issue case #4: Folder name does not match student ID. "
    # fi

    if [[ ! -d $submissionDirectory ]]; then
        deductedMarks=$guideline_violation_penalty
        # mv "$submission" issues/
        remarks+="Issue case #4: Folder name does not match student ID. "
        totalMarks=$(( 0 - deductedMarks ))
        echo "$sId,0,$deductedMarks,$totalMarks,\"$remarks\"" >> marks.csv
        continue
    fi

    if [[ $validLanguage == "false" ]]; then
        deductedMarks=$guideline_violation_penalty
        remarks+="Issue case #3: Invalid programming language. "
        mv $submissionDirectory issues/
        totalMarks=$(( 0 - deductedMarks ))
        echo "$sId,0,$deductedMarks,$totalMarks,\"$remarks\"" >> marks.csv
        continue
    fi


    if [[ ! -f $submittedFile ]]; then
        echo "Could not run program file. $submittedFile"
        exit 1
    fi

    temp="_output.txt"
    outPutFile="$submissionDirectory/${sId}${temp}"
    #echo $outPutFile
    #echo $submittedFile
    case $fileLang in
        c) gcc "$submittedFile" -o "$submissionDirectory/$sId" && "$submissionDirectory/$sId" > "$outPutFile" ;;
        cpp) g++ "$submittedFile" -o "$submissionDirectory/$sId" && "$submissionDirectory/$sId" > "$outPutFile" ;;
        py) python3 "$submittedFile" > "$outPutFile" ;;
        sh) bash "$submittedFile" > "$outPutFile" ;;
        # java) javac "$submittedFile" && java -cp "$submissionDirectory" "$sId" > "$outPutFile" ;;
    esac


    if [[ ! -f $outPutFile ]]; then
        echo "Could produce output file."
        exit 1
    fi

    flag="false"
    while IFS= read -r line;
    do
        if ! grep -Fxq "$line" "$outPutFile"; then
            marks=$((marks - mismatchPenalty))
            flag="true"
        fi
    done < "$expectedOutput"

    if [[ "$flag" == "true" ]]; then
        remarks+="Mark deducted for mismatch. "
    fi

    totalMarks=$(( marks - deductedMarks ))
    #echo "${plagiarizedId[$sId]}"
    plagiarismPenalty=$(echo "$plagiarismPenalty" | tr -d '\r' | xargs)
    if [[ -n "${plagiarizedId[$sId]}" ]]; then
        totalMarks=$(( - (allMark * plagiarismPenalty / 100) )) 
        remarks+="Plagiarism Detected. "
    fi

    
    #remarks=${remarks:-"All Checked"}             # :- -> default value if variable is 
    remarks+="All Checked"
    
    
    echo "$sId,$marks,$deductedMarks,$totalMarks,\"$remarks\"" >> marks.csv   # \" \" -> to ensure that any commas or special characters inside remarks are treated as part of the value and not as separate fields in the CSV

    if [[ "$remarks" =~ "All Checked" ]]; then
        if [[ "$folderFlag" == "true" ]]; then
            cp -r $submissionDirectory checked/
        else
            mv $submissionDirectory checked/
        fi
    else
        mv $submissionDirectory issues/
    fi
done
# ----------------------------------------------