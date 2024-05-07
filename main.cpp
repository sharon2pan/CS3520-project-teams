#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <array>
#include <string>
using namespace std;

int main() {
	// allow user to enter a specific team size (either 3 or 4)
	int teamSize;
	cout << "Enter team size (3 or 4): ";
	cin >> teamSize;

	// allow user to enter a specific csv file to read from
	string rosterFile;
	cout << "Enter the roster file name to read: ";
	cin.ignore();
	getline(cin, rosterFile);
	cout << rosterFile << endl;

	//open the specified file 
	ifstream file;
	file.open(rosterFile, ios::in);
	vector<vector<string>> fileRows; // 2d vector to store the file's rows

	//read the file to find all the students
	while (file.good()) {

		vector<string> row;
		string line;
		getline(file, line);

		stringstream ss(line);
		// find all the information between the commas
		while (getline(ss, line, ',')) {
			// add it to the vector for this row
			row.push_back(line);
		}

		// add the row to the 2d vector
		fileRows.push_back(row);
	}

	// delete the first row, which is unnecessary because it is just the header, and last row
	fileRows.erase(fileRows.begin());
	fileRows.erase(fileRows.begin() + fileRows.size());

	//create a list of students from the strings read from the csv file
	vector<Student> students = createRoster(fileRows);

	//contains all of the teams that is formed from the students
	vector<vector<Student>> allTeams;

	//check to make sure num students is divisible by the specified size
	if (students.size() % teamSize == 0) {
		int numTeams = students.size() / teamSize;

		//iterating through all the students
		for (Student &thisStudent : students) {
			vector<Student> team;
			// if the student has people they want to work with and the team is not yet filled and this student is not in a team yet and 
			// the max number of teams has not been reached
			if (!thisStudent.yesWork.empty() && team.size() < teamSize && !thisStudent.inGroup && allTeams.size() < numTeams) {
				// add this student to the team
				thisStudent.inGroup = true;
				team.push_back(thisStudent);

				// iterate through the students again
				for (Student &otherStudent : students) {
					// skip any students they do not want to work with
					for (string notThisStudent : thisStudent.notWork) {
						if (toLowercase(otherStudent.username) == toLowercase(notThisStudent)) {
							continue;
						}
					}
					// add the other student to the team if this student wants to work with them and other student is not part of a team and this student is not in the other student's do not want to work with list
					for (string yesThisStudent : thisStudent.yesWork) {
						if (toLowercase(otherStudent.username) == toLowercase(yesThisStudent) && !otherStudent.inGroup) {// && !isInNotWork(otherStudent, thisStudent)) {
							otherStudent.inGroup = true;
							team.push_back(otherStudent);
						}
						}
						//if the size of the current team has reached its max, add it to allTeams
						if (team.size() == teamSize) {
							allTeams.push_back(team);
							break;
						}
					}
					//also add current team to allTeam if it's any size, as long as the max number of teams has not been reached
					if (team.size() < teamSize && team.size() > 0) {
						allTeams.push_back(team);
					}
				}
			}
		}

		// create a list of students who aren't in groups yet
		vector<Student> notInGroup;

		//add all the students who are not in groups to this list
		for (auto student : students) {
			if (!student.inGroup) {
				notInGroup.push_back(student);
			}
		}

		//fill in the remaining teams
		for (auto &team : allTeams) {
			if (team.size() < teamSize) {
				while (teamSize != team.size()) {
					//add to the team
					team.push_back(notInGroup[0]);

					//then get rid of it from the list of students who aren't in groups yet
					notInGroup.erase(notInGroup.begin());
				}
			}
		}

		//if there are still students left, create new teams out of those students
		if (notInGroup.size() > 0) {
			while (!notInGroup.empty()) {
				vector<Student> newTeam;
				//to ensure that each team will be of the specified size
				for (int i = 0; i < teamSize; i++) {
					//add to the team
					newTeam.push_back(notInGroup[0]);
					//then get rid of it from the list of students who aren't in groups yet
					notInGroup.erase(notInGroup.begin());
				}
				//check if the combined sums are within a specific range so that the teams are evenly distributed
				allTeams.push_back(newTeam);
			}
		}

		//vector storing all of the combined scores for each team
		vector<array<int, 3>> teamScores;
		//add up all of the scores for each time
		teamScores = addScores(allTeams);

		//for each team, neatly print out the scores
		for (int i = 0; i < allTeams.size(); i++) {
			array<int, 3> scoreList = teamScores[i];
			print(allTeams[i], scoreList[0], scoreList[1], scoreList[2], i+1);
		}

		//writing to a new csv file
		fstream fout;

		fout.open("allTeamsInfo.csv", ios::out | ios::app);

		//separate different elements by a comma, and lists with a semicolon
		//include team number, each student's username, and the combined scores
		fout << "Team number,student's username,combined scores of all students in the team" << endl;
		int teamNum = 1;
		for (int i = 0; i < allTeams.size(); i++) {
			fout << "Team " + to_string(teamNum) + ",";
			vector<Student> thisTeam = allTeams[i];
			for (int j = 0; j < 3; j++) {
				if (i <= 1) {
					fout << thisTeam[j].username << ";";
				}
				else {
					fout << thisTeam[j].username << ",";
				}
			}
			array<int, 3> scoreList = teamScores[i];
			fout << scoreList[0] << ";" << scoreList[1] << ";" << scoreList[2] << endl;
			teamNum++;
		}

		cout << "wrote to new file" << endl;
	}
