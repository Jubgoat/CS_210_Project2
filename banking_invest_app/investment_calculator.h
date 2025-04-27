#ifndef INVESTMENT_CALCULATOR_H_
#define INVESTMENT_CALCULATOR_H_

#include <iostream>
#include <iomanip>
#include <cmath>

class InvestmentCalculator { // InvestmentCalculator.h
public :
	void Run(); // Main function to run the investment calculator
private:
	void GetUserInput(); // Get user input for investment parameters
	void CalculateWithoutMonthlyDeposits(); // Calculate investment without monthly deposits
	void DisplayInputSummary() const; // Display a summary of the input data
	void CalculateWithMonthlyDeposits(); // Calculate investment with monthly deposits
	void WaitForUser() const;  // Wait for user input before exiting the program

	float m_initialInvestment; // Initial investment amount
	float m_monthlyDeposit; // Monthly deposit amount
	float m_annualInterest; // Annual interest rate in percentage
	int m_years; // Number of years for the investment
};

#endif
