Step by step Development of a string parser that creates a child process  
and passes string stream input from stdin to the child where the child  
sorts the string and passes it on the stdoutput with the string truncated  
in the following fashion: aaaabcc-->a4bc2    

current status  
===============  
-Build a model and practice the functionality of the pipe  
-->pipe_child.c: takes in user input of strings and passes it on to the child  
---->child passes it on to stdout. 
