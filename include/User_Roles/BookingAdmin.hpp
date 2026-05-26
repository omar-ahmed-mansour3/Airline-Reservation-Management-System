#ifndef BOOKINGADMIN_H
#define BOOKINGADMIN_H
#include "User.hpp"
class BookingAdmin : public User
{

    private:
    //**********ATTRIBUTES****************** */


    public:

    //************RULE OF 5 *********************** */
    BookingAdmin(int userid, std::string username , std::string password, 
        std::string full_name,std::string phone, std::string email);
    BookingAdmin(const BookingAdmin& other);
    BookingAdmin& operator=(const BookingAdmin& other);
    ~BookingAdmin();




    //************overriden functions************* */

    std::string getRole() const override;
    void showProfile() const override;


};

#endif