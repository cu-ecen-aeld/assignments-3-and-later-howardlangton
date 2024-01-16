#!/bin/sh
# Assignment 1 finder.sh
#
# Check number of arguments
if [ $# -ne 2 ]
then
	echo "Expected 2 arguments"
	echo "Usage: finder.sh filesdir searchstr"
	echo "You provided $# arguments"
	exit 1

fi

# Exit if  $1 is not a directory
if [ ! -d $1 ]
then
	echo "$1 is not a directory, exiting..."
	exit 1	
fi

number_of_files=$( find -L $1 -type f | wc -l )
# echo $number_of_files

number_of_searchstr=$(find -L $1 -type f  -exec grep $2 {} \; | wc -l)
# echo $number_of_searchstr
echo "The number of files are ${number_of_files} and the number of matching lines are ${number_of_searchstr} "
