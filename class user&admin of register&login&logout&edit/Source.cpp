#include <iostream>
#include "User.h"
#include "Admin.h"

using namespace std;

void saveData(User& user, Admin& admin) {
    user.saveToFile();
    admin.saveToFile();
}

int main() {
    cout << "Welcome to CyberCash Carry Wallet !" << endl;

    
    User user("", "");
    Admin admin("", "");

    while (true) {
        cout << "1. Register\n2. Login\n3. Exit" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Register as:\n1. User\n2. Admin" << endl;
            int userType;
            cin >> userType;

            if (userType == 1) {
                string newUsername, newPassword;
                cout << "Enter username : ";
                cin >> newUsername;
                while (newUsername.length() < 10) {
                    cout << "Username must be at least 10 characters long." << endl;
                    cout << "Enter username : ";
                    cin >> newUsername;
                }

                bool isUnique = true;
                for (const auto& registeredUser : User::users) {
                    if (registeredUser.getUsername() == newUsername) {
                        isUnique = false;
                        break;
                    }
                }

                if (!isUnique) {
                    cout << "Username already exists. Please choose a different one." << endl;
                    continue; 
                }

                cout << "Enter password: ";
                cin >> newPassword;
                while (newPassword.length() < 8) {
                    cout << "Password must be at least 8 characters long." << endl;
                    cout << "Enter password: ";
                    cin >> newPassword;
                }

                User newUser(newUsername, newPassword);
                user = newUser;
                user.saveToFile();
                cout << "User registration successful." << endl;
            }
            else if (userType == 2) {
                string newUsername, newPassword;
                cout << "Enter admin username: ";
                cin >> newUsername;

                bool isUnique = true;
                for (const auto& registeredAdmin : Admin::admins) {
                    if (registeredAdmin.getUsername() == newUsername) {
                        isUnique = false;
                        break;
                    }
                }

                if (!isUnique) {
                    cout << "Username already exists. Please choose a different one." << endl;
                    continue; 
                }

                cout << "Enter admin password: ";
                cin >> newPassword;

                Admin newAdmin(newUsername, newPassword);
                admin = newAdmin;
                admin.saveToFile();
                cout << "Admin registration successful." << endl;
            }
            else {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 2: {
            cout << "Login as:\n1. User\n2. Admin" << endl;
            int userType;
            cin >> userType;

            if (userType == 1) {
                string inputUsername, inputPassword;
                cout << "Enter username: ";
                cin >> inputUsername;
                cout << "Enter password: ";
                cin >> inputPassword;

                bool loggedIn = false;
                for (auto& registeredUser : User::users) {
                    if (registeredUser.getUsername() == inputUsername && registeredUser.authenticate(inputPassword)) {
                        loggedIn = true;
                        cout << "Login successful. Welcome, " << registeredUser.getUsername() << endl;
                     
                        cout << "1. Edit Profile\n2. Logout" << endl;
                        int userOption;
                        cin >> userOption;

                        if (userOption == 1) {
                            string newPassword;
                            cout << "Enter new password: ";
                            cin >> newPassword;

                            if (newPassword.length() < 8) {
                                cout << "Password must be at least 8 characters long. Profile not updated." << endl;
                            }
                            else {
                                registeredUser.setPassword(newPassword);
                                user.saveToFile();
                                cout << "Password updated successfully." << endl;
                            }
                        }
                        else if (userOption == 2) {
                            cout << "Logging out..." << endl;
                        }
                        else {
                            cout << "Invalid option." << endl;
                        }
                        break; 
                    }
                }

                if (!loggedIn) {
                    cout << "Invalid username or password." << endl;
                }
            }
            else if (userType == 2) {
                string inputUsername, inputPassword;
                cout << "Enter admin username: ";
                cin >> inputUsername;
                cout << "Enter admin password: ";
                cin >> inputPassword;

                bool loggedIn = false;
                for (auto& registeredAdmin : Admin::admins) {
                    if (registeredAdmin.getUsername() == inputUsername && registeredAdmin.authenticate(inputPassword)) {
                        loggedIn = true;
                        cout << "Admin login successful. Welcome, " << registeredAdmin.getUsername() << endl;
                        
                        cout << "1. Edit Profile\n2. Logout" << endl;
                        int adminOption;
                        cin >> adminOption;

                        if (adminOption == 1) {
                            string newPassword;
                            cout << "Enter new password: ";
                            cin >> newPassword;

                            if (newPassword.length() < 8) {
                                cout << "Password must be at least 8 characters long. Profile not updated." << endl;
                            }
                            else {
                                registeredAdmin.setPassword(newPassword);
                                admin.saveToFile();
                                cout << "Password updated successfully." << endl;
                            }
                        }
                        else if (adminOption == 2) {
                            cout << "Admin logging out..." << endl;
                        }
                        else {
                            cout << "Invalid option." << endl;
                        }
                        break;
                    }
                }

                if (!loggedIn) {
                    cout << "Invalid admin username or password." << endl;
                }
            }
            else {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 3:
            
            saveData(user, admin);
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
