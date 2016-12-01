This project will include step by step coding I have gone through in order to become familiarized and adept in Systems Programming using the standard POSIX syscalls.          

1. Goldbach  
-Practices: Bit mapping, Bit operations, general algorithm  
-function: calulates all prime numbers up to user's input and uses the prime numbers to get two highest prime numbers that results to another user's input.    
2. Archive  
-Practices: Standard I/O of POSIX as well as traversing a file by its raw data, and general algorithm  
-function: Emulates the POSIX "ar" Syscall. Compatible with the actual ar Syscall.    
3. Signal  
-Practices: Message queues and Signals in order to track and read records.  Also uses Shared memory in order to record datas between multiple processes.  
-function: Compute.c calculates the perfect number starting from the number take from the command line argument  and sends it to manage.c using message queues. Manage.c uses the data received from message queue to update the data record in shared memory.  Lastly the record.c reads the data from shared memory and outputs the result.  
4. IPC  
-Practices: Pipes,execl, POSIX standard buffered I/O  
-function: reads a text file and truncate/find duplicate based on the set rule    
