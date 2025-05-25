#include <iostream>

#include "Utils.h" 
#include "UserContainer.h"
#include "CourseCollection.h"
#include "Command.h"     
#include "CommandFactory.h" 

using namespace Utils;
          
int main() 
{
    UserContainer container(USERS_FILE_NAME);
    CourseCollection collection(COURSES_FILE_NAME);
    UserType logged = UserType::None;
    int loggedId = -1;
    Context context{ container, collection, logged, loggedId };
    char buffer[MAX_BUFFER_SIZE];
    while (true) 
    {
        std::cout << "> ";
        std::cin.getline(buffer, MAX_BUFFER_SIZE);
        if (isValidExitInput(buffer)) break;
        Command* command = createCommand(buffer, context);
        if (command) 
        {
            command->execute();
            delete command;
        }
    }
    container.writeToBinaryFile(USERS_FILE_NAME);
    collection.writeToBinaryFile(COURSES_FILE_NAME);
    return 0;
}