#ifndef RESERVATION_H
#define RESERVATION_H
#include<memory>
#include"Flight.hpp"
#include"User.hpp"
#include"Payment.hpp"
enum class BookingStatus
{
    Confirmed, Refunded, Canceled, PendingPayment
};
class Reservation
{
    private: 
        std::string booking_id;
        std::string Seat_number;
        std::shared_ptr<User> passenger;     
        std::shared_ptr<Flight> flight;
        std::shared_ptr<Payment> payment;       
        BookingStatus bookingStatus;
    public:

    //**********rule of 5***************** */
        Reservation( std::string booking_id, std::string Seat_number,std::shared_ptr<User> passenger,
        std::shared_ptr<Flight> flight,BookingStatus bookingStatus);
        Reservation(const Reservation& other);
        Reservation& operator=(const Reservation& other);
        ~Reservation();

    //************** Getters ************** */
        std::string getBookingId() const;
        std::string getSeatNumber() const;
        std::shared_ptr<User> getPassenger() const;
        std::shared_ptr<Flight> getFlight() const;
        std::shared_ptr<Payment> getPayment() const;
        BookingStatus getBookingStatus() const;

    //************** Setters ************** */
        void setBookingId(const std::string& id);
        void setSeatNumber(std::string seat);
        void setPassenger(std::shared_ptr<User> pass);
        void setFlight(std::shared_ptr<Flight> fl);
        void setPayment(std::shared_ptr<Payment> pay);
        void setBookingStatus(BookingStatus status);

    //************ Class Specific Functions ****************** */
        bool confirmReservation();
        void cancelReservation();
        bool modifySeat(const std::string& newSeat);
        void displayTicket() const;

    

};


#endif