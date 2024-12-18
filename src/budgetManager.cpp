#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

string getCurrentDateTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string dateTime =
    to_string(1900 + ltm->tm_year) + "-" +
    to_string(1 + ltm->tm_mon) + "-" +
    to_string(ltm->tm_mday) + " " +
    to_string(ltm->tm_hour) + ":" +
    to_string(ltm->tm_min);
    return dateTime;
}

class Transaction
{
public:
    double amount;
    string description;
    string dateTime;
    
    Transaction() : description(""), amount(0.0), dateTime("") {}
    
    void inputTransaction()
    {
        cout << "Enter Description: ";
        cin.ignore();
        getline(cin, description);
        
        cout << "Enter Amount: ";
        cin >> amount;
        
        dateTime = getCurrentDateTime();
    }
    
    void displayTransaction(int index) const
    {
        cout << left << setw(5) << index
        << setw(20) << description
        << setw(10) << amount
        << setw(20) << dateTime << endl;
    }
};

class BudgetManager
{
private:
    Transaction income[100];
    Transaction expenses[100];
    
    int incomeCount;
    int expenseCount;
    
public:
    BudgetManager() : incomeCount(0), expenseCount(0) {}
    
    void addIncome()
    {
        if(incomeCount < 100)
        {
            cout << endl << "Adding income: " << endl;
            income[incomeCount].inputTransaction();
            incomeCount++;
            
            cout << "Income added successfully" << endl;
        }
        else
        {
            cout << "Income list is full" << endl;
        }
    }
    
    void addExpense()
    {
        if(expenseCount < 100)
        {
            cout << endl << "Adding expense: " << endl;
            expenses[expenseCount].inputTransaction();
            expenseCount++;
            
            cout << "Expense added successfully" << endl;
        }
    }
    
    void displayTransactions() const
    {
        cout << endl << "--- Incomes ---" << endl;
        cout << left << setw(5) << "No" << setw(20) << "Description"
        << setw(10) << "Amount" << setw(20) << "Date & Time" << endl;
        
        for (int i = 0; i < incomeCount; i++)
        {
            income[i].displayTransaction(i + 1);
        }
        
        cout << endl << "--- Expenses ---" << endl;
        cout << left << setw(5) << "No" << setw(20) << "Description"
        << setw(10) << "Amount" << setw(20) << "Date & Time" << endl;
        
        for (int i = 0; i < expenseCount; i++)
        {
            expenses[i].displayTransaction(i + 1);
        }
    }
    
    
    void editTransaction()
    {
        int choice;
        int recordNo;
        
        cout << "Press 1 to edit income" << endl;
        cout << "Press 2 to edit expenses" << endl;
        cout << "Here : ";
        cin >> choice;
        
        if (choice == 1 && incomeCount > 0)
        {
            cout << "Enter Income Record No to Edit: ";
            cin >> recordNo;
            
            if (recordNo > 0 && recordNo <= incomeCount)
            {
                income[recordNo - 1].inputTransaction();
                cout << "Income updated successfully" << endl;
            }
            else
            {
                cout << "Invalid Record Number" << endl;
            }
        }
        
        else if(choice == 2 && expenseCount > 0)
        {
            cout << "Enter Expense Record No to Edit: ";
            cin >> recordNo;
            
            if (recordNo > 0 && recordNo <= expenseCount)
            {
                expenses[recordNo - 1].inputTransaction();
                cout << "Expense updated successfully" << endl;
            }
            else
            {
                cout << "Invalid Record Number" << endl;
            }
        }
        
        else
        {
            cout << "No records to edit" << endl;
        }
    }
    
    void deleteTransaction()
    {
        int choice;
        int recordNo;
        
        cout << "Press 1 to delete income" << endl;
        cout << "Press 2 to delete expenses" << endl;
        cout << "Here : ";
        cin >> choice;
        
        if (choice == 1 && incomeCount > 0)
        {
            cout << "Enter Income Record No to Edit: ";
            cin >> recordNo;
            
            if (recordNo > 0 && recordNo <= incomeCount)
            {
                for (int i = recordNo - 1; i < incomeCount - 1; i++)
                {
                    income[i] = income[i + 1];
                }
                
                incomeCount--;
                cout << "Income deleted successfully" << endl;
            }
        }
        
        else if(choice == 2 && expenseCount > 0)
        {
            cout << "Enter Expense Record No to Edit: ";
            cin >> recordNo;
            
            if (recordNo > 0 && recordNo <= expenseCount)
            {
                for (int i = recordNo - 1; i < expenseCount - 1; i++)
                {
                    expenses[i] = expenses[i + 1];
                }
                
                expenseCount--;
                cout << "Expense deleted successfully" << endl;
            }
        }
        
        else
        {
            cout << "Invalid record number" << endl;
        }
    }
    
    void saveToFile() const
    {
        ofstream file("budget_data.txt");
        file << incomeCount << endl;
        
        for (int i = 0; i < incomeCount; i++)
        {
            file << income[i].description << "," << income[i].amount << "," << income[i].dateTime << endl;
        }
        file << expenseCount << endl;
        
        for (int i = 0; i < expenseCount; i++)
        {
            file << expenses[i].description << "," << expenses[i].amount << "," << expenses[i].dateTime << endl;
        }
        file.close();
        
        cout << "Data saved" << endl;
    }
    
    void loadFromFile()
    {
        ifstream file("budget_data.txt");
        if (file)
        {
            file >> incomeCount;
            file.ignore();
            for (int i = 0; i < incomeCount; i++)
            {
                getline(file, income[i].description, ',');
                file >> income[i].amount;
                file.ignore();
                getline(file, income[i].dateTime);
            }
            
            file >> expenseCount;
            file.ignore();
            for (int i = 0; i < expenseCount; i++)
            {
                getline(file, expenses[i].description, ',');
                file >> expenses[i].amount;
                file.ignore();
                getline(file, expenses[i].dateTime);
            }
            
            cout << "Data loaded" << endl;
        }
        
        file.close();
    }
    
    void displayAnalytics()
    {
        double totalIncome = 0;
        double totalExpense = 0;
        
        for (int i = 0; i < incomeCount; i++)
        {
            totalIncome += income[i].amount;
        }
        
        for (int i = 0; i < expenseCount; i++)
        {
            totalExpense += expenses[i].amount;
        }
        
        cout << endl << "--- Budget Analytics ---" << endl;
        cout << "Total Incomes: $" << totalIncome << endl;
        cout << "Total Expenses: $" << totalExpense << endl;
        cout << "Savings: $" << totalIncome - totalExpense << endl;
    }
};

int main()
{
    BudgetManager manager;
    manager.loadFromFile();
    int choice = 0;

    do {
        cout << endl << "--- Personal Budget Manager ---" << endl;
        cout << "1. Add income" << endl;
        cout << "2. Add expense" << endl;
        cout << "3. View Transactions" << endl;
        cout << "4. Edit a Transaction" << endl;
        cout << "5. Delete a Transaction" << endl;
        cout << "6. View Analytics" << endl;
        cout << "7. Save and Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Enter a number1" << endl;
            continue;
        }

        switch (choice)
        {
            case 1: manager.addIncome(); break;
            case 2: manager.addExpense(); break;
            case 3: manager.displayTransactions(); break;
            case 4: manager.editTransaction(); break;
            case 5: manager.deleteTransaction(); break;
            case 6: manager.displayAnalytics(); break;
            case 7: manager.saveToFile(); break;
            default: cout << "Invalid, try again." << endl;
        }
    } while (choice != 7);
    return 0;
}
