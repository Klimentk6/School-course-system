#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Submission.h"

using namespace Utils;

class Assignment
{
public:
	Assignment();
	Assignment(const char* name);
	Assignment(const Assignment& other);
	Assignment& operator=(const Assignment& other);
	~Assignment();

	void writeToBinaryFile(std::ofstream&) const;
	void readFromBinaryFile(std::ifstream&);

	const char* getName() const;
	void addSubmission(const Submission& newSubmission);
	bool hasAStudentSubmited(int studentId) const;
	void printSubmissions() const;
	Submission* getSubmissionPointer(int studentId);

private:
	void copyFrom(const Assignment& other);
	void free();

	void resize(int newCapacity);
	int calculateCapacity(int size) const;

	char* name;
	Submission* arr;
	int size;
	int capacity;
};

