The followng myar.c file is my own implementation of the POSIX System call ar.  It archives files into the format of an ar file and is compatible with the actual syscall as well as syscall created ar files.  
-function q    
1. Terminal syntax: archiver q "archive name" "file name"  
2. function: Adds a file to an existing archive, if archive does not exist, create an archive with the name, and then add the file.    
-function x  
1. Terminal syntax: archiver x "archive name" "filename"  
2. function: Extracts a file matching to the "filename" from the archive. Restores the original permission and utime.    
-function t    
1. Terminal syntax: archiver t "archive name"  
2. function: Prints out the names of the archived files in a list.    
-function v    
1. Terminal syntax: archiver v "archive name"  
2. function: Prints out a detailed information about the files in the archive.  Mode/gid/uid/date/size/Filename    
-function d    
1. Terminal syntax: archiver d "archive name" "file name"  
2. function: Deletes the designated file ("file name") from the archive    
-function A    
1. Terminal syntax: archiver A "archive name"  
2. function: Appends all files in the current directory that have been modified within the last hour, except for the archive itself.  


