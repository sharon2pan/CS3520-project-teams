#include "student.hpp"
#include "score.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <string>
using namespace std;

extern vector<Student> createRoster(vector<vector<string>> &fileRows);
Score getScore(string scoreString);
vector<array<int, 3>> addScores(vector<vector<Student>> &allTeams);
void print(vector<Student> &neam, int CPPSum, int GDBSum, int algoSum, int acc);
bool isInNotWork(Student &thisStudent, Student &otherStudent);
string toLowercase(string &str);

