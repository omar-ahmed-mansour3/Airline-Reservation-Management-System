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


//************class specific functions************************* */

// void Administrators ::manageUsers()
// {
//     int choice;
//     bool validChoice= false;

//     while(!validChoice)
//     {
//         std::cin>>choice;
//         std::cout << "\n--- USER MANAGEMENT SUB-SYSTEM ---" << std::endl;
//         std::cout << "Please choose a number\n";
//         std::cout << "1. Create New User Account\n"
//           << "2. View All Registered Users\n"
//           << "3. Update Existing User Information\n"
//           << "4. Delete a User Account\n"
//           << "5. Return to Main Admin Menu" << std::endl;

//         switch(choice)
//         {

//         }
//     }
// }
