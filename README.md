## os_shell

#Q40. The shell is a program that interprets commands and acts as an intermediary between the user and the inner workings of the operating system and as such is arguably one of the most 
important parts of a Unix system. In this assignment, we shall start making our very own version of a Unix shell. Submission: Write a simple shell in C. Call it simplesh.c The shell should implement following features: 
● The shell should run continuously, and display a prompt (>, similar to $) when waiting for input. Include the full path of the current directory also in the prompt followed by the “>” sign (for ex., /usr/home/me/Desktop>). ● The shell should read a line from input one at a time. 
● After parsing and lexing the command, the shell should execute it. ● Implement the following Built-in Commands, ● clear: clear the screen ● env: displays all environment parameters 
● cd 
● pwd: prints the current directory 
● mkdir : creates a directory called "dir" 
● rmdir : removes the directory called "dir" 
● ls: lists files in current directory ( ls –l: option also need to be supported ) 
● history: displays the last commands the user ran, with an offset next to each command. Last commands can be stored in a file and may be displayed to user when the command is issued. 
● exit: exits the shell The commands are the same as the corresponding Linux commands by the same name. Do "man" to see the descriptions. You can use the standard C library functions chdir, getcwd, mkdir, rmdir, readdir, stat etc. to implement the calls. All calls should handle errors properly, with an informative error message. Look up the perror call. These commands are called builtin commands since your shell program will have a function corresponding to each of these commands to execute them; no new process will be created to execute them. (Note that all these commands are not builtin commands in the bash shell, but we will make them so in our shell). 

● Any other command typed at the prompt should be executed as if it is the name of an executable file. For example, typing "a.out" should execute the file a.out. The file can be in the current directory or in any of the directories specified by the PATH environment variable (use getenv to get the value of PATH). The file should be executed after creating a new process and then executing the file onto it. The parent process should wait for the file to finish execution and then go on to read the next command from the user. The command typed can have any number of command line arguments. 

● Support background execution of commands. Normally when you type a command at the shell prompt, the prompt does not return until the command is finished. For background executions, the prompt returns immediately, the command continues execution in the background. Typing an "&" at the end of a command (for ex., a.out&) should make it execute in the background. (Note: Background execution needn‟t be supported for built in commands)...
