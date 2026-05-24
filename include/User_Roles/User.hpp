#ifndef USER_H
#define USER_H
#include"string"
#include<iostream>

class User
{
protected:
    int userid;
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


    std::string getFullName() const;
//************ Pure Virtual functions **************************** */
    virtual void displayWindow() const =0;
    virtual std::string getRole() const = 0;


//************Virtual functions **************************** */
    
    virtual void showProfile() const;
    virtual void searchFlights();
    virtual void manageBooking();


};


#endif