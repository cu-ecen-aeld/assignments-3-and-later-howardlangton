#!/bin/sh
# Assignment 2 writer.sh
#
# Check number of arguments
if [ $# -ne 2 ]
then
	echo "Expected 2 arguments"
	echo "Usage: writer.sh writefile writestr"
	echo "You provided $# arguments"
	exit 1

fi

# Check directory exists, if not create it or throw an error
directory_name=$(dirname $1)
if [ ! -d ${directory_name} ]
then
	 error_msg=$(mkdir -p ${directory_name} 2>&1)
	 status=$?
	 if [ $status -ne 0 ]
	 then
		 echo "Directory ${directory_name} could not be created, error is ${error_msg}"
		 exit 1
	 fi
fi

# Copy $2 to $1 
error_msg=$(echo $2 2>&1 > $1)
status=$?

if [ $status -eq 1 ]
then
	echo  "File not created, error messsage was '${error_msg}'"
	exit 1
fi
