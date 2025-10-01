#include <iostream>
#include <memory>

/*
 * OOPS CONCEPTS SUMMARY
 * ----------------------------------------------------------------------
 * Learnt 4 Pillars of OOP using the BankAccount Hierarchy.
 * * 1. ENCAPSULATION (Data Hiding and Control)
 * - Goal: Bundle data (attributes) and methods (operations) and protect the data.
 * - C++ Feature: ACCESS SPECIFIERS
 * - private: Data only accessible within its own class (e.g., helper methods).
 * - protected: Data only accessible within its own class AND derived classes (used for 'balance').
 * - public: Accessible from anywhere (the class's public interface, e.g., 'deposit()').
 * * 2. INHERITANCE (Code Reuse)
 * - Goal: Create new classes (derived) from existing ones (base) to reuse code.
 * - C++ Feature: DERIVATION SYNTAX
 * - class Derived : public Base {}
 * - Public Inheritance: Preserves the access level of inherited members.
 * * 3. POLYMORPHISM (Many Forms)
 * - Goal: Treat objects of different types (derived classes) through a common interface (base pointer/reference).
 * - C++ Feature: VIRTUAL KEYWORD
 * - virtual void withdraw(int amount);  // Enables dynamic dispatch in the base class.
 * - This forces the program to look at the object's ACTUAL type at RUNTIME, not the pointer's type.
 * - void withdraw(int amount) override; // Optional keyword, but highly recommended for clarity and compiler checks.
 * * 4. ABSTRACTION (Defining the Contract/Interface)
 * - Goal: Define required functionality without providing implementation details.
 * - C++ Feature: PURE VIRTUAL FUNCTION(Run Time Polymorphism)
 * - virtual void withdraw(int amount) = 0;
 * - Effect: The base class becomes an **Abstract Class** (cannot be instantiated).
 * - Requirement: All concrete derived classes (like SavingsBankAccount) MUST provide an implementation for the pure virtual function.
 * - Compile time polymorphism using new deposit function that factors in exchangeRate for foreign deposits in dollars
 * * ----------------------------------------------------------------------
 * KEY C++ BEST PRACTICES USED:
 * * - RAII (Resource Acquisition Is Initialization): 
 * - Use of smart pointers (std::unique_ptr) to automatically manage memory and prevent leaks.
 * * - Static vs. Dynamic Dispatch:
 * - Static: Compiler decides which function to call at compile time (occurs without 'virtual').
 * - Dynamic: Program decides which function to call at run time (occurs with 'virtual').
 * * - Trade-off: Pure virtual functions enforce the interface (Abstraction) but prevent derived classes from calling a common implementation in the base class.
 */

class BankAccount
{
protected: //Private member is inaccessible by derived class
    double balance;
public:
    BankAccount() : balance(0) 
    {

    }

    void deposit(double amount)
    {
        balance += amount;
        std::cout << "Amount deposited is ₹" << amount << " and final balance is ₹" << balance << std::endl;
    }

    //Compile time polymorphism. New deposit function for foreign deposits in dollars
    void deposit(double amount, double exchangeRate)
    {
        auto convertedAmount = amount * exchangeRate;
        balance += convertedAmount;
        std::cout << "Foreign deposit: $" << amount << " converted to ₹" << convertedAmount 
                  << ". Final balance is ₹" << balance << std::endl;
    }

    // virtual void withdraw(double amount) //For run time polymorphism
    // {
    //     if(amount > balance)
    //     {
    //         std::cout << "Amount requested for withdrawl ₹" << amount << " is greater than total money in bank account" << std::endl;
    //         return;
    //     }
    //     balance -= amount;
    //     std::cout << "₹" << amount << " withdrawn from bank account " << std::endl;
    //     std::cout << "Remaining balance in account is ₹" << balance << std::endl;
    // }
    virtual void withdraw(double amount) = 0; //Pure virtual function

    double getBalance() const { return balance; }
};

//public inherits members by keeping their original access level,public stays public, and protected stays protected.
//protected inherits public and protected members of base class as protected
//private inherits public and protected members of base class as private
//private members of base class are inaccessible by derived class
class SavingsBankAccount : public BankAccount
{
private:
    double interestRate;
public:
    SavingsBankAccount() : interestRate(3) 
    {

    }

    void setInterestRate(double rate)
    {
        interestRate = rate;
    }

    //To override base class implementation
    // void withdraw(double amount) override 
    // {
    //     std::cout << "Amount requested for withdrawl ₹" << amount << " from savings bank account" << std::endl;
    //     if(amount < 1000)
    //     {
    //         std::cout << "Minimum amount for withdrawl is ₹1000" << std::endl;
    //         return;
    //     }
        
    //     //2. Delegate the remaining logic (balance check and actual subtraction)
    //     //to the base class's withdraw method for code reuse.
    //     BankAccount::withdraw(amount); 
    // }

    //Abstraction
    void withdraw(double amount) override
    {
        std::cout << "Amount requested for withdrawl ₹" << amount << " from savings bank account" << std::endl;
        if(amount < 1000)
        {
            std::cout << "Minimum amount for withdrawl is ₹1000" << std::endl;
            return;
        }
        if(amount > balance)
        {
            std::cout << "Amount requested for withdrawl ₹" << amount << " is greater than total money in bank account" << std::endl;
            return;
        }
        balance -= amount;
        std::cout << "₹" << amount << " withdrawn from bank account " << std::endl;
        std::cout << "Remaining balance in account is ₹" << balance << std::endl;
    }

    //Simple interest for simplicity
    void addInterestToBalance(int time_in_years)
    {
        auto interest = (balance * interestRate * time_in_years) / 100;
        balance += interest;
    }

    double getInterestRate() const { return interestRate; }
};

int main()
{
    std::unique_ptr<BankAccount> account_ptr = std::make_unique<SavingsBankAccount>();
    account_ptr->deposit(10000);
    account_ptr->deposit(10023, 87);
    account_ptr->withdraw(5000);
    return 0;
}
