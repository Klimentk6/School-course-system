#include "Course.h"    

Course::Course()
{
    name = nullptr;
    password = nullptr;

    assignmentSize = 0;
    assignmentCapacity = MIN_ASSIGNMENT_CAPACITY;
    arr = new Assignment[assignmentCapacity];

    studentsIdSize = 0;
    studentsIdCapacity = MIN_STUDENTS_CAPACITY;
    studentsId = new int[studentsIdCapacity];

    teacherId = -1;
}
Course::Course(const char* name, const char* password, int teacherId)
{
    int nameLen = stringLength(name);
    this->name = new char[nameLen + 1];
    stringCopy(this->name, name);

    int passwordLen = stringLength(password);
    this->password = new char[passwordLen + 1];
    stringCopy(this->password, password);

    this->teacherId = teacherId;

    assignmentSize = 0;
    assignmentCapacity = MIN_ASSIGNMENT_CAPACITY;
    arr = new Assignment[assignmentCapacity];

    studentsIdSize = 0;
    studentsIdCapacity = MIN_STUDENTS_CAPACITY;
    studentsId = new int[studentsIdCapacity];
}
Course::Course(const Course& other)
{
    copyFrom(other);
}
Course& Course::operator=(const Course& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Course::~Course()
{
    free();
}

void Course::copyFrom(const Course& other)
{
    unsigned nameLength = stringLength(other.name);
    name = new char[nameLength + 1];
    stringCopy(name, other.name);

    unsigned passLength = stringLength(other.password);
    password = new char[passLength + 1];
    stringCopy(password, other.password);

    assignmentSize = other.assignmentSize;
    assignmentCapacity = other.assignmentCapacity;
    arr = new Assignment[assignmentCapacity];
    for (int i = 0; i < assignmentSize; i++)
    {
        arr[i] = other.arr[i];
    }

    studentsIdSize = other.studentsIdSize;
    studentsIdCapacity = other.studentsIdCapacity;
    studentsId = new int[studentsIdCapacity];
    for (int i = 0; i < studentsIdSize; i++)
    {
        studentsId[i] = other.studentsId[i];
    }

    teacherId = other.teacherId;
}
void Course::free()
{
    delete[] name;
    delete[] password;
    delete[] arr;
    delete[] studentsId;
}

const char* Course::getName() const
{
    return name;
}
int Course::getTeacherId() const
{
    return teacherId;
}
bool Course::isPasswordCorrect(const char* checkPassword) const
{
    return areStringsEqual(checkPassword, password);
}
void Course::addStudentId(int studentId)
{
    if (studentsIdSize == studentsIdCapacity)
    {
        resizeStudentsId(studentsIdCapacity * RESIZE_COEFF);
    }

    studentsId[studentsIdSize++] = studentId;
}
bool Course::isStudentIdInCourse(int studentId) const
{
    for (int i = 0; i < studentsIdSize; i++)
    {
        if (studentId == studentsId[i])
        {
            return true;
        }
    }
    return false;
}
void Course::addAssignment(const Assignment& assignmentToAdd)
{
    if (assignmentSize == assignmentCapacity)
    {
        resizeAssignment(assignmentCapacity * RESIZE_COEFF);
    }

    arr[assignmentSize++] = assignmentToAdd;
}
Assignment* Course::getAssignmentPointer(const char* name)
{
    for (int i = 0; i < assignmentSize; i++)
    {
        if (areStringsEqual(name, arr[i].getName()))
        {
            return &arr[i];
        }
    }
    return nullptr;
}

Assignment* Course::getAssignmentFromArr(int index)
{
    return &arr[index];
}

int Course::getAssignmentSize() const
{
    return assignmentSize;
}

void Course::resizeAssignment(int newCapacity)
{
    Assignment* newArr = new Assignment[newCapacity];
    for (int i = 0; i < assignmentSize; i++)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    assignmentCapacity = newCapacity;
}
void Course::resizeStudentsId(int newCapacity)
{
    int* newArr = new int[newCapacity];
    for (int i = 0; i < studentsIdSize; i++)
    {
        newArr[i] = studentsId[i];
    }
    delete[] studentsId;
    studentsId = newArr;
    studentsIdCapacity = newCapacity;
}

int Course::calculateCapacity(int size) const
{
    int result = MIN_ASSIGNMENT_CAPACITY;
    while (result < size)
    {
        result *= RESIZE_COEFF;
    }
    return result;
}

void Course::readFromBinaryFile(std::ifstream& ifs)
{
    free();

    unsigned nameLen = 0;
    ifs.read((char*)&nameLen, sizeof(nameLen));
    name = new char[nameLen + 1];
    ifs.read(name, nameLen);
    name[nameLen] = '\0';

    unsigned passLen = 0;
    ifs.read((char*)&passLen, sizeof(passLen));
    password = new char[passLen + 1];
    ifs.read(password, passLen);
    password[passLen] = '\0';

    ifs.read((char*)&teacherId, sizeof(teacherId));

    ifs.read((char*)&assignmentSize, sizeof(assignmentSize));
    assignmentCapacity = calculateCapacity(assignmentSize);
    arr = new Assignment[assignmentCapacity];
    for (int i = 0; i < assignmentSize; i++)
    {
        arr[i].readFromBinaryFile(ifs);
    }

    ifs.read((char*)&studentsIdSize, sizeof(studentsIdSize));
    studentsIdCapacity = calculateCapacity(studentsIdSize);
    studentsId = new int[studentsIdCapacity];
    for (int i = 0; i < studentsIdSize; i++)
    {
        ifs.read((char*)&studentsId[i], sizeof(studentsId[i]));
    }
}
void Course::writeToBinaryFile(std::ofstream& ofs) const
{
    unsigned nameLen = stringLength(name);
    ofs.write((const char*)&nameLen, sizeof(nameLen));
    ofs.write(name, nameLen);

    unsigned passLen = stringLength(password);
    ofs.write((const char*)&passLen, sizeof(passLen));
    ofs.write(password, passLen);

    ofs.write((const char*)&teacherId, sizeof(teacherId));

    ofs.write((const char*)&assignmentSize, sizeof(assignmentSize));
    for (int i = 0; i < assignmentSize; i++)
    {
        arr[i].writeToBinaryFile(ofs);
    }

    ofs.write((const char*)&studentsIdSize, sizeof(studentsIdSize));
    for (int i = 0; i < studentsIdSize; i++)
    {
        ofs.write((const char*)&studentsId[i], sizeof(studentsId[i]));
    }
}


