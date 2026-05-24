#ifndef PAYMENT_HPP
#define PAYMENT_HPP

#include <string>
#include <iostream>

enum PaymentMethod {
    CreditCard,
    DebitCard,
    PayPal,
    LoyaltyPoints,
    Cash 
};

enum PaymentStatus {
    Pending,
    Completed,
    Failed,
    Refunded
};

class Payment {
private:
    // ************ ATTRIBUTES ******************
    std::string transactionID; 
    double amount;            
    PaymentMethod method;      
    PaymentStatus status;      
    std::string timestamp;     

public:
    // ************ Rule of 5*******************
    // Note: status is intentionally omitted here as new payments start as Pending
    Payment(std::string txID, double amt, PaymentMethod payMethod, std::string time);
    
    Payment(const Payment& other);
    Payment& operator=(const Payment& other);
    ~Payment();

    //************class specific functions************************* */
    bool processPayment();     
    bool processRefund();     
    void displayReceipt() const; 

    // ************ GETTERS *************************
    std::string getTransactionID() const;
    double getAmount() const;
    PaymentMethod getMethod() const; // Added for completeness!
    std::string getTimestamp() const; // Added for completeness!
    PaymentStatus getStatus() const;
    std::string getStatusString() const; 
    std::string getMethodString() const; 

    // ************ SETTERS *************************
    void setTransactionID(const std::string& txID);
    void setAmount(double amt);
    void setMethod(PaymentMethod payMethod);
    void setStatus(PaymentStatus newStatus);
    void setTimestamp(const std::string& time);
};

#endif