# project-teams

This is an assignment that I coded for my Programming in C++ course at Northeastern University. The purpose of this program is to split a roster of students into teams of 3-4, ensuring that higher preference is given to students’ choice of team members than the need for skills-balanced teams. These are some of the requirements that should be met:

    1. The teacher MUST honor student’s request for “DONOT want to work with someone”.
    2. The teacher SHOULD honor student’s request to work with someone as much as possible.
    3. Teams SHOULD be “skill-balanced” as much as possible. For example, you want to make sure that each team has someone who is knowledgeable in the programming language and is experienced in 
       debugging as well as in algorithm development. Ideally, we would want to avoid a situation where one team has all members with ‘Advanced’ skill levels and another team with all ‘Begineer’        skills levels. However, we would like to give preference to students’ choice of teammates.


These are the files in this repository:
- algorithm.txt : some pseudocode/thoughts written out before I coded the program
- functions.cpp : implementation of functions declared in functions.hpp
- functions.hpp : header file for all functions used in main.cpp
- main.cpp :
- roster1.csv : in class 1, holds each student's information in the following order
    1. Username
    2. Level of experience with C++
    3. Level of experience with gdb?
    4. Level of experience in algorithms?
    5. students you do NOT want to work with?
    6. students that you would like to work with?
- roster2.csv : in class 2, holds each student's information in the following order
    1. Username
    2. Level of experience with C++
    3. Level of experience with gdb?
    4. Level of experience in algorithms?
    5. students you do NOT want to work with?
    6. students that you would like to work with?
- score.hpp : header file for an enum of scores
- student.hpp : header file for a struct representing a Student
