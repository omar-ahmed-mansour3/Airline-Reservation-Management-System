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

void BookingAdmin::displayWindow() const 
{
    int choice;
    bool validChoice = false;
    while (!validChoice)
    {
        std::cout << "\n--- BOOKING ADMIN SERVICES MAIN MENU ---" << std::endl;
        std::cout << "Please choose a number\n";
        std::cout << "1. View Staff Profile\n"
                  << "2. Search Available Flights\n"
                  << "3. Facilitate Passenger Booking & Seat Selection\n"
                  << "4. Process Booking Modification or Cancellation\n"
                  << "5. Manage Airport Counter Check-In\n"
                  << "6. Exit System" << std::endl;
                  
        std::cin >> choice;
        
        switch(choice)
        {
            case 1: // 1. View Staff Profile
                showProfile(); 
                validChoice = true; // Valid option selected, exits loop
                break;

            case 2: // 2. Search Available Flights
                // searchFlights();
                validChoice = true;
                break;

            case 3: // 3. Facilitate Passenger Booking & Seat Selection
                validChoice = true;
                break;

            case 4: // 4. Process Booking Modification or Cancellation
                validChoice = true;
                break;

            case 5: // 5. Manage Airport Counter Check-In
                validChoice = true;
                break;
                
            case 6: // 6. Exit System
                std::cout << "Exiting system... Goodbye!" << std::endl;
                validChoice = true;
                break;   

            default:
                // Do NOT set validChoice to true here. 
                // This forces the while loop to print the menu again!
                std::cout << "\n[ERROR] Invalid choice! Please select a valid number from 1 to 6." << std::endl;
                break;
        }
    }
}


