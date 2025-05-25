#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Course.h"

using namespace Utils;

class CourseCollection
{
public:
    CourseCollection();
    CourseCollection(const char* fileName);
    CourseCollection(const CourseCollection& other);
    CourseCollection& operator=(const CourseCollection& other);
    ~CourseCollection();

    void writeToBinaryFile(const char* fileName) const;
    void readFromBinaryFile(const char* fileName);

    void addCourse(const Course& course);
    int getSize() const;
    Course* getCourseFromArr(int index) const;

    Course* getCoursePointer(const char* name);

private:
    void copyFrom(const CourseCollection& other);
    void free();

    void resize(int newCapacity);
    int calculateCapacity(int size) const;

    Course* arr;
    int size;
    int capacity;
};
