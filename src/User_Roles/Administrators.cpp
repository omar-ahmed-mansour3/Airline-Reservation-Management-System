#include"Administrators.hpp"


//**********rule of 5***************** */
Administrators::Administrators(int userid, std::string username , std::string password, 
        std::string full_name,std::string phone, std::string email):
    User(userid,username,password,full_name,phone,email){}

Administrators::Administrators(const Administrators& other):User(other)
{}

Administrators& Administrators:: operator=(const Administrators& other)
{
    if(this != &other)
    {
        User::operator=(other);
    }
    return *this;
}

Administrators:: ~Administrators(){}


//************overriden functions************* */

std::string Administrators:: getRole() const 
{
    return "Administrators";
}

void  Administrators:: showProfile() const
{
    std::cout << "--- Administrators Profile ---" << std::endl;
    User::showProfile();
}


