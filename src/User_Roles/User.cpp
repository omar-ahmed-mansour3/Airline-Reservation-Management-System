#include"User.hpp"

//************RULE OF 5 **************************** */
User:: User(int userid, std::string username , std::string password, 
    std::string full_name, std::string phone, std::string email):
    userid(userid) , username(username), password(password), full_name(full_name),Phone(phone),email(email) {}

User::~User(){} // no dynamic allocation to free

User::User(const User& other) 
{
    
    this->userid = other.userid;
    this->username = other.username;
    this->password = other.password;
    this->full_name = other.full_name;
    this->Phone = other.Phone; 
    this->email = other.email;
}

User& User::operator=(const User& other)
{
    if(this != &other)
    {
    this->userid = other.userid;
    this->username = other.username;
    this->password = other.password;
    this->full_name = other.full_name;
    this->Phone = other.Phone; // Added
    this->email = other.email;
    }

    return *this;
}

std::string User::getFullName() const 
{
    return this->full_name; 
}


//************Virtual functions*****************************/

void User:: showProfile() const
{
    std::cout<<"username: " << this->username <<std::endl;
    std::cout<<"full name: " << this->full_name<<std::endl;
    std::cout<<"Phone: " << this->Phone<<std::endl;
    std::cout<<"email: " << this->email<<std::endl;
}
