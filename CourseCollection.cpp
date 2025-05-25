#include "CourseCollection.h"

CourseCollection::CourseCollection()
{
    size = 0;
    capacity = MIN_COURSE_CAPACITY;
    arr = new Course[capacity];
}
CourseCollection::CourseCollection(const char* fileName)
{
    try
    {
        readFromBinaryFile(fileName);
    }
    catch (std::exception)
    {
        size = 0;
        capacity = MIN_COURSE_CAPACITY;
        arr = new Course[capacity];
    }
}
CourseCollection::CourseCollection(const CourseCollection& other)
{
    copyFrom(other);
}
CourseCollection& CourseCollection::operator=(const CourseCollection& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
CourseCollection::~CourseCollection()
{
    free();
}

void CourseCollection::copyFrom(const CourseCollection& other)
{
    size = other.size;
    capacity = other.capacity;
    arr = new Course[capacity];
    for (int i = 0; i < size; ++i)
    {
        arr[i] = other.arr[i];
    }
}
void CourseCollection::free()
{
    delete[] arr;
}

void CourseCollection::writeToBinaryFile(const char* fileName) const
{
    std::ofstream ofs(fileName, std::ios::binary);
    if (!ofs.is_open())
    {
        throw std::runtime_error("Could not open file for writing");
    }

    ofs.write((const char*)&size, sizeof(size));
    for (int i = 0; i < size; ++i)
    {
        arr[i].writeToBinaryFile(ofs);
    }

    ofs.close();
}
void CourseCollection::readFromBinaryFile(const char* fileName)
{
    std::ifstream ifs(fileName, std::ios::binary);
    if (!ifs.is_open())
    {
        throw std::runtime_error("Could not open file for reading");
    }

    free();

    ifs.read((char*)&size, sizeof(size));
    capacity = calculateCapacity(size);
    arr = new Course[capacity];

    for (int i = 0; i < size; ++i)
    {
        arr[i].readFromBinaryFile(ifs);
    }

    ifs.close();
}

void CourseCollection::resize(int newCapacity)
{
    Course* temp = new Course[newCapacity];
    for (int i = 0; i < size; ++i)
    {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    capacity = newCapacity;
}
void CourseCollection::addCourse(const Course& course)
{
    if (size == capacity)
    {
        resize(capacity * RESIZE_COEFF);
    }
    arr[size++] = course;
}

int CourseCollection::getSize() const
{
    return size;
}

Course* CourseCollection::getCourseFromArr(int index) const
{
    return &arr[index];
}

Course* CourseCollection::getCoursePointer(const char* name)
{
    for (int i = 0; i < size; i++)
    {
        if (areStringsEqual(arr[i].getName(), name))
        {
            return &arr[i];
        }
    }
    return nullptr;
}

int CourseCollection::calculateCapacity(int size) const
{
    int result = MIN_COURSE_CAPACITY;
    while (result < size)
    {
        result *= RESIZE_COEFF;
    }
    return result;
}