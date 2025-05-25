#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"

using namespace Utils;

class Submission
{
public:
	Submission();
	Submission(int studentId, const char* content);
	Submission(const Submission& other);
	Submission& operator=(const Submission& other);
	~Submission();

	void writeToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);

	int getStudentId() const;
	void printSubmission() const;
	void setGrade(double newGrade);
	double getGrade() const;

private:
	void copyFrom(const Submission& other);
	void free();

	int studentId;
	char* content;
	double grade;
};

