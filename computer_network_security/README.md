# Computer And Network Security

This repository contains the Gradebook program. This is a basic command line program that simulates a gradebook tool that a teacher or professor might use. This program was written in C and there are multiple .c files which make up the program as a whole. There is an accompanying makefile which builds the executable. 

The relevant files are found through the /buildit-21-master/build filepath. 

#### These are the 'admin.c' 'gradebook.c' 'student.c' and 'teacher.c' files. 

The overall goal of this project was to construct a program that takes in user input but to ensure that it was impenetrable to attacks such as buffer overflows. 

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

It follows standard username/password storing practices, comparing if supplied passwords
matches the stored one in the "database". In this instance, all of the storage done by the program is stored to textfiles locally on the 
hard drive. 

After logging in, the program acts according to whether the account is designated as either a teacher or a student since there are 
different functions which accompany the different user permissions. A teacher account can manage classes and enroll students and mark
their grades in the respective classes. A student can login and and check for a list of enrolled classes and check their grades in each 
class that they are enrolled in.

This program writes and reads data to and from a textfile so that upon execution it can continue from the same state where it left off, 
i.e. it keeps track of all the grades and classes that a teacher might have created and modified from the last session.
