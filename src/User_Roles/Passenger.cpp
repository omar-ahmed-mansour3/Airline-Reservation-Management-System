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



