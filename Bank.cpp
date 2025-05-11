#include "Stronghold.h"
#include <iostream>
using namespace std;
Bank::Bank()
{
    totalMoney = 5000;
    totalLoans = 0;
    fraud = false;
}
void Bank::takeLoan() 
{
    int loan;
    cout << "Enter loan amount you want to take: ";
    cin >> loan;
    totalLoans = totalLoans + loan;
    totalMoney = totalMoney + loan;
    cout << "Loan of " << loan << " coins taken." << endl;
}
void Bank::payLoan() 
{
    if (totalLoans == 0)
    {
        cout << "No loans to pay." << endl;
        return;
    }
    int pay;
    cout << "Enter amount you want to pay back: ";
    cin >> pay;
    if (pay > totalLoans)
    {
        cout << "You are paying more than your loan. Paying only " << totalLoans << endl;
        pay = totalLoans;
    }
    if (pay > totalMoney) 
    {
        cout << "Not enough money in bank to pay loan." << endl;
        return;
    }
    totalLoans = totalLoans - pay;
    totalMoney = totalMoney - pay;

    cout << "Paid " << pay << " coins of loan." << endl;
}
void Bank::checkMoney() 
{
    cout << "Bank has " << totalMoney << " coins available." << endl;
}
void Bank::detectFraud() 
{
    int chance = rand() % 10; 
    if (chance == 0)
    { 
        fraud = true;
        int stolen = 500 + (rand() % 1000); 
        if (totalMoney >= stolen)
        {
            totalMoney = totalMoney - stolen;
        }
        else 
        {
            totalMoney = 0;
        }
        cout << "Fraud detected! " << stolen << " coins stolen!" << endl;
    }
    else 
    {
        fraud = false;
        cout << "No fraud detected." << endl;
    }
}
void Bank::showBank() 
{
    cout << "\n--- Bank Status ---" << endl;
    cout << "Total Money: " << totalMoney << " coins" << endl;
    cout << "Total Loans: " << totalLoans << " coins" << endl;
    if (fraud)
    {
        cout << "Warning: Recent fraud detected!" << endl;
    }
    else
    {
        cout << "No fraud detected." << endl;
    }
}
