#ifndef SALESTRANSACTION_H
#define SALESTRANSACTION_H

#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

class SalesTransaction {
private:
    std::string transactionID;
    std::string productID;
    int quantity;
    double salePrice;        // Per unit
    double totalAmount;
    std::string transactionDate;  // YYYY-MM-DD
    std::string transactionType;  // "Sale" or "Purchase"
    double discountApplied;  // 0.0 to 1.0

public:
    SalesTransaction();
    SalesTransaction(const std::string& transID, const std::string& prodID,
                     int qty, double price, const std::string& date,
                     const std::string& type);
    
    ~SalesTransaction();
    
    // Getters
    std::string getTransactionID() const;
    std::string getProductID() const;
    int getQuantity() const;
    double getSalePrice() const;
    double getTotalAmount() const;
    std::string getTransactionDate() const;
    std::string getTransactionType() const;
    double getDiscountApplied() const;
    
    // Setters
    void setQuantity(int qty);
    void setSalePrice(double price);
    void setDiscountApplied(double discount);
    
    // Calculations
    double calculateProfit(double costPrice) const;
    void applyDiscount(double discountPercent);
    void calculateTotalAmount();
    
    // File operations
    std::string toCSVString() const;
    void loadFromCSVString(const std::string& line);
    
    // Display
    void displayInfo() const;
    
    // Utility
    static std::string generateTransactionID();
    static std::string getCurrentDate();
};

#endif // SALESTRANSACTION_H
