Step by step Development of a string parser that creates a child process  
and passes string stream input from stdin to the child where the child  
sorts the string and passes it on the stdoutput with the string truncated  
in the following fashion: aaaabcc-->a4bc2    

current status  
===============  
-Build a model and practice the functionality of the pipe  
-->pipe_child.c: takes in user input of strings and passes it on to the child  
---->child passes it on to stdout. 
-Finished creating a program where it takes in lines of text as standard input while 
discerning each seperation of words by a non-alphabetic character (space, new line, numbers , etc). 
Each seperated word then will be sorted and then duplicates will be filtered.
-Outputting result will an integer showing how many instances of the word exsits within the file 
and the word it self. 

--> ex) abc@abc#bbb
-->output: 2 abc
           1 bbb 
           
*Very standard practice program using pipes/execl/forks. 
