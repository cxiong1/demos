# Computer And Network Security

This repository contains the Gradebook program. This is a basic command line program that simulates a gradebook tool that a teacher or professor might use. This program was written in C and there are multiple .c files which make up the program as a whole. There is an accompanying makefile which builds the executable. 

The relevant files are found through the /buildit-21-master/build filepath. 

#### These are the 'admin.c' 'gradebook.c' 'student.c' and 'teacher.c' files. 

The overall goal of this project was to construct a program that takes in user input but to ensure that it was impenetrable to attacks such as buffer overflows. 

## Program functionality
There are 3 main types of accounts that are recognized by the system: `admin`, `teacher`, `student`. Depending on login, the program will
branch off and handle specific commands from the command line.

`admin`:   
  -create other accounts for teacher and students
  
`teacher`:  
  -create classes  
  -add students to classes  
  -assign grades/marks to students  
 
`student`:  
  -check list of enrolled classes  
  -check current grade in each class  

## Program execution

The program follows a shell type architecture, where upon execution, it prompts the user for input. It continously asks for input until
the program forced closed or if the user exits the program themselves.

![gradebook program control flow](https://github.com/cxiong1/demos/blob/master/computer_network_security/gradebookdiagram.jpg)

There are two types of users for this program, teachers and students. These permissions are designated at the time of account creation.
A new account can only be created by an administrator. This event occurs at the start of execution, before it prompts the user for their 
login information, it prompts login or signup. If the user enters 'signup' into the console, the program then asks for 'credentials'. 
This is a 32 character string stored in a textfile which only administrators should have access to. The program checks if this file 
exists on startup. If the file exists, it retrieves the credential key, if it doesn't, it randomly generates the 32 characters and 
writes it to the textfile.

## Program auxilliary functionality

Username and passwords are stored as plaintext in a local textfile. Login is accomplished by comparing if supplied passwords
matches the stored one in the "database". 

This program writes and reads data to and from a textfile so that upon execution it can continue from the same state where it left off, 
i.e. it keeps track of all the grades and classes that a teacher might have created and modified from the last session.

## Program security

Much of the validity checking and sanitization of inputs occurs in 'utils.c' It uses `regex` as its main form of input checking. It 
whitelists only acceptted characters and any inputs that have blacklisted characters are rejected. The input is discarded and the 
program assumes as if no input was entered in the first place. This helps protect against buffer overflow type attacks which rely on 
using an input to overwrite into the instruction pointer of the stack.

