#include "Admin.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<Admin> Admin::admins;
static string loggedInUsername;
Admin::Admin(string username, string password)
    : username(username), password(password) {}

void Admin::registerAdmin() {
    string newUsername, newPassword;
    cout << "Enter admin username: ";
    cin >> newUsername;
    if (newUsername.length() < 10) {
        cout << "Username must be at least 10 characters long." << endl;
        return;
    }

    bool isUnique = true;
    for (const auto& admin : admins) {
        if (admin.username == newUsername) {
            isUnique = false;
            cout << "Username already exists. Please choose a different one." << endl;
            return;
        }
    }

    cout << "Enter admin password: ";
    cin >> newPassword;
    if (!isStrongPassword(newPassword)) {
        cout << "Password is not strong enough. Please try again." << endl;
        return;
    }


    Admin newAdmin(newUsername, newPassword);
    admins.push_back(newAdmin);
    saveToFile();
    cout << "Admin registration successful." << endl;
}

void Admin::loginAdmin() {
    string inputUsername, inputPassword;
    cout << "Enter admin username: ";
    cin >> inputUsername;
    cout << "Enter admin password: ";
    cin >> inputPassword;

    for (const auto& admin : admins) {
        if (admin.username == inputUsername && admin.password == inputPassword) {
            cout << "Admin login successful. Welcome, " << admin.username << endl;
            return;
        }
    }

    cout << "Invalid admin username or password." << endl;
}
//bool Admin::isRegistered() {
//    return !admins.empty();
//}
//
//bool Admin::isLoggedIn() {
//    return !loggedInUsername.empty();
//}


void Admin::editProfile() {
    string newPassword;
    cout << "Enter new password: ";
    cin >> newPassword;

    if (isStrongPassword(newPassword)) {
        password = newPassword;
        saveToFile();
        cout << "Password updated successfully." << endl;
    }
    else {
        cout << "Password is not strong enough. Profile not updated." << endl;
    }
}

void Admin::logout() {
    cout << "Admin logging out..." << endl;
}
string Admin::getUsername() const {
    return username;
}

void Admin::setPassword(const string& newPassword) {
    password = newPassword;
}
bool Admin::authenticate(string password) {
    return this->password == password;
}

void Admin::changePassword(string newPassword) {
    password = newPassword;
}

void Admin::saveToFile() const {
    ofstream file("adminData.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    file << username << " " << password << endl;
}

void Admin::loadFromFile() {
    ifstream file("adminData.txt");
    if (!file.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    string username, password;
    while (file >> username >> password) {
        Admin newAdmin(username, password);
        admins.push_back(newAdmin);
    }
    file.close();
}

bool Admin::isStrongPassword(string password) {
    return password.length() >= 8 &&
        hasUpperCase(password) &&
        hasLowerCase(password) &&
        hasDigit(password);
}

bool Admin::hasUpperCase(string str) {
    for (char c : str) {
        if (isupper(c)) {
            return true;
        }
    }
    return false;
}

bool Admin::hasLowerCase(string str) {
    for (char c : str) {
        if (islower(c)) {
            return true;
        }
    }
    return false;
}

bool Admin::hasDigit(string str) {
    for (char c : str) {
        if (isdigit(c)) {
            return true;
        }
    }
    return false;
}
//#include "Admin.h"
//#include <iostream>
//#include <fstream>
//#include <vector>
//
//using namespace std;
//
//vector<Admin> Admin::admins;
//static string loggedInUsername;
//Admin::Admin(string username, string password)
//    : username(username), password(password) {}
//
//void Admin::registerAdmin() {
//    string newUsername, newPassword;
//    cout << "Enter admin username: ";
//    cin >> newUsername;
//    if (newUsername.length() < 10) {
//        cout << "Username must be at least 10 characters long." << endl;
//        return;
//    }
//
//    bool isUnique = true;
//    for (const auto& admin : admins) {
//        if (admin.username == newUsername) {
//            isUnique = false;
//            cout << "Username already exists. Please choose a different one." << endl;
//            return;
//        }
//    }
//
//    cout << "Enter admin password: ";
//    cin >> newPassword;
//    if (!isStrongPassword(newPassword)) {
//        cout << "Password is not strong enough. Please try again." << endl;
//        return;
//    }
//
//
//    Admin newAdmin(newUsername, newPassword);
//    admins.push_back(newAdmin);
//    saveToFile();
//    cout << "Admin registration successful." << endl;
//}
//
//void Admin::loginAdmin() {
//    string inputUsername, inputPassword;
//    cout << "Enter admin username: ";
//    cin >> inputUsername;
//    cout << "Enter admin password: ";
//    cin >> inputPassword;
//
//    for (const auto& admin : admins) {
//        if (admin.username == inputUsername && admin.password == inputPassword) {
//            cout << "Admin login successful. Welcome, " << admin.username << endl;
//            return;
//        }
//    }
//
//    cout << "Invalid admin username or password." << endl;
//}
////bool Admin::isRegistered() {
////    return !admins.empty();
////}
////
////bool Admin::isLoggedIn() {
////    return !loggedInUsername.empty();
////}


//void Admin::editProfile() {
//    string newPassword;
//    cout << "Enter new password: ";
//    cin >> newPassword;
//
//    if (isStrongPassword(newPassword)) {
//        password = newPassword;
//        saveToFile();
//        cout << "Password updated successfully." << endl;
//    }
//    else {
//        cout << "Password is not strong enough. Profile not updated." << endl;
//    }
//}
//
//void Admin::logout() {
//    cout << "Admin logging out..." << endl;
//}
//
//bool Admin::authenticate(string password) {
//    return this->password == password;
//}
//
//void Admin::changePassword(string newPassword) {
//    password = newPassword;
//}
//
//void Admin::saveToFile() const {
//    ofstream file("adminData.txt", ios::app);
//    if (!file.is_open()) {
//        cout << "Error opening file for writing." << endl;
//        return;
//    }
//    file << username << " " << password << endl;
//}
//
//void Admin::loadFromFile() {
//    ifstream file("adminData.txt");
//    if (!file.is_open()) {
//        cout << "Error opening file for reading." << endl;
//        return;
//    }
//
//    string username, password;
//    while (file >> username >> password) {
//        Admin newAdmin(username, password);
//        admins.push_back(newAdmin);
//    }
//    file.close();
//}
//
//bool Admin::isStrongPassword(string password) {
//    return password.length() >= 8 &&
//        hasUpperCase(password) &&
//        hasLowerCase(password) &&
//        hasDigit(password);
//}
//
//bool Admin::hasUpperCase(string str) {
//    for (char c : str) {
//        if (isupper(c)) {
//            return true;
//        }
//    }
//    return false;
//}
//
//bool Admin::hasLowerCase(string str) {
//    for (char c : str) {
//        if (islower(c)) {
//            return true;
//        }
//    }
//    return false;
//}
//
//bool Admin::hasDigit(string str) {
//    for (char c : str) {
//        if (isdigit(c)) {
//            return true;
//        }
//    }
//    return false;
//}
