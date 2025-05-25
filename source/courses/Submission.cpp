#include "Submission.h"

Submission::Submission()
{
    studentId = -1;
    content = nullptr;
    grade = -1;
}
Submission::Submission(int studentId, const char* content)
{
    this->studentId = studentId;

    this->content = new char[stringLength(content) + 1];
    stringCopy(this->content, content);

    grade = -1;
}
Submission::Submission(const Submission& other)
{
    copyFrom(other);
}
Submission& Submission::operator=(const Submission& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Submission::~Submission()
{
    free();
}

void Submission::copyFrom(const Submission& other)
{
    studentId = other.studentId;

    content = new char[stringLength(other.content) + 1];
    stringCopy(content, other.content);

    grade = other.grade;
}
void Submission::free()
{
    delete[] content;
}

void Submission::writeToBinaryFile(std::ofstream& ofs) const
{
    ofs.write((const char*)&studentId, sizeof(studentId));

    unsigned contentLen = stringLength(content);
    ofs.write((const char*)&contentLen, sizeof(contentLen));
    ofs.write(content, contentLen);

    ofs.write((const char*)&grade, sizeof(grade));
}
void Submission::readFromBinaryFile(std::ifstream& ifs)
{
    free();

    ifs.read((char*)&studentId, sizeof(studentId));

    unsigned contentLen = 0;
    ifs.read((char*)&contentLen, sizeof(contentLen));
    content = new char[contentLen + 1];
    ifs.read(content, contentLen);
    content[contentLen] = '\0';

    ifs.read((char*)&grade, sizeof(grade));
}

int Submission::getStudentId() const
{
    return studentId;
}
void Submission::printSubmission() const
{
    std::cout << "Id " << studentId << ": " << content << std::endl;
}
void Submission::setGrade(double newGrade)
{
    grade = newGrade;
}
double Submission::getGrade() const
{
    return grade;
}
