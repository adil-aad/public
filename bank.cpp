#include <iostream>
#include <string>
#include <iomanip>
#include <random>
using namespace std;

int main()
{
    const int numberofAccounts = 100, numberofTransactions = 100, numberofAutomatedTransactions = 100;

    int currentAccountIndex = 0, currentTransactionIndex = 0, currentAutoTransactionIndex = 0;

    int accountnumber[numberofAccounts], balance[numberofAccounts];
    string name[numberofAccounts], password[numberofAccounts];

    int transactionAmount[numberofTransactions], transactionAccountNumber[numberofTransactions];
    string transactionType[numberofTransactions], transactionTime[numberofTransactions];
    time_t currentTime = time(0);

    const int numberOfCurrencies = 4;
    string USD, pound, euro, ETB;
    string depositCurrencies[numberOfCurrencies] = {USD, pound, euro, ETB};
    double rates[numberOfCurrencies] = {54.4, 64.7, 58.3, 1.0};

    int paymentFrequency[numberofAutomatedTransactions];
    double paymentAmount[numberofAutomatedTransactions];
    int paymentFrom[numberofAutomatedTransactions], paymentTo[numberofAutomatedTransactions];

    string transactionLogPassword = "qwe123";

    bool banking = true;

menu:
    while (banking)
    {
        tm *timeNow = localtime(&currentTime);

        int dayOfWeek = timeNow->tm_wday;
        int hourOfDay = timeNow->tm_hour;
        int dayOfMonth = timeNow->tm_mday;

        const string dayNames[] = {
            "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

        string currentDayName = dayNames[dayOfWeek];
        const float interestRate = 4.0;

        if (currentDayName == "Thursday")
        {
            for (int i = 0; i < currentAccountIndex; i++)
            {
                balance[i] += (balance[i] * (interestRate / 100));
            }
        }
        for (int i = 0; i < currentAutoTransactionIndex; i++)
        {
            if (dayOfMonth == 15)
            {
                // Check if there are sufficient funds
                if (balance[paymentFrom[i]] >= paymentAmount[i])
                {
                    // Deduct the payment amount from the balance
                    balance[paymentFrom[i]] -= paymentAmount[i];
                    balance[paymentTo[i]] += paymentAmount[i];
                    ostringstream ossDate;
                    ostringstream ossTime;

                    string dateAndTime;

                    currentTime = time(0);
                    tm *timeNow = localtime(&currentTime);
                    ossDate << put_time(timeNow, "%d-%m-%Y ");
                    ossTime << put_time(timeNow, "%I:%M %p");
                    dateAndTime = ossDate.str() + ossTime.str();

                    transactionAmount[currentTransactionIndex] = -paymentAmount[i];
                    transactionAccountNumber[currentTransactionIndex] = accountnumber[paymentFrom[i]];
                    transactionType[currentTransactionIndex] = "Auto payment";
                    transactionTime[currentTransactionIndex] = dateAndTime;

                    currentTransactionIndex++;

                    transactionAmount[currentTransactionIndex] = paymentAmount[i];
                    transactionAccountNumber[currentTransactionIndex] = accountnumber[paymentTo[i]];
                    transactionType[currentTransactionIndex] = "Auto payment";
                    transactionTime[currentTransactionIndex] = dateAndTime;

                    currentTransactionIndex++;
                }
            }
        }
        system("cls");
        cout << "----------------------------------------------------" << endl;
        cout << "|              Welcome to our bank                  |" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "|   1. Create an account                            |" << endl;
        cout << "|   2. Deposit                                      |" << endl;
        cout << "|   3. Withdraw                                     |" << endl;
        cout << "|   4. Transfer                                     |" << endl;
        cout << "|   5. Transaction History                          |" << endl;
        cout << "|   6. Automated payment setup                      |" << endl;
        cout << "|   7. Edit account information                     |" << endl;
        cout << "----------------------------------------------------" << endl;

        int userchoice;
        cout << "Choose the number corresponding to the service you are looking for" << endl;
        cin >> userchoice;

        switch (userchoice)
        {
            /// creates an account
        case 1:
        {
            system("cls");
            cout << "Enter Your Name: ";
            getline(cin.ignore(), name[currentAccountIndex]); // cin.ignore() is a function in C++ that is used to clear or ignore characters in the input buffer.
        enterAgain:
            string temporaryPassword = ""; /// stores the input password in a string temporarly to check it's validity
            cout << "Enter a new password for your account: ";
            getline(cin, temporaryPassword);

            if (temporaryPassword.length() < 7)
            {
                cout << "Password has to be a minimum of 7 characters " << endl;
                goto enterAgain;
            }
            else
            {
                password[currentAccountIndex] = temporaryPassword; // assigns it if it is valid
            }
            balance[currentAccountIndex] = 0;

            bool IsItUnique = false;

            random_device rd;
            mt19937 generator(rd());
            uniform_int_distribution<int> distribution(10000, 99999); // generates a random account number in the given range

            int randomAccountnumber = distribution(generator); // loop to check that no two numbers generated are the same

            for (int i = 0; i < numberofAccounts; i++)
            {
                if (accountnumber[i] != randomAccountnumber)
                {
                    accountnumber[currentAccountIndex] = randomAccountnumber; // approves the number account number
                    IsItUnique = true;                                        // why did we use it
                }
                while (IsItUnique == false)
                {
                    randomAccountnumber = distribution(generator);

                    if (accountnumber[i] != randomAccountnumber)
                    {
                        accountnumber[currentAccountIndex] = randomAccountnumber;
                        IsItUnique = true;
                    }
                }
            }
            cout << " your account number is " << accountnumber[currentAccountIndex] << endl
                 << " your current balance is " << balance[currentAccountIndex] << endl;

            currentAccountIndex++;
            char Continuetomenu;
            cout << " Click [Y] to return to main menu and any other key to exit the program" << endl;
            cin >> Continuetomenu;
            if (Continuetomenu == 'Y' || Continuetomenu == 'y')
                ;

            else
                banking = false;

            break;
        }
        /// makes a deposit to an account
        case 2:
        {
            system("cls");
            cout << "Deposit into an account" << endl;
            int inputAccount, inputAccountIndex;
            bool isItFound = false;
            while (isItFound == false)
            {
            EnterAccountAgain:
                cout << "Enter your account number " << endl;
                cin >> inputAccount;
                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a number." << endl; // outputs inavalid if the expected datatype and the user inputs' data type are not the same
                    cin.clear();                                             // Clear the error state of cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');     // Discard any remaining input in the buffer and defines the maximum limit of characters
                    goto EnterAccountAgain;
                }
                for (int i = 0; i < currentAccountIndex; i++)
                {
                    if (accountnumber[i] == inputAccount)
                    {
                        isItFound = true;
                        inputAccountIndex = i;
                        break;
                    }
                }
                if (isItFound == false)
                {
                    cout << "Account does not exist " << endl
                         << "Make sure you entered the correct account number " << endl;
                    goto EnterAccountAgain;
                }
            }

            if (isItFound == true)
            {
                double depositAmount;
                int currencyAtHand, currencyConvertedtoBirr;

                cout << "Hello " << name[inputAccountIndex] << endl;
                cout << "[1] US Dollar" << endl;
                cout << "[2] British Pound" << endl;
                cout << "[3] Euro" << endl;
                cout << "[4] ETB" << endl;
            EnterCurrency:
                cout << "These are the list of foreign currencies our bank works with" << endl
                     << "Enter the currency of the money you are looking to deposit" << endl;
                cin >> currencyAtHand;
                if (currencyAtHand < 1 || currencyAtHand > 4)
                {
                    cout << "Invalid input. Please enter a number between 1 and 4." << endl;
                }
                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    goto EnterCurrency;
                }
                cout << "Enter the amount of money you want to deposit: ";
            EnterCorrectAmount:
                cin >> depositAmount;
                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    goto EnterCorrectAmount;
                }
                if (depositAmount >= 1)
                {
                    currencyConvertedtoBirr = depositAmount * rates[currencyAtHand - 1];
                    balance[inputAccountIndex] += currencyConvertedtoBirr;

                    ostringstream ossDate; // ostringstream is a class in the C++ Standard Library that provides a way to construct strings in a stream-like fashion.
                    ostringstream ossTime; // ossDate and ossTime are objects of ostringstream class used to store the formatted date and time strings, respectively.

                    string dateAndTime; // this variable will store the final concatenated string representing the current date and time.

                    currentTime = time(0);                       // currentTime is initialized with the current system time using the time function from the <ctime> library. time(0) returns the current time as a time_t object.
                    tm *timeNow = localtime(&currentTime);       // time(0) function is called to obtain the current time as a time_t value. localtime() is then used to convert this time_t value into a pointer to a tm structure representing the local time.
                    ossDate << put_time(timeNow, "%d-%m-%Y ");   // put_time() function is used to format the time based on the provided tm structure and format specifier.
                    ossTime << put_time(timeNow, "%I:%M %p");    // ossDate appends the formatted date using the format specifier "%d-%m-%Y " and ossTime appends the formatted time using the format specifier "%I:%M %p"
                    dateAndTime = ossDate.str() + ossTime.str(); // str() member function is used to retrieve the accumulated strings from ossDate and ossTime, concatenated together using the + operator. The resulting concatenated string is assigned to the dateAndTime variable.

                    transactionAmount[currentTransactionIndex] = currencyConvertedtoBirr;
                    transactionAccountNumber[currentTransactionIndex] = accountnumber[inputAccountIndex];
                    transactionType[currentTransactionIndex] = "Deposit";
                    transactionTime[currentTransactionIndex] = dateAndTime;

                    currentTransactionIndex++;

                    cout << "Deposit was successful" << endl;
                    cout << "Your current balance is " << balance[inputAccountIndex] << " ETB" << endl;
                }
                else
                {
                    cout << "Amount is invalid" << endl
                         << "Enter a correct amount to deposit: ";
                    goto EnterCorrectAmount;
                }

                char continuetoMenu;
                cout << "Click [Y] to return to main menu and any other key to exit the program" << endl;
                cin >> continuetoMenu;
                if (continuetoMenu == 'Y' || continuetoMenu == 'y')
                    goto menu;

                else
                    banking = false;
            }
            else
                break;
        }
        /// withdrawal from an account
        case 3:
        {
            system("cls");
            cout << "Withdaw from an account" << endl;
            int inputAccount, inputAccountIndex;
            bool isItFound = false;
            while (isItFound == false)
            {
            EnterWithdrawAgain:
                cout << " Enter the account number to withdraw from" << endl;
                cin >> inputAccount;
                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    goto EnterWithdrawAgain;
                }
                for (int i = 0; i < currentAccountIndex; i++)
                {
                    if (accountnumber[i] == inputAccount)
                    {
                        isItFound = true;
                        inputAccountIndex = i;
                        break;
                    }
                }
                if (isItFound == false)
                {
                    cout << "Account does not exist " << endl
                         << "Make sure you entered the correct account number " << endl;
                }
            }
            string inputPassword;
            bool correctPassword = false;
            int numberOfTrial = 3;
        enterThepass:
            cout << " Enter the password for your account: ";
            getline(cin.ignore(), inputPassword);
            while (correctPassword == false && numberOfTrial > 0)
            {

                for (int i = 0; i < currentAccountIndex; i++)
                {
                    if (password[i] == inputPassword)
                        correctPassword = true;
                    else
                    {
                        numberOfTrial--;
                        cout << "Incorrect password\n ";
                        if (numberOfTrial >= 1)
                        {
                            cout << numberOfTrial << " number of trials left";
                            goto enterThepass;
                        }
                        else
                            break;
                    }
                }
            }
            if (correctPassword == true)
            {
                cout << "Hello " << name[inputAccountIndex] << endl;

                double withdrawAmount;
                cout << " Enter the amount of money you want to withdraw: ";
            EnterCorrectWithdraw:
                cin >> withdrawAmount;

                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    goto EnterCorrectWithdraw;
                }

                if ((balance[inputAccountIndex] - withdrawAmount) >= 0)
                {
                    balance[inputAccountIndex] -= withdrawAmount;

                    ostringstream ossDate;
                    ostringstream ossTime;

                    string dateAndTime;

                    currentTime = time(0);
                    tm *timeNow = localtime(&currentTime);
                    ossDate << put_time(timeNow, "%d-%m-%Y ");
                    ossTime << put_time(timeNow, "%I:%M %p");
                    dateAndTime = ossDate.str() + ossTime.str();

                    transactionAmount[currentTransactionIndex] = withdrawAmount;
                    transactionAccountNumber[currentTransactionIndex] = accountnumber[inputAccountIndex];
                    transactionType[currentTransactionIndex] = "Withdrawal";
                    transactionTime[currentTransactionIndex] = dateAndTime;

                    currentTransactionIndex++;

                    cout << " Withdraw was successful" << endl
                         << " Your current balance is " << (balance[inputAccountIndex]) << endl;
                }
                else
                {
                    cout << " Your balance is insufficent for this amount of withdraw" << endl;
                    cout << " You balance is " << balance[inputAccountIndex] << endl
                         << " Enter the correct amount of withdrawal: ";
                    goto EnterCorrectWithdraw;
                }

                char continuetoMenu;
                cout << " Click [Y] to return to main menu and any other key to exit the program" << endl;
                cin >> continuetoMenu;
                if (continuetoMenu == 'Y' || continuetoMenu == 'y')
                    goto menu;

                else
                    banking = false;
            }
            else
                cout << "You have entered incorrect password too many times" << endl;
            char continuetoMenu;
            cout << " Click [Y] to return to main menu and any other key to exit the program" << endl;
            cin >> continuetoMenu;
            if (continuetoMenu == 'Y' || continuetoMenu == 'y')
                goto menu;

            else
                banking = false;
            break;
        }
        /// Transfers from one account to another
        case 4:
        {
            system("cls");
            cout << "Transfer to an account" << endl;
            int inputAccount, inputAccountIndex;
            bool isItFound = false;
        EnterCorrectTransferAcc:
            cout << "Enter the account to be transferd from " << endl;
            cin >> inputAccount;
            if (cin.fail())
            {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();                                         // Clear the error state of cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any remaining input in the buffer and defines the maximum limit of characters
                goto EnterCorrectTransferAcc;
            }

            while (isItFound == false)
            {
                for (int i = 0; i < currentAccountIndex; i++)
                {
                    if (accountnumber[i] == inputAccount)
                    {
                        isItFound = true;
                        inputAccountIndex = i;
                        break;
                    }
                }
                if (isItFound == false)
                {
                    cout << "Account does not exist " << endl
                         << "Make sure you entered the correct account number " << endl;
                    cout << "Enter the account to be transferd from " << endl;
                    cin >> inputAccount;
                }
            }

            string inputPassword;
            bool correctPassword = false;
            int numberOfTrial = 3;

            cout << "Enter the password of the account to be transferd from: ";
            getline(cin.ignore(), inputPassword);
            while (correctPassword == false && numberOfTrial > 0)
            {

                for (int i = 0; i < currentAccountIndex; i++)
                {
                    if (password[i] == inputPassword)
                        correctPassword = true;
                    else
                    {
                        numberOfTrial--;
                        cout << " Incorrect password\n ";
                        if (numberOfTrial >= 1)
                        {
                            cout << numberOfTrial << " trials left" << endl;
                            cout << "Enter the password of the account to be transferd from: ";
                            getline(cin.ignore(), inputPassword);
                        }
                        else
                            break;
                    }
                }
            }

            if (correctPassword == true)
            {

                double transferAmount;
                cout << "Hello " << name[inputAccountIndex] << endl;

                int recevierAccount, recevierAccountIndex;
                bool foundrecevierAccount = false;

                while (foundrecevierAccount == false)
                {
                EnterCorrectReciverAcc:
                    cout << "Enter the account to be transferd to: " << endl;
                    cin >> recevierAccount;

                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a number." << endl;
                        cin.clear();                                         // Clear the error state of cin
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any remaining input in the buffer and defines the maximum limit of characters
                        goto EnterCorrectReciverAcc;
                    }

                    for (int i = 0; i < currentAccountIndex; i++)
                    {
                        if (accountnumber[i] == recevierAccount)
                        {
                            foundrecevierAccount = true;
                            recevierAccountIndex = i;
                            break;
                        }
                    }
                    if (foundrecevierAccount == false)
                        cout << "Account does not exist. Make sure you entered the correct account number" << endl;
                }

            EnterCorrectTransferAmount:
                cout << "Enter the amount of money you want to transfer: ";
                cin >> transferAmount;
                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a number." << endl;
                    cin.clear();                                         // Clear the error state of cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any remaining input in the buffer and defines the maximum limit of characters
                    goto EnterCorrectTransferAmount;
                }

                if (transferAmount > 0)
                {
                    if ((balance[inputAccountIndex] - transferAmount) >= 0)
                    {
                        balance[recevierAccountIndex] += transferAmount;
                        balance[inputAccountIndex] -= transferAmount;

                        ostringstream ossDate;
                        ostringstream ossTime;

                        string dateAndTime;

                        currentTime = time(0);
                        tm *timeNow = localtime(&currentTime);
                        ossDate << put_time(timeNow, "%d-%m-%Y ");
                        ossTime << put_time(timeNow, "%I:%M %p");
                        dateAndTime = ossDate.str() + ossTime.str();

                        transactionAmount[currentTransactionIndex] = -transferAmount;
                        transactionAccountNumber[currentTransactionIndex] = accountnumber[inputAccountIndex];
                        transactionType[currentTransactionIndex] = "Transfer";
                        transactionTime[currentTransactionIndex] = dateAndTime;

                        currentTransactionIndex++;

                        transactionAmount[currentTransactionIndex] = transferAmount;
                        transactionAccountNumber[currentTransactionIndex] = accountnumber[recevierAccountIndex];
                        transactionType[currentTransactionIndex] = "Transfer";
                        transactionTime[currentTransactionIndex] = dateAndTime;

                        currentTransactionIndex++;

                        cout << "Transfer to " << name[recevierAccountIndex] << " was successful " << endl
                             << "Your current balance is " << balance[inputAccountIndex] << endl;
                    }
                    else
                    {
                        cout << "Your balance is insufficent for this amount to be transferd" << endl;
                        cout << "You balance is " << balance[inputAccountIndex] << endl;
                        goto EnterCorrectTransferAmount;
                    }
                }
                else
                    cout << "Invalid amount is input for transfer" << endl
                         << "Please check if the amount entered is correct" << endl;

                char continuetoMenu;
                cout << " Click [Y] to return to main menu and any other key to exit the program" << endl;
                cin >> continuetoMenu;
                if (continuetoMenu == 'Y' || continuetoMenu == 'y')
                    goto menu;

                else
                    banking = false;
            }
            else
                cout << "You have entered incorrect password too many times" << endl;
            char continuetoMenu;
            cout << " Click [Y] to return to main menu and any other key to exit the program" << endl;
            cin >> continuetoMenu;
            if (continuetoMenu == 'Y' || continuetoMenu == 'y')
                goto menu;

            else
                banking = false;
        }
        break;
            // view transaction record
        case 5:
        {
            system("cls");
            cout << "Transaction history" << endl;
            bool isItFound = false;
            char choice;
            cout << "For a user transaction history click [u] for adminstrator transaction log click [a]";
            cin >> choice;

            switch (choice)
            {
            case 'u':
            {
                int inputAccount, inputAccountIndex;

                while (isItFound == false)
                {
                    cout << "Enter your account number" << endl;
                    cin >> inputAccount;
                EntertransactionAcc:
                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        goto EntertransactionAcc;
                    }
                    for (int i = 0; i < currentAccountIndex; i++)
                    {
                        if (accountnumber[i] == inputAccount)
                        {
                            isItFound = true;
                            inputAccountIndex = i;
                            break;
                        }
                    }
                    if (isItFound == false)
                    {
                        cout << "Account does not exist " << endl
                             << "Make sure you entered the correct account number " << endl;
                    }
                }

                string inputPassword;
                bool correctPassword = false;
                int numberOfTrial = 3;
                cout << "Enter the password of your account " << endl;
                getline(cin.ignore(), inputPassword);

                while (correctPassword == false && numberOfTrial > 0)
                {

                    for (int i = 0; i < currentAccountIndex; i++)
                    {
                        if (password[i] == inputPassword)
                            correctPassword = true;
                        else
                        {
                            numberOfTrial--;
                            cout << "Incorrect password\n ";
                            if (numberOfTrial >= 1)
                            {
                                cout << numberOfTrial << " trials left" << endl;
                                cout << "Enter the password of your account " << endl;
                                getline(cin.ignore(), inputPassword);
                            }
                            else
                                break;
                        }
                    }
                }
                if (correctPassword == true)
                {

                    cout << "Hello " << name[inputAccountIndex] << endl
                         << "Below are your past transactions" << endl;

                    cout << "-----------------------------------------------------------------" << endl;
                    cout << left << setw(15) << "Amount (ETB)";
                    cout << left << setw(15) << "Account";
                    cout << left << setw(15) << "Type";
                    cout << left << setw(25) << "Time" << endl;

                    for (int i = 0; i < currentTransactionIndex; i++)
                    {

                        if (transactionAccountNumber[i] == accountnumber[inputAccountIndex])
                        {

                            cout << left << setw(15) << transactionAmount[i];
                            cout << left << setw(15) << transactionAccountNumber[i];
                            cout << left << setw(15) << transactionType[i];
                            cout << left << setw(25) << transactionTime[i] << endl;
                        }
                    }
                    cout << "-----------------------------------------------------------------" << endl;
                    cout << "Your current balance is " << balance[inputAccountIndex] << endl;
                }

                else
                    cout << "You have entered incorrect password too many times" << endl;

                char continuetoMenu;
                cout << " Click [Y] to return to main menu and any other key to exit the program" << endl;
                cin >> continuetoMenu;
                if (continuetoMenu == 'Y' || continuetoMenu == 'y')
                    goto menu;

                else
                    banking = false;
                break;
            }
            break;

            case 'a':
            {
                string logPassword;
                cout << "Input Administrator password";
            logagain:
                getline(cin.ignore(), logPassword);
                if (logPassword == transactionLogPassword)
                {
                    cout << "Below are the past transactions" << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                    cout << left << setw(15) << "Amount (ETB)";
                    cout << left << setw(15) << "Account";
                    cout << left << setw(15) << "Type";
                    cout << left << setw(25) << "Time" << endl;

                    for (int i = 0; i < currentTransactionIndex; i++)
                    {

                        {
                            cout << left << setw(15) << transactionAmount[i];
                            cout << left << setw(15) << transactionAccountNumber[i];
                            cout << left << setw(15) << transactionType[i];
                            cout << left << setw(25) << transactionTime[i] << endl;
                        }
                    }
                    cout << "-----------------------------------------------------------------" << endl;
                    cout << "Total Transactions: " << currentTransactionIndex << endl;

                    char continuetoMenu;
                    cout << " Click [Y] to return to main menu and any other key to exit the program" << endl;
                    cin >> continuetoMenu;
                    if (continuetoMenu == 'Y' || continuetoMenu == 'y')
                        goto menu;

                    else
                        banking = false;
                    break;
                }
                else
                    cout << "Incorrect password" << endl
                         << "try again";
                goto logagain;
            }
            }
        }
            // Edit your account information
        case 6:
        {
            system("cls");
            cout << "6. Automated payment setup" << endl;
            int inputAccount, inputAccountIndex;
            bool isItFound = false;
            int recevierAccount, recevierAccountIndex;
            bool foundrecevierAccount = false;

            cout << "Enter the account to be transferd from (automatically) " << endl;
            cin >> inputAccount;
        EnterAutoAcc:
            if (cin.fail())
            {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto EnterAutoAcc;
            }

            while (isItFound == false)
            {
                for (int i = 0; i < currentAccountIndex; i++)
                {
                    if (accountnumber[i] == inputAccount)
                    {
                        isItFound = true;
                        inputAccountIndex = i;
                        break;
                    }
                }
                if (isItFound == false)
                {
                    cout << "Account does not exist " << endl
                         << "Make sure you entered the correct account number " << endl;
                }
            }

            if (isItFound == true)
            {
                string inputPassword;
                bool correctPassword = false;
                int numberOfTrial = 3;

                cout << "Enter the password of the account to be transferd from: ";
                getline(cin.ignore(), inputPassword);
                while (correctPassword == false && numberOfTrial > 0)
                {

                    for (int i = 0; i < currentAccountIndex; i++)
                    {
                        if (password[i] == inputPassword)
                            correctPassword = true;
                        else
                        {
                            numberOfTrial--;
                            cout << " Incorrect password\n ";
                            if (numberOfTrial >= 1)
                            {
                                cout << numberOfTrial << " trials left" << endl;
                                cout << "Enter the password of the account to be transferd from: ";
                                getline(cin.ignore(), inputPassword);
                            }
                            else
                                break;
                        }
                    }
                }

                if (correctPassword == true)
                {

                    double transferAmount;
                    cout << "Hello " << name[inputAccountIndex] << endl;

                    while (foundrecevierAccount == false)
                    {
                        cout << "Enter the account to be transferd to: " << endl;
                        cin >> recevierAccount;
                    EnterAutoRecAcc:
                        if (cin.fail())
                        {
                            cout << "Invalid input. Please enter a number." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto EnterAutoRecAcc;
                        }

                        for (int i = 0; i < currentAccountIndex; i++)
                        {
                            if (accountnumber[i] == recevierAccount)
                            {
                                foundrecevierAccount = true;
                                recevierAccountIndex = i;
                                break;
                            }
                        }
                        if (foundrecevierAccount == false)
                            cout << "Account does not exist. Make sure you entered the correct account number" << endl;
                    }
                }
            }
            // Get recurring transfer details from the user
            cout << "Recurring Transfer Setup" << endl;
        EnterPaymentFreq:
            if (cin.fail())
            {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto EnterPaymentFreq;
            }
        EnterPaymentAmt:
            double moneyamount;
            cout << "Enter Payment Amount to be deducted every month: ";
            cin >> moneyamount;
            if (cin.fail())
            {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto EnterPaymentAmt;
            }
            cout << "Automatic transaction setup was successful" << endl;
            paymentAmount[currentAutoTransactionIndex] = moneyamount;
            paymentFrom[currentAutoTransactionIndex] = inputAccountIndex;
            paymentTo[currentAutoTransactionIndex] = recevierAccountIndex;
            currentAutoTransactionIndex++;

            char continuetoMenu;
            cout << " Click [Y] to return to main menu and any other key to exit the program" << endl;
            cin >> continuetoMenu;
            if (continuetoMenu == 'Y' || continuetoMenu == 'y')
                goto menu;

            else
                banking = false;
        }
        case 7:
        {
            system("cls");
            cout << "7. Edit your account" << endl;
            bool isItFound = false;

            int inputAccount, inputAccountIndex;

            while (isItFound == false)
            {
                cout << "Enter your account number" << endl;
                cin >> inputAccount;
            EntertoEdit:
                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    goto EntertoEdit;
                }
                for (int i = 0; i < currentAccountIndex; i++)
                {
                    if (accountnumber[i] == inputAccount)
                    {
                        isItFound = true;
                        inputAccountIndex = i;
                        break;
                    }
                }
                if (isItFound == false)
                {
                    cout << "Account does not exist " << endl
                         << "Make sure you entered the correct account number " << endl;
                }
            }
            string inputPassword;
            bool correctPassword = false;
            int numberOfTrial = 3;
            cout << "Enter the password of your account " << endl;
            getline(cin.ignore(), inputPassword);
            while (correctPassword == false && numberOfTrial > 0)
            {

                for (int i = 0; i < currentAccountIndex; i++)
                {
                    if (password[i] == inputPassword)
                        correctPassword = true;
                    else
                    {
                        numberOfTrial--;
                        cout << "Incorrect password\n ";
                        if (numberOfTrial >= 1)
                        {
                            cout << numberOfTrial << " number of trials left" << endl;
                            cout << "Enter the password of your account " << endl;
                            getline(cin.ignore(), inputPassword);
                        }
                        else
                            break;
                    }
                }
            }
            if (correctPassword == true)
            {
            anotherChange:
                cout << "Hello " << name[inputAccountIndex] << endl
                     << "Your current account name is: " << name[inputAccountIndex] << endl
                     << "Your current password is: " << password[inputAccountIndex] << endl;

                char editChoice;
                cout << "Enter [1] to change your account name " << endl
                     << "Enter [2] to change your account password " << endl;

                cin >> editChoice;

                if (editChoice == '1')
                {
                    system("cls");
                    cout << "Enter a new name for your account: ";
                    getline(cin.ignore(), name[inputAccountIndex]);

                    cout << "Your account has been renamed " << endl;
                    goto anotherChange;
                }
                else if (editChoice == '2')
                {
                    system("cls");
                    string temporaryPassword;
                    cout << "Enter a new password for your account: ";
                tryAgain:
                    getline(cin.ignore(), temporaryPassword);

                    if (temporaryPassword.length() < 7)
                    {
                        cout << "Password has to be a minimum of 7 characters " << endl
                             << "Enter again: ";
                        goto tryAgain;
                    }
                    else
                    {
                        password[inputAccountIndex] = temporaryPassword;
                        cout << "Your Password has been changed" << endl;
                        char continuetoMenu;
                        cout << " Click [Y] to return to main menu and any other key to exit the program" << endl;
                        cin >> continuetoMenu;
                        if (continuetoMenu == 'Y' || continuetoMenu == 'y')
                            goto menu;
                        else
                            break;
                    }
                }
            }
            else
                cout << "You have entered incorrect password too many times" << endl;

            char continuetoMenu;
            cout << " Click [Y] to return to main menu and any other key to exit the program" << endl;
            cin >> continuetoMenu;
            if (continuetoMenu == 'Y' || continuetoMenu == 'y')
                goto menu;

            else
                banking = false;
        }
        break;

            break;
        default:
        {
            cout << "Invalid choice. Please Enter a correct option" << endl;
        }
        }
    }
}