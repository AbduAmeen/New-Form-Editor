//Make sure you copy into file
//Don't try to use the file
//#include "pch.h"//Remove if in windows
#if _WIN32
#else
#include <dirent.h>
#endif
#include "useraccess.h"
//#include "vitamin.h"
#include <iostream>
using namespace std;

int main() {
    bool x = false;
    bool y = 1;
    char extra;

    do {
        useraccess *user = new useraccess;
        int cds = user->askques();

        while (y != 0) {
            user->retrieveinfo();
            if (cds == 1) {
                int fort = user->createdir();

                if (fort == 1) {
                    extra = user->checklist();

                }
                else {
                    cerr << "Error";
                    break;
                }
            }
            else if (cds == 2) {
                int xyz = user->direxist();

                if (xyz == 1) {
                    user->checklist();
                }
                else if (xyz == 2) {
                    cds = 1;
                }
            }
        }

        delete user;

    } while (!x);


    return 0;
}