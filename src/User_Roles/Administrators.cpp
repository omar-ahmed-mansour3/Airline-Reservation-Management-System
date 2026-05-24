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

void Administrators::displayWindow() const 
{
    int choice;
    bool validChoice = false;

    while (!validChoice)
    {
        std::cout << "\n*** MASTER AIRLINE ADMINISTRATION CONSOLE ***" << std::endl;
        std::cout << "Please choose a number:\n";
        std::cout << "1. View Admin Profile\n"
                  << "2. Manage User Accounts\n"
                  << "3. Manage Flight Schedules\n"
                  << "4. Manage Aircraft & Fleet\n"
                  << "5. Assign Flight Crew\n"
                  << "6. View Operational & Financial Reports\n"
                  << "7. Exit System" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
            case 1: // 1. View Admin Profile
                showProfile(); 
                validChoice = true;
                break;

            case 2: // 2. Manage User Accounts
                
                validChoice = true;
                break;

            case 3: // 3. Manage Flight Schedules
              
                break;

            case 4: // 4. Manage Aircraft & Fleet
              
                validChoice = true;
                break;

            case 5: // 5. Assign Flight Crew
                
                validChoice = true;
                break;

            case 6: // 6. View Operational & Financial Reports
                
                validChoice = true;
                break;

            case 7: // 7. Exit System
                std::cout << "Exiting Master Console... Goodbye!" << std::endl;
                validChoice = true;
                break;

            default:
                std::cout << "\n[ERROR] Invalid choice! Please select a valid option (1-7)." << std::endl;
                
                break;
        }
    }
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
