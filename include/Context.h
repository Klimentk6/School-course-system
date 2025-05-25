#pragma once
#include "Utils.h"
#include "UserContainer.h"
#include "CourseCollection.h"

using namespace Utils;

struct Context
{
    UserContainer& container;
    CourseCollection& collection;
    UserType& logged;
    int& loggedId;
};