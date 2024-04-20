#include <string>
#include <vector>
using namespace std;

class User {
private:
    string username;
    string password;
    double balance;
    
public:
    User(string, string );
    static vector<User> users;
    void registerUser();
    void loginUser();

    string getUsername() const;

    void setPassword(const string&);
    bool authenticate(string);
    void editProfile();
    void logout();
    void saveToFile() const;
    void loadFromFile();


private:
    bool hasUpperCase(string);
    bool hasLowerCase(string);
    bool hasDigit(string );
    void changePassword(string);
    bool isStrongPassword(string );
};

