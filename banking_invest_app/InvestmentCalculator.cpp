#include "investment_calculator.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

void InvestmentCalculator::GetUserInput() { // GetUserInput function to gather user input
	std::cout << "**************************************\n"; 
	std::cout << "************ Data Input **************\n"; // Prompt user for input

	std::cout << "Initial Investment Amount: $"; // Prompt for initial investment
	std::cin >> m_initialInvestment; // Check for valid input

	std::cout << "Monthly Deposit: $"; // Prompt for monthly deposit
	std::cin >> m_monthlyDeposit; // Check for valid input

	std::cout << "Annual Interest Rate (in %): "; // Prompt for annual interest rate
	std::cin >> m_annualInterest; // Check for valid input

	std::cout << "Number of Years: "; // Prompt for number of years
	std::cin >> m_years; // Check for valid input

	if (m_initialInvestment < 0 || m_monthlyDeposit < 0 || m_annualInterest < 0 || m_years <= 0) { // Validate input
		throw std::invalid_argument("All values must be positive"); // Throw an exception if any input is invalid
	}
}

void InvestmentCalculator::DisplayInputSummary() const { // DisplayInputSummary function to show the input summary
	std::cout << std::fixed << std::setprecision(2); // Set precision for floating-point output
	std::cout << "\n************************************\n";
	std::cout << "************Data Input ***************\n";
	std::cout << "Initial Investment Amount: $" << m_initialInvestment << "\n"; // Display initial investment
	std::cout << "Monthly Deposit: $" << m_monthlyDeposit << "\n"; // Display monthly deposit
	std::cout << "Annual Interest: " << m_annualInterest << "%\n"; // Display annual interest rate
	std::cout << "Number of Years: " << m_years << "\n"; // Display number of years
}

void InvestmentCalculator::CalculateWithoutMonthlyDeposits() { // CalculateWithoutMonthlyDeposits function to compute investment without monthly deposits
	float totalAmount = m_initialInvestment; // Start with the initial investment

	std::cout << "\n\n\tBalance and Interest Without Monthly Deposits\n"; //	Display header for the calculation results
	std::cout << "==================================================\n"; // Set up the header for the output table
	std::cout << std::left << std::setw(10) << "Year" << std::setbase(20) << "Year End Balance" << "Year End Interest\n"; // Set up the header for the output table
	std::cout << "--------------------------------------------------\n";

	for (int year = 0; year < m_years; ++year) { // Loop through each year to calculate the balance and interest
		const float interestAmount = totalAmount * (m_annualInterest / 100); // Calculate interest for the year
		totalAmount += interestAmount; // Update the total amount with the interest earned

		std::cout << std::setw(10) << (year + 1) << "$" << std::setw(19) << totalAmount << "$" << interestAmount << "\n"; // Output the year, year-end balance, and year-end interest

	}
}

void InvestmentCalculator::CalculateWithMonthlyDeposits() { // CalculateWithMonthlyDeposits function to compute investment with monthly deposits
	float totalAmount = m_initialInvestment; // Start with the initial investment

	std::cout << "\n\n\tBalance and Interest With Monthly Deposits\n"; // Display header for the calculation results	
	std::cout << "==================================================\n"; // Set up the header for the output table
	std::cout << std::left << std::setw(10) << "Year" 
		<< std::setw(20) << "Year End Balance"
		<< "Year End Interest\n"; // Set up the header for the output table
	std::cout << "--------------------------------------------------\n";

	for (int year = 0; year < m_years; ++year) { // Loop through each year to calculate the balance and interest
		float yearlyTotalInterest = 0; // Initialize yearly total interest to zero for each year

		for (int month = 0; month < 12; ++month) { // Loop through each month of the year
			const float interestAmount = (totalAmount + m_monthlyDeposit) *
				(m_annualInterest / 100 / 12); // Calculate monthly interest
			yearlyTotalInterest += interestAmount; // Accumulate the total interest for the year
			totalAmount += m_monthlyDeposit + interestAmount; // Update the total amount with the monthly deposit and interest earned
		}

		std::cout << std::setw(10) << (year + 1) // Output the year number
			<< "$" << std::setw(19) << totalAmount 
			<< "$" << yearlyTotalInterest << "\n"; // Output the year-end balance and year-end interest
	}
}

void InvestmentCalculator::WaitForUser() const { // WaitForUser function to pause the program until the user presses Enter
	std::cout << "Press Enter to continue..."; // Prompt user to press Enter
	std::cin.ignore(); // Clear the input buffer to avoid skipping the next input
	std::cin.get(); // Wait for user input (Enter key)
}

void InvestmentCalculator::Run() { // Run function to execute the investment calculator
	try { 
		GetUserInput(); // Get user input for investment parameters
		DisplayInputSummary(); // Display the input summary
		WaitForUser(); // Wait for user to read the summary before proceeding

		CalculateWithoutMonthlyDeposits(); // Calculate and display investment without monthly deposits
		CalculateWithMonthlyDeposits(); // Calculate and display investment with monthly deposits
	}
	catch (const std::exception& exception) { // Catch any exceptions thrown during the execution
		std::cerr << "Error: " << exception.what() << "\n"; // Display the error message
	}
}