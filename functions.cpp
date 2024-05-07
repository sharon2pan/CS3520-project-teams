#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include "functions.hpp"
using namespace std;

vector<Student> createRoster(vector<vector<string>> &fileRows) {
	vector<Student> students;

	// convert the fileRows into a vector of Students
	for (auto row : fileRows) {

		Student student;
		// set the username and scores of the new student
		student.username = row[0];
		student.scoreCPP = getScore(row[1]);
		student.scoreGDB = getScore(row[2]);
		student.scoreAlgo = getScore(row[3]);

		// add respective students to the notWork vector
		string noStudent;
		stringstream ss(row[4]);
		while (getline(ss, noStudent, ';')) {
			student.notWork.push_back(noStudent);
		}

		//add respective students to the yesWork vector
		string yesStudent;
		stringstream ss2(row[5]);
		while (getline(ss2, yesStudent, ';')) {
			if (yesStudent == " ") {
				student.yesWork = {};
			}
			else {
				student.yesWork.push_back(yesStudent);
			}
		}

		// students are not yet in groups
		student.inGroup = false;

		//add the student to the vector
		students.push_back(student);
	}

	return students;
}

Score getScore(string scoreString) {
	// match each string to its respective Score enum
	if (scoreString == "Beginner") {
		return Beginner;
	} else if (scoreString == "Intermediate") {
		return Intermediate;
	} else {
		return Advanced;
	}
}

vector<array<int, 3>> addScores(vector<vector<Student>> &allTeams) {
	//vector representing all the combined scores for each team
	vector<array<int, 3>> teamScores;

	//for each score, add up the scores for each student
	for (auto team : allTeams) {
		array<int, 3> scoreList;
		int CPPSum = 0;
		int GDBSum = 0;
		int algoSum = 0;
		for (auto student : team) {
			CPPSum += student.scoreCPP;
			GDBSum += student.scoreGDB;
			algoSum += student.scoreAlgo;
		}
		//set each sum to its appropriate index
		scoreList[0] = CPPSum;
		scoreList[1] = GDBSum;
		scoreList[2] = algoSum;

		//add the sum to the vector
		teamScores.push_back(scoreList);
	}

	return teamScores;
}

void print(vector<Student> &team, int CPPSum, int GDBSum, int algoSum, int acc) {
	//neatly print out all the combined sums of the scores
	cout << "Team name   " << "CPP   " << "GDB   " << "Algo" << endl;
	cout << "Team " + to_string(acc) + ":    " + to_string(CPPSum) + "     " + to_string(GDBSum) + "     " + to_string(algoSum) << endl;
}

bool isInNotWork(Student &thisStudent, Student &otherStudent) {
	bool willNotWork = false;
	// skip any students they do not want to work with
	for (auto notThisStudent : thisStudent.notWork) {
		if (toLowercase(otherStudent.username) == toLowercase(notThisStudent)) {
			willNotWork = true;
		}
	}
	return willNotWork;
}

string toLowercase(string &str) {
	//turn a string into all lowercase
	string temp = str;
	for (char &c : temp) {
		c = tolower(c);
	}
	return temp;
}

