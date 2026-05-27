# Airline Reservation Management System - Complete UML Class Diagram

```mermaid
classDiagram
    %% --- Inheritance Relationships (User Hierarchy) ---
    User <|-- Passenger
    User <|-- Administrators
    User <|-- BookingAdmin

    %% --- Inheritance Relationships (Crew Hierarchy) ---
    CrewMember <|-- Pilot
    CrewMember <|-- FlightAttendant

    %% --- Architectural Associations ---
    AirlineSystem "1" *-- "many" User : userRegistry
    AirlineSystem "1" *-- "many" Aircraft : fleetRegistry
    AirlineSystem "1" *-- "many" Flight : flightSchedule
    AirlineSystem "1" *-- "many" Reservation : activeReservations
    AirlineSystem "1" *-- "many" CrewMember : crewRegistry
    
    Reservation "1" --> "1" Passenger : Belongs to
    Reservation "1" --> "1" Flight : Books
    Reservation "1" *-- "1" Payment : Processes via
    Aircraft "1" *-- "many" Maintenance : Logs history

    %% --- Class Definitions ---
    class User {
        #string userID
        #string password
        #string name
        #string email
        #string phone
        #string role
        +login(string id, string pass) bool*
        +showStaffProfile() void*
    }

    class Passenger {
        -string passportNumber
        +displayProfile() void
    }

    class CrewMember {
        #string employeeID
        #string rank
        #double salary
        +showStaffProfile() void*
    }

    class Pilot {
        -string licenseNumber
        -int flightHours
        +showStaffProfile() void
    }

    class FlightAttendant {
        -vector~string~ languagesSpoken
        +showStaffProfile() void
    }

    class Administrators {
        +showStaffProfile() void
    }

    class BookingAdmin {
        +showStaffProfile() void
    }

    class Aircraft {
        -string tailNumber
        -string model
        -int capacity
        -string status
        -vector~Maintenance~ maintenanceHistory
        +printFullMaintenanceHistory() void
    }

    class Flight {
        -string flightNumber
        -string origin
        -string destination
        -string departureTime
        -string arrivalTime
        -int availableSeats
        -double basePrice
    }

    class Reservation {
        -string reservationID
        -shared_ptr~Passenger~ passenger
        -shared_ptr~Flight~ flight
        -string seatNumber
        -double totalPrice
        -Payment paymentInfo
        -string status
        +displayReservationDetails() void
    }

    class Payment {
        -string paymentID
        -double amount
        -string paymentMethod
        -string paymentStatus
    }

    class Maintenance {
        -string recordID
        -string date
        -string description
        -string technicianName
        -double cost
    }

    class AirlineSystem {
        -vector~shared_ptr~User~~ userRegistry
        -vector~shared_ptr~Aircraft~~ fleetRegistry
        -vector~shared_ptr~Flight~~ flightSchedule
        -vector~shared_ptr~Reservation~~ activeReservations
        -vector~shared_ptr~CrewMember~~ crewRegistry
        +load_Data_From_Json() void
        +save_Data_To_Json() void
    }

    class ConsoleUI {
        -AirlineSystem system
        -shared_ptr~User~ currentUser
        +run() void
        -displayMainMenu() void
        -handleBookingManagement() void
        -handleCheckIn() void
    }