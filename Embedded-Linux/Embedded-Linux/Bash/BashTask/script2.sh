#!/bin/bash

# Check if the source directory is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <source_directory>"
    exit 1
fi

# Name of the directory will manages
DIR_SRCPATH="$1"



# Check if the source directory exists
if [ ! -d "$DIR_SRCPATH" ]; then
    echo "The source directory '$DIR_SRCPATH' does not exist."
    exit 1
fi

# Path for directories that will be created
IMAGE_DIR="$DIR_SRCPATH/Images"
DOC_DIR="$DIR_SRCPATH/Documents"
OTHER_DIR="$DIR_SRCPATH/Others"

# Create subdirectories if they do not exist
mkdir -p "$IMAGE_DIR" "$DOC_DIR" "$OTHER_DIR"

# Function for printing
func(){
	local SRC_File=$1
	local DIS_Dir=$2
	mv "$SRC_File" "$DIS_Dir"
	echo " Move  $SRC_File to  $DIS_Dir successfully"
}


for file in "$DIR_SRCPATH"/*; do
    if [ -f "$file" ]; then
	# Extension name of file
        Extension="${file##*.}"
	# file name with the extension
        fileName="${file##*/}" 

	# Make Sure that file has an extension
        if [[ "$fileName" == *.* ]]; then
            case "$Extension" in
                jpg|png|gif)
                   func "$file" "$DOC_DIR"
                    ;;
                txt|doc|pdf)
                   func "$file" "$DOC_DIR"
                    ;;
                *)
                   func "$file" "$DOC_DIR"
                    ;;
            esac
        else
            mv "$file" "$OTHER_DIR"
	    
        fi
    fi
done

echo "Files organized successfully."
