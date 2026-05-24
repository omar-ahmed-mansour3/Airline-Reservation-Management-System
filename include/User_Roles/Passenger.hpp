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
    void displayWindow() const override;
    std::string getRole() const override;
    
    //**i don't think we will need to override, just implement them in user */
    void searchFlights() override;
    void manageBooking() override;
    //**i don't think we will need to override, just implement them in user */

    //************class specific functions************************* */
    void makeReservation();//  Initiates the booking process for a selected flight.
    void selectSeat();//: Interfaces with the flight's seat map to pick a specific spot
    void cancelReservation();//Allows the passenger to remove an existing booking and potentially trigger a refund.
    //??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
    void performOnlineCheckIn();//Enables the passenger to check in for a flight and obtain a boarding pass.
    void viewLoyaltyStatus(); //allow point redemption, we already display that stuff on show profile

};



#endif