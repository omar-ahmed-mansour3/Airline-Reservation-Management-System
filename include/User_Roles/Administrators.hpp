#ifndef ADMINSTRATORS_H
#define ADMINSTRATORS_H
#include "User.hpp"

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

    std::string getRole() const override;
    void showProfile() const override;


};
#endif