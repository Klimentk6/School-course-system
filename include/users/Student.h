#pragma once
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "User.h"

using namespace Utils;

class Student : public User 
{
public:
    Student() = default; 
    Student(const char* name, const char* surname, int id, const Mail& inbox, const char* password);
    Student(const char* name, const char* surname, int id, const char* password);
    Student(const Student& other) = default;
    Student& operator=(const Student& other) = default;
    ~Student() = default;

    UserType getUserType() const override;
    User* clone() const override;
    void writeToBinaryFile(std::ofstream& ofs) const override;
    void printUser() const override;
};
