#include "Assignment.h"

Assignment::Assignment()
{
    name = nullptr;
    size = 0;
    capacity = MIN_SUBMISSION_CAPACITY;
    arr = new Submission[capacity];
}
Assignment::Assignment(const char* name)
{
    this->name = new char[stringLength(name) + 1];
    stringCopy(this->name, name);

    size = 0;
    capacity = MIN_SUBMISSION_CAPACITY;
    arr = new Submission[capacity];
}
Assignment::Assignment(const Assignment& other)
{
    copyFrom(other);
}
Assignment& Assignment::operator=(const Assignment& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Assignment::~Assignment()
{
    free();
}

void Assignment::copyFrom(const Assignment& other)
{
    int len = stringLength(other.name);
    name = new char[len + 1];
    stringCopy(name, other.name);

    size = other.size;
    capacity = other.capacity;
    arr = new Submission[capacity];
    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }
}
void Assignment::free()
{
    delete[] name;
    delete[] arr;
}
void Assignment::resize(int newCapacity)
{
    Submission* newArr = new Submission[newCapacity];

    for (int i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
}

int Assignment::calculateCapacity(int size) const
{
    int result = MIN_SUBMISSION_CAPACITY;
    while (result < size)
    {
        result *= RESIZE_COEFF;
    }
    return result;
}
void Assignment::writeToBinaryFile(std::ofstream& ofs) const
{
    unsigned nameLen = stringLength(name);
    ofs.write((const char*)&nameLen, sizeof(nameLen));
    ofs.write(name, nameLen);

    ofs.write((const char*)&size, sizeof(size));
    for (int i = 0; i < size; i++)
    {
        arr[i].writeToBinaryFile(ofs);
    }
}
void Assignment::readFromBinaryFile(std::ifstream& ifs)
{
    free();

    unsigned nameLen = 0;
    ifs.read((char*)&nameLen, sizeof(nameLen));
    name = new char[nameLen + 1];
    ifs.read(name, nameLen);
    name[nameLen] = '\0';

    ifs.read((char*)&size, sizeof(size));
    capacity = calculateCapacity(size);
    arr = new Submission[capacity];

    for (int i = 0; i < size; i++)
    {
        arr[i].readFromBinaryFile(ifs);
    }
}

const char* Assignment::getName() const
{
    return name;
}
bool Assignment::hasAStudentSubmited(int studentId) const
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].getStudentId() == studentId)
        {
            return true;
        }
    }
    return false;
}

void Assignment::printSubmissions() const
{
    for (int i = 0; i < size; i++)
    {
        arr[i].printSubmission();
    }
}

Submission* Assignment::getSubmissionPointer(int studentId)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].getStudentId() == studentId)
        {
            return &arr[i];
        }
    }
    return nullptr;
}

void Assignment::addSubmission(const Submission& newSubmission)
{
    if (size == capacity)
    {
        resize(capacity * RESIZE_COEFF);
    }
    arr[size++] = newSubmission;
}
