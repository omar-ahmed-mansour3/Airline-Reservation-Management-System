#include<BookingAdmin.hpp>

//**********rule of 5***************** */
BookingAdmin::BookingAdmin(int userid, std::string username , std::string password, 
        std::string full_name,std::string phone, std::string email):
        User(userid,username,password,full_name,phone,email){}

BookingAdmin::BookingAdmin(const BookingAdmin& other):User(other)
{}
    

BookingAdmin& BookingAdmin::operator=(const BookingAdmin& other)
{
    if(this!=&other)
    {
        User:: operator=(other);
    }
    return *this;
}

BookingAdmin::~BookingAdmin(){}



//************overriden functions************* */

std::string BookingAdmin::getRole() const 
{
    return "BookingAdmin";
}

void BookingAdmin::showProfile() const
{
    std::cout << "--- Booking Admin Profile ---" << std::endl;
    User::showProfile();
}

