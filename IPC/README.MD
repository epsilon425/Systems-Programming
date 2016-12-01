Step by step Development of a string parser that creates a child process  
and passes string stream input from stdin to the child. The the second child is  connected to the third child and the third child suppresses redundant words  and instead increments a counter.  The child uses the standard command line sort program thats comes with standard UNIX OS.  
-->Parent, Child, 2nd Child is connected by two pipes  

current status  
===============  
10/28/2016  
-Build a model and practice the functionality of the pipe  
-->pipe_child.c: takes in user input of strings and passes it on to the child  
<<<<<<< HEAD
---->child passes it on to stdout.  
11/3/2016  
-Succesfully connected the parent with the first child.  
 -->Receives data from standard input by opening a stream and using fgetc.  
	-->inputs data into the pipe using fputc.  
  
11/9/2016
-The second child is created and succesfully receives the sorted words from  
the first child. The second child suppresses duplicated words.  
  
11/10/2016  
-New rule has been implemented  
-->Any word smaller than 3 characters will be ignored  
-->Any word larger than 30 characters will be truncated  
-->Any string that is a not alphabet will be ignored, and be the divider  
between words.  

example)  
aaaa&aaaa&DDDDDD&DDDDDD9877766867888aaa7667766555aaa  
--> 3 aaa 
    1 aaaa  
    2 dddddd

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
>>>>>>> e51d3d7d5bb5422fcdd0ddd0f13e8e348891f8fa
