#include"Passenger.hpp"


//**********rule of 5***************** */
Passenger::Passenger(int id, std::string uname, std::string pwd, std::string name, 
                     std::string phone, std::string email, std::string passport,
                     std::string seatPref, std::string mealPref) :
    User(id, uname, pwd, name, phone, email) 
{
    this->passport = passport;
    this->loyaltyPoints = 0; 
    this->seatPreference = seatPref;
    this->mealPreference = mealPref;
    
}
Passenger:: ~Passenger(){}

Passenger::Passenger(const Passenger& other):User(other)
{
    
    this->loyaltyPoints = other.loyaltyPoints;
    this->passport= other.passport;
    this->travelHistory = other.travelHistory;
    this->seatPreference = other.seatPreference;
    this->mealPreference = other.mealPreference;
}

Passenger& Passenger:: operator=(const Passenger& other)
{
    if(this != &other)
    {
        User::operator=(other);
        this->loyaltyPoints = other.loyaltyPoints;
        this->passport= other.passport;
        this->travelHistory = other.travelHistory;
        this->seatPreference = other.seatPreference;
        this->mealPreference = other.mealPreference;
    }
    return *this;
}


//************overriden functions************* */
std::string Passenger:: getRole() const 
{
    return "Passenger";
} 

void Passenger::showProfile() const
{
    std::cout << "--- Passenger Travel Profile ---" << std::endl;
    User::showProfile();
    std:: cout<<"loyaltyPoints: " << this-> loyaltyPoints<<std::endl;
    std:: cout<<"passport: " << this-> passport<<std::endl;
    std:: cout<<"seatPreference: " << this-> seatPreference<<std::endl;
    std:: cout<<"mealPreference: " << this-> mealPreference<<std::endl;

}


void Passenger::displayWindow() const 
{
    int choice;
    bool validChoice = false;
    while (!validChoice)
    {
            std::cout << "\n---PASSENGER SERVICES MAIN MENU ---" << std::endl;
    std::cout<<"please choose a number\n";
    std::cout << "1. View My Profile & Loyalty Points\n"
              << "2. Search Available Flights\n"
              << "3. Book a Flight & Select Seats\n"
              << "4. Modify or Cancel a Reservation\n"
              << "5. Perform Online Check-In\n"
              << "6. Logout" << std::endl;
    std::cin>>choice;
    switch(choice)
    {
        case 1://View My Profile & Loyalty Points
        showProfile();
        validChoice = true;
        break;

        case 2://2. Search Available Flights
        validChoice = true;

        break;

        case 3://3. Book a Flight & Select Seats
        validChoice = true;
        break;

        case 4://4. Modify or Cancel a Reservation
        validChoice = true;
        break;

        case 5://5. Perform Online Check-In
        validChoice = true;
        break;
        
        case 6://6. Logout
        validChoice = true;
        break;   

        default:
        std::cout << "\n[ERROR] Invalid choice! Please select a valid number from 1 to 6." << std::endl;
        break;

    }
    }

            
}



