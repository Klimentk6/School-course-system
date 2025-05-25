#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Assignment.h"

using namespace Utils;

class Course
{
public:
	Course();
	Course(const char* name, const char* password, int teacherId);
	Course(const Course& other);
	Course& operator=(const Course& other);
	~Course();

	void writeToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);

	const char* getName() const;
	int getTeacherId() const;
	bool isPasswordCorrect(const char* checkPassword) const;
	void addStudentId(int studentId);
	bool isStudentIdInCourse(int studentId) const;
	void addAssignment(const Assignment& assignmentToAdd);
	Assignment* getAssignmentPointer(const char* name);
	Assignment* getAssignmentFromArr(int index);
	int getAssignmentSize() const;

private:
	void copyFrom(const Course& other);
	void free();

	int calculateCapacity(int size) const;
	void resizeAssignment(int newCapacity);
	void resizeStudentsId(int newCapacity);

	char* name;
	char* password;
	Assignment* arr;
	int assignmentSize;
	int assignmentCapacity;
	int* studentsId;
	int studentsIdSize;
	int studentsIdCapacity;
	int teacherId;
};


