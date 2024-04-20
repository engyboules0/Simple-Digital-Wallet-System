#include "User.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
static vector<User> users;

User::User(string username, string password)
    : username(username), password(password), balance(0.0) {}

void User::registerUser() {
    string newUsername, newPassword;
    cout << "Enter username : ";
    cin >> newUsername;
    if (newUsername.length() < 10) {
        cout << "Username must be at least 10 characters long." << endl;
        return;
    }

    bool isUnique = true;
    for (const auto& user : users) {
        if (user.username == newUsername) {
            isUnique = false;
            cout << "Username already exists. Please choose a different one." << endl;
            return;
        }
    }

    cout << "Enter password: ";
    cin >> newPassword;
    if (!isStrongPassword(newPassword)) {
        cout << "Password is not strong enough. Please try again." << endl;
        return;
    }

    User newUser(newUsername, newPassword);
    users.push_back(newUser);
    saveToFile();
    cout << "User registration successful." << endl;
}

void User::loginUser() {
    string inputUsername, inputPassword;
    cout << "Enter username: ";
    cin >> inputUsername;
    cout << "Enter password: ";
    cin >> inputPassword;

    for (auto& user : users) {
        if (user.username == inputUsername && user.password == inputPassword) {
            cout << "Login successful. Welcome, " << user.username << endl;
            return;
        }
    }

    cout << "Invalid username or password." << endl;
}

void User::editProfile() {
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

void User::logout() {
    cout << "Logging out..." << endl;
}

bool User::authenticate(string password) {
    return this->password == password;
}
string User::getUsername() const {
    return username;
}

void User::setPassword(const string& newPassword) {
    password = newPassword;
}

void User::changePassword(string newPassword) {
    password = newPassword;
}

void User::saveToFile() const {
    ofstream file("userData.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    file << username << " " << password << " " << balance << endl;
}

void User::loadFromFile() {
    ifstream file("userData.txt");
    if (!file.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    string username, password;
    double balance;
    while (file >> username >> password >> balance) {
        User newUser(username, password);
        newUser.balance = balance;
        users.push_back(newUser);
    }
    file.close();
}

bool User::isStrongPassword(string password) {
    return password.length() >= 8 &&
        hasUpperCase(password) &&
        hasLowerCase(password) &&
        hasDigit(password);
}

bool User::hasUpperCase(string str) {
    for (char c : str) {
        if (isupper(c)) {
            return true;
        }
    }
    return false;
}

bool User::hasLowerCase(string str) {
    for (char c : str) {
        if (islower(c)) {
            return true;
        }
    }
    return false;
}

bool User::hasDigit(string str) {
    for (char c : str) {
        if (isdigit(c)) {
            return true;
        }
    }
    return false;
}
