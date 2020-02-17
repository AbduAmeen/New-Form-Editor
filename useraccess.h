#include <fstream>
#include <iostream>
#include <string>
#include <errno.h>
#include <sstream>
#if __APPLE__
#else
#include <filesystem>
#endif
#if _WIN32
#include <windows.h>//Windows only
#else
#include <sys/stat.h>//linux only
#include <sys/types.h>//linux only
#include <unistd.h>//linux only
#include <limits.h>//linux only
#include <dirent.h>//linux only
#endif

using namespace std;

#ifndef useraccess_h
#define useraccess_h
class useraccess {
public:
    useraccess();
    ~useraccess();

    //Functions:

    //Retrieves the name of user
    //return@ - name of user
    string getname();

    //Retrieves password from the user
    //returns - password of user
    string getpass();

    //checks and creates dir for user
    int createdir();

    //Checks to see if directory already exists
    int direxist();

    //Creates password txt
    void retrieveinfo();

    //Checks for a txt file
    int checkpass();

    //Checks what type of list the user wants
    bool createlist();

    //checks what lists you have
    void openlist();

    //Checks to see if character is correct
    char checkchar(char, char);

    //converts the user answer to uppercase
    void uppercase(char&);

    //Checks to see if user wants to restart
    bool restart();

    //Check to see if an account is made
    int checkdir();

    //Finds out if user wants to create user or log in
    int askques();

    //Clears the screen
    void cls();

    //creates text file that has the password inside
    void createpass();

    //checks if user wants to make a new list or open a list already existing
    int checklist();

    //creates the list, recipes, and vit list folders for user
    int createfolders();
    //Variables:

private:
    //Variables:

    //options:
    const char Y = 'Y';
    const char N = 'N';

    //The user's name
    string name;


    //Path to public document folder
    wstring Pdocument;//windows
#if __linux__
    string Pdocumentl;//linux
	char hostname[HOST_NAME_MAX];//linux
	string hname;//linux
	string dirofuser;
#elif __APPLE__
    string Pdocumenta;
    string dirofuser;
#elif _WIN32
    wstring wname;//W string of name
    wstring dirofuser;//W directory of user
#endif
    //The user's password
    string password;

    //The type of list the user wants
    char listoption;

    //File object
    fstream file;
};
#endif /* useraccess_h */