#include <iostream>
using namespace std;

//Programmer: Xinyu Mei
//Date: 9/13/2023
//Project 1 for EECS 402
//Purpose: This program implements functionality to accrue interest
//for a bank account

//global constant declarations and initializations here
const double MINIMUM_INTEREST_RATE = 0.0015;
const double MAXIMUM_INTEREST_RATE = 0.004;
const double STANDARD_INTEREST_RATE = 0.00225;
const double LOW_BALANCE_BOUND = 1000;
const double HIGH_BALANCE_BOUND = 15000;
const char AGREE = 'y';

//global function prototypes and documentation here
//Ths function accrues interest, as per the way our bank allows, for
//a single month
bool accrueOneMonthsInterest(
     double &balanceAmt,
     const bool doPrintInfo
     );
//This function accrues interest, as per the way our bank allows, over
//specified number of months     
bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
     );


#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  double initialBalanceAmt;
  double balanceAmt;
  int numMonths;
  char printEachMonth;

  cout << "Enter the initial balance of the account:";
  cin >> initialBalanceAmt;
  balanceAmt = initialBalanceAmt;

  cout << "Enter the number of months to accrue interest:";
  cin >> numMonths;

  cout << "Show month-by-month results - 'y' for yes, any other for no:";
  cin >> printEachMonth;
  
  if (!accrueInterest(balanceAmt, numMonths, printEachMonth == AGREE))
  {
    cout << "Sorry, an error was detected. Unable to provide results!" << endl;
  }
  else
  {
    cout << "Interest accrued for " << numMonths << " months!" << endl;
    cout << "\nInitial balance: " << initialBalanceAmt << endl;
    cout << "Total interest accrued: " << balanceAmt - initialBalanceAmt << endl;
    cout << "Final balance: " << balanceAmt << endl;
  }
  
  return 0;
}
#endif


bool accrueInterest(
     double &balanceAmt,
     const int numMonths,
     const bool doPrintEachMonth
     )
{
  int cntMonths;

  if (numMonths <= 0)
  {
    cout << "ERROR in accrueInterest: numMonths must be > 0, " << 
            "but the value " << numMonths << " was provided!" << endl;
    return false;
  }

  else
  {
    for (cntMonths = 1; cntMonths <= numMonths; cntMonths++)
    {
      if (!accrueOneMonthsInterest(balanceAmt, doPrintEachMonth))
      {
        return false;
      }
    }
    return true;
  }
}


bool accrueOneMonthsInterest(
     double &balanceAmt,
     const bool doPrintInfo
     )
{
  double rateOfMonth;
  double initialBalanceOfMonth;
  initialBalanceOfMonth = balanceAmt;

  if (balanceAmt < 0)
  {
    cout << "Error in accrueOneMonthsInterest: balanceAmt must be >= 0, " << 
            "but the value " << balanceAmt << " was provided!" << endl;
    return false;
  }

  else
  {
    if (balanceAmt < LOW_BALANCE_BOUND)
    {
      rateOfMonth = MINIMUM_INTEREST_RATE;
      balanceAmt *= 1 + rateOfMonth;
    }
    else if (balanceAmt >= HIGH_BALANCE_BOUND)
    {
      rateOfMonth = MAXIMUM_INTEREST_RATE;
      balanceAmt *= 1 + rateOfMonth;
    }
    else
    {
      rateOfMonth = STANDARD_INTEREST_RATE;
      balanceAmt *= 1 + rateOfMonth;
    }

    if (doPrintInfo)
    {
      cout << "Accruing interest for 1 month:" << endl;
      cout << "  Initial balance: " << initialBalanceOfMonth << endl;
      cout << "  Initial rate: " << rateOfMonth << endl;
      cout << "  Interest accrued: " << 
              balanceAmt - initialBalanceOfMonth << endl;
      cout << "  New balance: " << balanceAmt << endl;
    }
    return true;
  }
}