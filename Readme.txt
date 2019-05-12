*********************************************************
 MEHMET OZKAN
 Foundation of Operating Systems
 Project #1: New Island Shell - Writing Your Own Shell
 October 11, 2017
 Instructor: Dr. Ajay K. Katangur
*********************************************************

		Contents of the Directory

1.Readme.txt	- Describing the contents of directory and solutions of the problems
2.guish.cpp	- Compiled Source file 
3.guish.l	- Source File
4.Makefile	- Extraction portions to be compiled

		Methods of Achieving the Project Requirements 

1. Fork() and Execv() functions are used for creating a process and executing the commands from the user.
2. Signal() functions are used to handle Ctrl C, Ctrl \ and Ctrl Z signal interrupts.
3. Exit(EXIT_FAILURE) function used to terminate process when user types "exit".
   Using alone break or exit(0) procedures in exit statement didn't work to terminate process properly.
4. Dup2() functions are used both input and output redirections.
5. Multi-dimensional array techniques are used to store commands in the history.
   Queue, stacks and one dimensional array data structures didn't achieve the requirements of the history section.  
   In queue and stack approaches, only commands with no arguments saved in history and accessing the last nth command in history didn't work accurately.
   Creating more template queue and stacks discussed to access last nth command while doing the project, but these approaches were extremely hard and
   time consuming. By using multi-dimensional arrays in the history section, we can easily store each commands with arguments and access last nth command accurately. 


		
		