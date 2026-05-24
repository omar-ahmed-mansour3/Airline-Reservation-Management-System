#ifndef ADMINSTRATORS_H
#define ADMINSTRATORS_H
#include<User.hpp>

class Administrators : public User
{ 
    private:
    //**********ATTRIBUTES****************** */

    public:

    //**********rule of 5***************** */
    Administrators(int userid, std::string username , std::string password, 
        std::string full_name,std::string phone, std::string email);
    Administrators(const Administrators& other);
    Administrators& operator=(const Administrators& other);
    ~Administrators();





    //************overriden functions************* */
    void displayWindow () const override;//: Must show administrative options "Add/Remove Flight," "Manage Users," and "View Maintenance Logs"
    std::string getRole() const override;
    void showProfile() const override;

    //**i don't think we will need to override, just implement them in user */
    void searchFlights() override;
    void manageBooking() override;
    //**i don't think we will need to override, just implement them in user */


    //************class specific functions************************* */

    void manageUsers(); //The entry point for creating, updating, or deleting user accounts.
    void manageFlights();
    void manageAircraft();
    void manageCrew();
    void viewReports();
    void scheduleMaintenance();//might evolve into 2 functions 
};
#endif