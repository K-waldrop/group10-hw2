/*
 * FILE NAME: main.cpp
 * AUTHOR:
 * DESCRIPTION:
 * Calculates a loan amortization schedule using a loan amount,
 * yearly interest rate, and monthly payment passed through the
 * command line.
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Pass in space-delimited arguments when calling the executable.
// Example:
// ./a.out 1000 18 50

int main(int argc, char* argv[])
{
    // -------------------------------------------------
    // CHECK NUMBER OF ARGUMENTS
    // -------------------------------------------------

    if (argc > 4)
    {
        cout << "Too many arguments. Cannot pass in more than three." << endl;
        return -1;
    }

    // -------------------------------------------------
    // VARIABLES
    // -------------------------------------------------

    double loan_amount = 0.0;
    double yearly_interest_rate = 0.0;
    double monthly_payment = 0.0;

    double monthly_interest_rate;
    double interest;
    double principal;
    double total_interest = 0.0;
    double payment;

    int current_month = 0;

    double arguments[3] = {0.0, 0.0, 0.0};

    // -------------------------------------------------
    // CONVERT COMMAND LINE ARGUMENTS TO NUMBERS
    // -------------------------------------------------

    int i = 1;

    while (i < argc)
    {
        try
        {
            arguments[i - 1] = stod(argv[i]);
        }
        catch (const invalid_argument&)
        {
            if (i == 1)
            {
                cout << "(Invalid loan amount): "
                     << argv[i] << endl;
            }
            else if (i == 2)
            {
                cout << "(Invalid interest rate): "
                     << argv[i - 1] << " "
                     << argv[i] << endl;
            }
            else
            {
                cout << "(Invalid payment): "
                     << argv[i - 2] << " "
                     << argv[i - 1] << " "
                     << argv[i] << endl;
            }

            return -2;
        }

        i++;
    }

    // -------------------------------------------------
    // MAKE SURE ALL THREE ARGUMENTS WERE PROVIDED
    // -------------------------------------------------

    if (argc != 4)
    {
        cout << "Usage: ./a.out <loan> <interest rate> <monthly payment>" << endl;
        return -1;
    }

    loan_amount = arguments[0];
    yearly_interest_rate = arguments[1];
    monthly_payment = arguments[2];

    // -------------------------------------------------
    // VALIDATE NUMERIC VALUES
    // -------------------------------------------------

    if (loan_amount <= 0)
    {
        cout << "(Invalid loan amount): "
             << loan_amount << endl;
        return -2;
    }

    if (yearly_interest_rate < 0)
    {
        cout << "(Invalid interest rate): "
             << loan_amount << " "
             << yearly_interest_rate << endl;
        return -2;
    }

    if (monthly_payment <= 0)
    {
        cout << "(Invalid payment): "
             << loan_amount << " "
             << yearly_interest_rate << " "
             << monthly_payment << endl;
        return -2;
    }

    // -------------------------------------------------
    // CURRENCY FORMATTING
    // -------------------------------------------------

    cout << fixed << setprecision(2);

    // -------------------------------------------------
    // DISPLAY INPUT
    // -------------------------------------------------

    cout << "Loan Amount: " << loan_amount << endl;
    cout << "Interest Rate (% per year): "
         << yearly_interest_rate << endl;
    cout << "Monthly Payments: "
         << monthly_payment << endl;
    cout << endl;

    // -------------------------------------------------
    // CONVERT YEARLY RATE TO MONTHLY DECIMAL RATE
    // -------------------------------------------------

    double monthly_rate_percent = yearly_interest_rate / 12.0;
    monthly_interest_rate = monthly_rate_percent / 100.0;

    // -------------------------------------------------
    // CHECK FOR INSUFFICIENT PAYMENT
    // -------------------------------------------------

    interest = loan_amount * monthly_interest_rate;

    if (monthly_payment <= interest)
    {
        cout << "Monthly payment is insufficient." << endl;
        return -3;
    }

    // -------------------------------------------------
    // AMORTIZATION TABLE
    // -------------------------------------------------

    cout << "*****************************************************************\n";
    cout << "\t\tAmortization Table\n";
    cout << "*****************************************************************\n";
    cout << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";

    // Month 0
    cout << current_month << "\t$"
         << loan_amount;

    if (loan_amount < 1000)
    {
        cout << "\t";
    }

    cout << "\tN/A\tN/A\tN/A\t\tN/A\n";

    // -------------------------------------------------
    // LOOP THROUGH EACH MONTH
    // -------------------------------------------------

    while (loan_amount > 0)
    {
        current_month++;

        interest = loan_amount * monthly_interest_rate;

        // ---------------------------------------------
        // FINAL PAYMENT
        // ---------------------------------------------

        if (loan_amount + interest <= monthly_payment)
        {
            payment = loan_amount + interest;
            principal = loan_amount;

            total_interest += interest;

            loan_amount = 0;
        }

        // ---------------------------------------------
        // NORMAL PAYMENT
        // ---------------------------------------------

        else
        {
            payment = monthly_payment;

            principal = payment - interest;

            loan_amount = loan_amount - principal;

            total_interest += interest;
        }

        // ---------------------------------------------
        // PRINT THIS MONTH
        // ---------------------------------------------

        cout << current_month << "\t$"
             << loan_amount;

        if (loan_amount < 1000)
        {
            cout << "\t";
        }

        cout << "\t$" << payment
             << "\t" << monthly_rate_percent
             << "\t$" << interest
             << "\t\t$" << principal
             << endl;
    }

    // -------------------------------------------------
    // FINAL RESULTS
    // -------------------------------------------------

    cout << "****************************************************************\n";

    cout << "\nIt takes "
         << current_month
         << " months to pay off the loan.\n";

    cout << "Total interest paid is: $"
         << total_interest
         << endl;

    return 0;
}