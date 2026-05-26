#ifndef USER_H
#define USER_H
#include"string"
#include<iostream>

class User
{
protected:
    int userid; // won't be used in the project since Username is unique but easier to remmember
    std::string username;
    std::string password;
    std::string full_name;
    std::string Phone;
    std::string email;

public:
//************RULE OF 5 **************************** */
    User(int userid, std::string username , std::string password, 
        std::string full_name,std::string phone, std::string email);
    virtual ~User();
    User(const User& other);
    User& operator=(const User& other);

    //getters
    int get_userid() const;
    const std::string& get_username() const;
    const std::string& get_password() const;
    std::string getFullName() const;
    const std::string& get_Phone() const;
    const std::string& get_email() const;
    //setters
    void set_userid(int id);
    void set_username(const std::string& uname);
    void set_password(const std::string& pass);
    void set_full_name(const std::string& fname);
    void set_Phone(const std::string& phone_num);
    void set_email(const std::string& mail);
    
//************ Pure Virtual functions **************************** */

    virtual std::string getRole() const = 0;


//************Virtual functions **************************** */
    
    virtual void showProfile() const;

};


#endif