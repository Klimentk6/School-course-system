## Description

This is a console application written in C++ that simulates a system for managing users, courses, and messages between them. The program is built using **object-oriented programming (OOP)** and the **Command Pattern**, making it flexible and easy to extend.

## Main Features

- **User Management**
  - Add new users  
  - Delete users  
  - Display a list of all registered users  

- **Course Management**
  - Create new courses  
  - Enroll users in a course  
  - Remove users from a course  
  - Display all courses and their participants  

- **Messaging**
  - Send messages between users  
  - View incoming and outgoing messages  

- **Command Handling (Command Pattern)**
  - Each command is implemented as an object that inherits from the `Command` interface  
  - A central **CommandFactory** creates the correct command based on user input  

- **Validation and Feedback**
  - Centralized input validation  
  - Clear error messages for invalid commands or actions  

## Technologies

- **Language**: C++  
- **Design Pattern**: Command Pattern  
- **Interface**: Console-based (CLI)  
- **Dependencies**: None – uses only the C++ Standard Library  
