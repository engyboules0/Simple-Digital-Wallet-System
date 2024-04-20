#include <string>
#include <vector>
using namespace std;
class Admin {
public:
    string username;
    string password;
    static vector<Admin> admins;
    //static string loggedInUsername;
public:
    Admin(string, string);

    void registerAdmin();
    void loginAdmin();
    string getUsername() const;

    void setPassword(const string&);
    bool authenticate(string);
    void editProfile();
    void logout();
    void saveToFile() const;

private:

    void changePassword(string);
    void loadFromFile();
    bool isStrongPassword(string);
    bool hasUpperCase(string);
    bool hasLowerCase(string);
    bool hasDigit(string);
};

