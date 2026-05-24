#include "Reservation.hpp"

//********** Rule of 5 ****************** */

    
    Reservation::Reservation(std::string booking_id, std::string Seat_number, std::shared_ptr<User> passenger,
                            std::shared_ptr<Flight> flight, BookingStatus bookingStatus)
        : booking_id(std::move(booking_id)), // Using std::move for efficiency!
        Seat_number(Seat_number),
        passenger(passenger),
        flight(flight),
        payment(nullptr),                  
        bookingStatus(bookingStatus)
    {}

    
    Reservation::Reservation(const Reservation& other)
    {
        this->booking_id = other.booking_id;
        this->Seat_number = other.Seat_number;
        this->passenger = other.passenger;
        this->flight = other.flight;
        this->payment = other.payment;
        this->bookingStatus = other.bookingStatus;
    }

   
    Reservation& Reservation::operator=(const Reservation& other)
    {
        if (this != &other)
        {
            this->booking_id = other.booking_id;
            this->Seat_number = other.Seat_number;
            this->passenger = other.passenger;
            this->flight = other.flight;
            this->payment = other.payment;
            this->bookingStatus = other.bookingStatus;
        }
        return *this;
    }

    
    Reservation::~Reservation() {}


//************** Getters ************** */

    std::string Reservation::getBookingId() const 
    {
        return this->booking_id;
    }

    std::string Reservation::getSeatNumber() const 
    {
        return this->Seat_number;
    }

    std::shared_ptr<User> Reservation::getPassenger() const 
    {
        return this->passenger;
    }

    std::shared_ptr<Flight> Reservation::getFlight() const 
    {
        return this->flight;
    }

    std::shared_ptr<Payment> Reservation::getPayment() const 
    {
        return this->payment;
    }

    BookingStatus Reservation::getBookingStatus() const 
    {
        return this->bookingStatus;
    }


//************** Setters ************** */

    void Reservation::setBookingId(const std::string& id) 
    {
        this->booking_id = id;
    }

    void Reservation::setSeatNumber(std::string seat) 
    {
        // Optional: Add validation here to ensure Seat_number is > 0
        this->Seat_number = seat;
    }

    void Reservation::setPassenger(std::shared_ptr<User> pass) 
    {
        this->passenger = pass;
    }

    void Reservation::setFlight(std::shared_ptr<Flight> fl) 
    {
        this->flight = fl;
    }

    void Reservation::setPayment(std::shared_ptr<Payment> pay) 
    {
        this->payment = pay;
    }

    void Reservation::setBookingStatus(BookingStatus status) 
    {
        this->bookingStatus = status;
    }


//************class specific functions**************************/


bool Reservation::confirmReservation() 
{
    if (this->bookingStatus == BookingStatus::Confirmed) 
    {
        std::cout << "[INFO] Reservation " << this->booking_id << " is already confirmed." << std::endl;
        return false;
    }

    if (this->flight->reserveSeat(this->Seat_number)) 
    {
       
        std::cout << "[PAYMENT] Processing charge of $" << this->flight->getPrice() << "..." << std::endl;
        bool paymentSucceeded = true; 
        
        if (paymentSucceeded) 
        {
            this->bookingStatus = BookingStatus::Confirmed;
            std::cout << "[SUCCESS] Payment accepted. Reservation " << this->booking_id << " is Confirmed!" << std::endl;
            return true;
        } 
        else 
        {
            std::cout << "[ERROR] Payment failed. Releasing seat." << std::endl;
            this->flight->releaseSeat(this->Seat_number);
            return false;
        }
    }
    
    return false; 
}

void Reservation::cancelReservation() 
{
    if (this->bookingStatus == BookingStatus::Canceled || this->bookingStatus == BookingStatus::Refunded) 
    {
        std::cout << "[INFO] Reservation is already canceled." << std::endl;
        return;
    }

    this->flight->releaseSeat(this->Seat_number);

    if (this->bookingStatus == BookingStatus::Confirmed) 
    {
        std::cout << "[PAYMENT] Processing refund of $" << this->flight->getPrice() << " to the passenger..." << std::endl;
        this->bookingStatus = BookingStatus::Refunded; 
    } 
    else 
    {
        this->bookingStatus = BookingStatus::Canceled;
    }

    std::cout << "[SUCCESS] Reservation " << this->booking_id << " has been canceled." << std::endl;
}


bool Reservation::modifySeat(const std::string& newSeat) 
{
    if (this->Seat_number == newSeat) 
    {
        std::cout << "[INFO] You are already assigned to seat " << newSeat << "." << std::endl;
        return false;
    }

    std::cout << "[INFO] Attempting to change seat from " << this->Seat_number << " to " << newSeat << "..." << std::endl;

    if (this->flight->reserveSeat(newSeat)) 
    {
        this->flight->releaseSeat(this->Seat_number);
        this->Seat_number = newSeat;
        std::cout << "[SUCCESS] Seat modification complete!" << std::endl;
        return true;
    }

    std::cout << "[ERROR] Seat modification failed. The new seat might be occupied." << std::endl;
    return false;
}

void Reservation::displayTicket() const 
{
    std::string statusStr;
    switch(this->bookingStatus) 
    {
        case BookingStatus::PendingPayment: statusStr = "Pending Payment"; break;
        case BookingStatus::Confirmed:      statusStr = "Confirmed";       break;
        case BookingStatus::Canceled:       statusStr = "Canceled";        break;
        case BookingStatus::Refunded:       statusStr = "Refunded";        break;
    }

    std::cout << "\n=================================================" << std::endl;
    std::cout << "               AIRLINE BOARDING PASS             " << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << "Booking ID:              " << this->booking_id << std::endl;
    std::cout << "Passenger Name:          " << this->passenger->getFullName() << std::endl; 
    std::cout << "Flight Number:           " << this->flight->getFlightNumber() << std::endl;
    std::cout << "Route:                   " << this->flight->getOrigin() << " -> " << this->flight->getDestination() << std::endl;
    std::cout << "Departure Time:          " << this->flight->getDepartureTime() << std::endl;
    std::cout << "Seat Assignment:         " << this->Seat_number << std::endl;
    
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Ticket Status:           " << statusStr << std::endl;
    std::cout << "=================================================\n" << std::endl;
}