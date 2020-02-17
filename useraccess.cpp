//#include "pch.h"//Disable in Mac/Linux
#include "useraccess.h"

useraccess::useraccess() {
    name = "";
    listoption = '\0';
    password = "";

#if _WIN32
    Pdocument = L"C:\\Users\\Public\\Documents\\";
    dirofuser = L"";
    wname = L"";
#elif __linux__
    dirofuser = "";
    Pdocumentl = getenv("HOME");
	Pdocumentl += "/";
#elif __APPLE__
    Pdocumenta = "~//Documents//";
    dirofuser = "";
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Functions used in the main
int useraccess::askques() {
    char S = 'S';
    char L = 'L';
    cout << "Press \"S\" To sign up or press \"L\" to login\n";
#if __linux__
    const char *homeDir = getenv("HOME");
	Pdocumentl += (string)hostname + "Documents";
#elif __APPLE__
    const char *homeDir = getenv("HOME");
    Pdocumenta = (string)homeDir + "/Documents";
#endif
    do {
        char c = checkchar(S, L);

        if (c == S) {
            return 1;
        }
        else if (c == L) {
            return 2;
        }
        else {
            cerr << "Error";
            return 4;
        }
    } while (S == 'S');

    return 3;
}

int useraccess::createdir() {
    bool wer = false;
    int error = errno;
    char tre = '\0';
    char ytp = '\0';
    int vre = 1;
    int r = 1;
#if _WIN32
    wstring s = Pdocument + wname;
#elif __APPLE__
    string s = Pdocumenta + "/" + name;
#elif __linux__
    string s = Pdocumentl  + "/" + name;
#endif

    int terry = 0;
    int gfe = 0;
    string qws = "";
    bool rew = true;

    terry = checkdir();
    gfe = checkpass();

    do {

        if ((terry == 1) && (gfe == 1)) {
            cerr << "You already have a user. We will just log you in instead";
            #if _WIN32
            dirofuser = Pdocument + wname;
            #elif __linux__
            dirofuser = Pdocumentl + "/" + name + "/";
            #else
            dirofuser = Pdocumenta + "/" + name + "/";
            #endif
            return 1;
        }

        else if ((terry == 1) && (gfe == 2)) {
            cout << "You messed with the stuff in your folder didn't you?";
            return 0;
        }

        else if ((terry == 1) && (gfe == 3)) {
            do {
                cls();
                cout << "Your password is incorrect. Please enter it again.\n";
                getpass();
                int ret = checkpass();

                if (ret == 1) {
                    return 1;
                }
                else if (ret == 2) {
                    return 0;
                }
                else {
                    continue;
                }
            } while (rew == true);
        }
        else if (terry == 2) {


            if (vre == 1) {
                do {
                    cls();
                    cout << "Are you sure you want to use this name for your account: " << name << " [Y/N]\n";
                    ytp = checkchar(Y, N);
                    break;
                } while (vre == 1);
            }

            if (ytp == Y) {
                vre = 2;
                if (r == 1) {
                    do {
                        cls();
                        cout << "Do you want to use this password for your account: " << password << " [Y/N]\n";
                        tre = checkchar(Y, N);
                        break;
                    } while (r == 1);
                }

                if (tre == Y) {
                    #ifdef _WIN32
                    if (_wmkdir(s.c_str()) == 0) {
                    #elif __linux__
                    string er = Pdocumentl + "/" + name;
					if (mkdir(er.c_str(), 0777) == 0) {
                    #elif __APPLE__
                    string t = Pdocumenta + "/" + name;
                    if (mkdir(t.c_str(), 0777) == 0) {
                    #endif
                        r = 2;
                        dirofuser = s;
                        createfolders();
                        createpass();
                        #if _WIN32
                        dirofuser = Pdocument + wname;
                        #elif __linux__
                        dirofuser = Pdocumentl + "/" + name + "/";
                        #else
                        dirofuser = Pdocumenta + "/" + name + "/";
                        #endif
                        cerr << "User successfully created";
                        return 1;

                    }
                    else {
                        cerr << "Error in pathname";
                        return 0;
                    }
                }
                else {
                    getpass();
                }
            }
            else {
                getname();
                terry = checkdir();
                gfe = checkpass();
            }
        }
    } while (wer == false);

    return 0;
}

int useraccess::direxist() {
    char s = Y;
    bool der = false;
    int welp = checkdir();
    int help = checkpass();

    if ((welp == 1) && (help == 1)) {
        #if _WIN32
        dirofuser = Pdocument + wname;
        #elif __linux__
        dirofuser = Pdocumentl + "/" + name + "/";
        #else
        dirofuser = Pdocumenta + "/" + name + "/";
        #endif
        cout << "Logged in";
        return 1;
    }
    else {
        while (s == Y) {
            for (int i = 0; i < 2; i++) {
                cls();
                cout << "Wrong username and/or password\n";
                retrieveinfo();
                welp = checkdir();
                help = checkpass();

                if ((welp == 1) && (help == 1)) {
#if _WIN32
                    dirofuser = Pdocument + wname;
#elif __linux__
                    dirofuser = Pdocumentl + "/" + name + "/";
#else
                    dirofuser = Pdocumenta + "/" + name + "/";
#endif
                    cout << "Logged in";
                    return 1;
                }
                else {

                    continue;
                }
            }
            cls();
            cout << "Are you sure you have an account?  [Y/N]\n";
            s = checkchar(Y, N);

            if (s == Y) {
                continue;
            }
            else {
                cls();
                cout << "We will sign you up instead\n";
                return 2;
            }
        }
    }

    return 0;
}

void useraccess::retrieveinfo() {
    getname();
    getpass();
    return;
}

int useraccess::checkpass() {
    char p = 'y';

    do {
        string pass = "";
#if _WIN32
        wstring s = Pdocument + wname + L"\\password.txt";

		ifstream input;
		input.open(s);
#elif __linux__
        string s = Pdocumentl + "/" + name + "/password.txt";

		ifstream input;
		input.open(s);
#elif __APPLE__
        string s = Pdocumenta + "/" + name + "/password.txt";

        ifstream input;
        input.open(s);
#endif
        if (input.is_open() == true) {

            for (unsigned int curLine = 0; getline(input, pass); curLine++) {
                if (pass.find(password) != string::npos) {
                    return 1;
                }
            }
        }
        else {
            return 2;
        }

        if (pass.find(password) == string::npos) {
            input.clear();
            input.seekg(0, ios::beg);
            input.close();
            return 3;
        }
    } while (p == Y);

    return 3;
}

bool useraccess::createlist() {
    char a = 'x';
    do {
        cls();
        cout << "What type of list would you like to make?\n\n";
        cout << "\"L\" for List | \"V\" for Vitamin list | \"R\" for Recipe\n";
        cin >> listoption;
        getchar();
        cout << "Are you sure you want to choose this?  [Y/N]\n";
        a = checkchar(Y, N);

        if (a == Y) {
            return true;
        }
        else if (a == N) {
            cls();
            continue;
        }
    } while (a != 'y');

    return false;
}

int useraccess::checklist() {
    cls();
    openlist();

    cout << "\nDo you want to open a list [O] or create a new list [C]?\n";
    char cx = checkchar('o', 'c');

    if (cx == 'O') {
        openlist();
    }
    else {
        createlist();
    }
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Functions that are not used in main
void useraccess::openlist() {
#if _WIN32
    wstring s = dirofuser + L"\\Lists";
	int count = 0;
	string str, str2;
	stringstream buffer;

	for (auto& i : experimental::filesystem::directory_iterator(s)) {
		count++;
	}
	
	cout << "You have " << count << " Lists\n";

	for (auto& i : experimental::filesystem::directory_iterator(s)) {
		buffer << i;
		str = buffer.str();

		str2 = str.erase(0, str.rfind("\\") + 1);
		str = str2.erase(str2.rfind("."), str2.back());
		cout << str << endl;
	}

	
	//Recipes
	s = dirofuser + L"\\Recipes";
	count = 0;

	for (auto& i : experimental::filesystem::directory_iterator(s)) {
		count++;
	}
	
	cout << "\nYou have " << count << " Recipes\n";

	for (auto& i : experimental::filesystem::directory_iterator(s)) {
		buffer << i;
		str = buffer.str();

		str2 = str.erase(0, str.rfind("\\") + 1);
		str = str2.erase(str2.rfind("."), str2.back());
		cout << str << endl;
	}

	
	//Vitamin lists
	s = dirofuser + L"\\Vitamin Lists";
	count = 0;
	
	for (auto& i : experimental::filesystem::directory_iterator(s)) {
		count++;
	}
	
	cout << "\nYou have " << count << " Vitamin Lists\n";
	
	for (auto& i : experimental::filesystem::directory_iterator(s)) {
		buffer << i;
		str = buffer.str();

		str2 = str.erase(0, str.rfind("\\") + 1);
		str = str2.erase(str2.rfind("."), str2.back());
		cout << str << endl;
	}
	return;
#elif __linux__
    string s = dirofuser + "/Lists";
    int count = 0;
    string str, str2;
    stringstream buffer;

    for (auto& i : experimental::filesystem::directory_iterator(s)) {
        count++;
    }

    cout << "You have " << count << " Lists\n";

    for (auto& i : experimental::filesystem::directory_iterator(s)) {
        buffer << i;
        str = buffer.str();

        str2 = str.erase(0, str.rfind("/") + 1);
        str = str2.erase(str2.rfind("."), str2.back());
        cout << str << endl;
    }


    //Recipes
    s = dirofuser + "/Recipes";
    count = 0;

    for (auto& i : experimental::filesystem::directory_iterator(s)) {
        count++;
    }

    cout << "\nYou have " << count << " Recipes\n";

    for (auto& i : experimental::filesystem::directory_iterator(s)) {
        buffer << i;
        str = buffer.str();

        str2 = str.erase(0, str.rfind("/") + 1);
        str = str2.erase(str2.rfind("."), str2.back());
        cout << str << endl;
    }


    //Vitamin lists
    s = dirofuser + "/Vitamin Lists";
    count = 0;

    for (auto& i : experimental::filesystem::directory_iterator(s)) {
        count++;
    }

    cout << "\nYou have " << count << " Vitamin Lists\n";

    for (auto& i : experimental::filesystem::directory_iterator(s)) {
        buffer << i;
        str = buffer.str();

        str2 = str.erase(0, str.rfind("/") + 1);
        str = str2.erase(str2.rfind("."), str2.back());
        cout << str << endl;
    }
    return;
#elif __APPLE__
    return;
#endif
}

int useraccess::checkdir() {
#if _WIN32
    wstring s = Pdocument + wname;

	DWORD dwAttrib = GetFileAttributes(s.c_str());

	if (dwAttrib != INVALID_FILE_ATTRIBUTES) {
		return 1;
	}
	else {
		return 2;
	}

#elif __linux__
    string sepp = Pdocumentl + "/" + name;

	if (opendir(sepp.c_str()) != NULL) {
		return 1;
	}

	else {}
		return 2;
	}
#elif __APPLE__
    string peep = Pdocumenta + "/" + name;

    if (opendir(peep.c_str()) != NULL) {
        return 1;
    }
    else {
        return 2;
    }

#endif
}

string useraccess::getpass() {
    cout << "Enter your password: ";
    cin >> password;
    getchar();
    return password;
}

string useraccess::getname() {
    cout << "Enter your name: ";
    getline(cin, name);
#if _WIN32
    wname.assign(name.begin(), name.end());
#endif
    return name;
}

bool useraccess::restart() {
    char x = Y;

    do {
        cls();
        cout << "Would you like to restart? [Y/N]";
        x = checkchar(Y, N);

        if (x == Y) {
            cout << "Are you sure? [Y/N]";
            x = checkchar(Y, N);

            if (x == Y) {
                return true;
            }
            else {
                cls();
                continue;
            }
        }
        else {
            return false;
        }
    } while (x != 'n');
    return false;
}

int useraccess::createfolders() {
    int error = 0;

#if _WIN32
    wstring s = dirofuser + L"\\Vitamin Lists";

	if (_wmkdir(s.c_str()) == 0) {
	}
	else {
		error = errno;
		return 0;
	}

	s = dirofuser + L"\\Lists";

	if (_wmkdir(s.c_str()) == 0) {
	}
	else {
		error = errno;
		return 0;
	}

	s = dirofuser + L"\\Recipes";

	if (_wmkdir(s.c_str()) == 0) {
	}
	else {
		error = errno;
		return 0;
	}
	return 1;
#else
    string s = dirofuser + "/Vitamin Lists";

    if (mkdir(s.c_str(), 0777) == 0) {}
    else {
        error = errno;
        return 0;
    }
    s = dirofuser + "/Lists";

    if (mkdir(s.c_str(), 0777) == 0) {}
    else {
        error = errno;
        return 0;
    }

    s = dirofuser + "/Recipes";

    if (mkdir(s.c_str(), 0777) == 0) {}
    else {
        error = errno;
        return 0;
    }
    return 1;
#endif
}

char useraccess::checkchar(char a, char b) {
    char x;

    do {
        cin >> x;
        getchar();
        uppercase(x);
        uppercase(b);
        uppercase(a);

        if (x == a) {
            return a;
        }
        else if (x == b) {
            return b;
        }
        else {
            cout << "Enter a vaild choice\n";
            continue;
        }
    } while ((x != a) || (x != b));

    return 'a';
}

void useraccess::uppercase(char& x) {
    x = toupper(x);
    return;
}

void useraccess::cls() {
#ifdef _WIN32
    //linux code goes here
	system("cls");
#else
    // windows code goes here
    system("clear");

#endif
    return;
}

void useraccess::createpass() {
#if _WIN32
    wstring s = dirofuser + L"\\password.txt";

	ofstream pw(s);
#elif __linux__
    string s = Pdocumentl + "/" + name + "/password.txt";

	ofstream pw(s);
#elif __APPLE__
    string s = Pdocumenta + "/" + name + "/password.txt";

    ofstream pw(s);
#endif
    pw << password;
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

useraccess::~useraccess() {
    file.close();
}