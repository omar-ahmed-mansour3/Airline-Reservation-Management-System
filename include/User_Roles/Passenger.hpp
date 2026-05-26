#ifndef PASSENGER_H
#define PASSENGER_H
#include"User.hpp"
#include<vector>
#include"Reservation.hpp"
#include<iostream>
class Passenger: public User
{
private:
    //**********ATTRIBUTES****************** */
    int loyaltyPoints =0;
    std::string passport;
    std::vector<Reservation>travelHistory ;
    std::string seatPreference; 
    std::string mealPreference;

    
public:
    //************RULE OF 5 *********************** */
Passenger(int id, std::string uname, std::string pwd, std::string name, 
              std::string phone, std::string email, std::string passport,
              std::string seatPref = "None", std::string mealPref = "None");
              
    Passenger(const Passenger& other);
    Passenger& operator=(const Passenger& other);

    ~Passenger();

    //************overriden functions************* */

    void showProfile() const override;
    std::string getRole() const override;
    

};



#endif