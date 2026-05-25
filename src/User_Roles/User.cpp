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

//getters
std::string User::getFullName() const 
{
    return this->full_name; 
}

int User::get_userid() const 
{
    return userid;
}

const std::string& User::get_username() const 
{
    return username;
}

const std::string& User::get_password() const 
{
    return password;
}

const std::string& User::get_Phone() const 
{
    return Phone;
}

const std::string& User::get_email() const 
{
    return email;
}

//setters 
void User::set_userid(int id) 
{
    userid = id;
}

void User::set_username(const std::string& uname) 
{
    username = uname;
}

void User::set_password(const std::string& pass) 
{
    password = pass;
}

void User::set_full_name(const std::string& fname) 
{
    full_name = fname;
}

void User::set_Phone(const std::string& phone_num) 
{
    Phone = phone_num;
}

void User::set_email(const std::string& mail) 
{
    email = mail;
}

//************Virtual functions*****************************/

void User:: showProfile() const
{
    std::cout<<"username: " << this->username <<std::endl;
    std::cout<<"full name: " << this->full_name<<std::endl;
    std::cout<<"Phone: " << this->Phone<<std::endl;
    std::cout<<"email: " << this->email<<std::endl;
}
