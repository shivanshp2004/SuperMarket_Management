#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;
struct bill
{
    string name;
    int quantity, price;
    bill(string n, int q, int p)
    {
        this->name = n;
        this->quantity = q;
        this->price = p;
    }
    bill() {}
};
bool check(string s)
{
    for (int i = 0; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}
// EXCEPTION HANDLING
class store{
    public:
    string name;
    string squantity, sprice, satleast;
    int quantity{}, weight{}, price{}, atleast{};
    static vector<store *> storage;
    static vector<bill *> b;
void add_item(bool &flagy)
    {
        bool flag = false;
        cout << "Enter Product Name : ";
        // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, this->name);
        string testname = this->name;
        testname.erase(remove_if(testname.begin(), testname.end(), ::isspace), testname.end());
        transform(testname.begin(), testname.end(), testname.begin(), ::toupper);
        for (auto i : store ::storage)
        {
            string iname = i->name;
            iname.erase(remove_if(iname.begin(), iname.end(), ::isspace), iname.end());
            transform(iname.begin(), iname.end(), iname.begin(), ::toupper);
            if (iname == testname)
            {
                cout << "\nITEM ALREADY IN STORE, TRY UPDATING INSTEAD !!!\n\n";
                return;
            }
        }
        cout << "Enter Product Price : ";
        getline(cin, this->sprice);
        while (!check(sprice))
        {
            cout << endl
                 << "Invalid Input" << endl
                 << endl;
            cout << "Enter Price Again : ";
            getline(cin, this->sprice);
            cout << endl;
        }
        this->price = stoi(sprice);
        cout << "\nNOTE : IF ITEM IS NOT COUNTABLE THEN AUTOMATICALLY IT WILL BE CONSIDERED WITH SUITABLE WEIGHT(kg or l), PROVIDE QUANTITY IN INTEGER\n";
        cout << "Enter Product Quantity : ";
        // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, this->squantity);
        while (!check(squantity))
        {
            cout << endl
                 << "Invalid Input" << endl
                 << endl;
            cout << "Enter Quantity Again : ";
            getline(cin, this->squantity);
            cout << endl;
        }
        this->quantity = stoi(squantity);
        cout << "Demanded Min. Quantity in Stock must be :  ";
        // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, this->satleast);
        while (!check(satleast))
        {
            cout << endl
                 << "Invalid Input" << endl
                 << endl;
            cout << "Enter Demanded Min. Quantity Again : ";
            getline(cin, this->satleast);
            cout << endl;
        }
        this->atleast = stoi(satleast);
        flagy = true;
        cout << "\nPRODUCT ADDED SUCCESSFULLY !!!\n";
    }

    // UPDATE ITEMS

    void update_item()
    {
        string item_name;
        cout << "Name of Item which you want to Update : ";
        getline(cin, item_name);
        item_name.erase(remove_if(item_name.begin(), item_name.end(), ::isspace), item_name.end());
        transform(item_name.begin(), item_name.end(), item_name.begin(), ::toupper);
        cout << "________________________________________________________\n";
        cout << "|                                                       |\n";
        cout << "|         1. Change Name                                |" << endl;
        cout << "|         2. Change Quantity                            |" << endl;
        cout << "|         3. Change Price                               |" << endl;
        cout << "|         4. Change Demanded Min. Quantity in Stock     |" << endl;
        cout << "|_______________________________________________________|\n";
        cout << "--------------------------------------------------------------\n";
        cout << "\nNOTE : IF ITEM IS NOT COUNTABLE THEN AUTOMATICALLY IT WILL BE CONSIDERED WITH SUITABLE WEIGHT(kg or l), PROVIDE QUANTITY IN INTEGER\n";
        cout << "Enter the choice : ";
        string schoice;
        int choice;
        getline(cin, schoice);
        while (!check(schoice))
        {
            cout << endl
                 << "Invalid Input" << endl
                 << endl;
            cout << "Enter Choice Again : ";
            getline(cin, this->squantity);
            cout << endl;
        }
        choice = stoi(schoice);
        bool flag = false;
        switch (choice)
        {
        case 1:
            change_name(item_name, flag);
            break;
        case 2:
            change_quantity(item_name, flag);
            break;
        case 3:
            change_price(item_name, flag);
            break;
        case 4:
            change_minreq(item_name, flag);
            break;
        default:
            cout << "Invalid choice." << endl;
        }
        if (flag)
            cout << "\n UPDATE COMPLETED SUCCESSFULLY !!!\n";
        else
            cout << "\n ITEM NOT FOUND, UPDATE FAILED !!!\n";
    }

    // SHOW STORE

    static void show_store()
    {
        const int nameWidth = 20;
        const int priceWidth = 7;
        const int quantityWidth = 10;

        cout << "  " << setw((nameWidth - 6) / 2) << "ITEMS" << setw((nameWidth + 6) / 2) << "  "
             << right << setw(priceWidth) << "PRICE" << right << setw(quantityWidth) << "QUANTITY" << endl;

        cout << "  " << setfill('-') << setw(nameWidth + priceWidth + quantityWidth + 7) << "" << setfill(' ') << endl;

        for (store *i : store::storage)
        {
            string checki;
            for (int j = 0; j < i->name.size(); j++)
                checki += toupper(i->name[j]);
            cout << "  " << left << setw(nameWidth) << checki
                 << right << setw(priceWidth) << fixed << setprecision(2) << i->price
                 << right << setw(quantityWidth) << i->quantity << endl;
        }
    }

    // DEMAND LIST

    static void demand_list()
    {
        bool flag = false;
        for (store *i : store::storage)
        {
            if (i->quantity >= i->atleast)
                continue;
            cout << i->name << " : " << i->atleast - i->quantity << endl;
            flag = true;
        }
        if (!flag)
            cout << "\n DEMAND LIST IS EMPTY !!!\n";
    }

    // UPDATE- CHANGE NAME

    void change_name(string uname, bool &flag)
    {
        string nname;
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter New Name : ";
        getline(cin, nname);
        // cin.clear();
        for (auto i : store ::storage)
        {
            string check = i->name;
            check.erase(remove_if(check.begin(), check.end(), ::isspace), check.end());
            transform(check.begin(), check.end(), check.begin(), ::toupper);
            if (check == uname)
            {
                i->name = nname;
                flag = true;
                break;
            }
        }
    }

    // UPDATE - CHANGE WEIGHT

    void change_weight(string uname, bool &flag)
    {
        string snweight;
        int nweight;
        cout << "Enter new Weight : ";
        getline(cin, snweight);
        while (!check(snweight))
        {
            cout << endl
                 << "Invalid Input" << endl;
            cout << "Enter Weight Again : ";
            getline(cin, snweight);
            cout << endl;
        }
        nweight = stoi(snweight);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (auto i : store ::storage)
        {
            string check = i->name;
            check.erase(remove_if(check.begin(), check.end(), ::isspace), check.end());
            transform(check.begin(), check.end(), check.begin(), ::toupper);
            if (check == uname)
            {
                i->weight = nweight;
                flag = true;
                break;
            }
        }
    }

    // UPDATE- CHANGE QUANTITY

    void change_quantity(string uname, bool &flag)
    {
        string snquantity;
        int nquantity;
        cout << "Enter new Quantity : ";
        getline(cin, snquantity);
        while (!check(snquantity))
        {
            cout << endl
                 << "Invalid Input" << endl;
            cout << "Enter Quantity Again : ";
            getline(cin, snquantity);
            cout << endl;
        }
        nquantity = stoi(snquantity);
        for (auto i : store ::storage)
        {
            string check = i->name;
            check.erase(remove_if(check.begin(), check.end(), ::isspace), check.end());
            transform(check.begin(), check.end(), check.begin(), ::toupper);
            if (check == uname)
            {
                i->quantity = nquantity;
                flag = true;
                break;
            }
        }
    }

    // UPDATE- CHANGE PRICE

    void change_price(string uname, bool &flag)
    {
        int nprice;
        string snprice;
        cout << "Enter new Price : ";
        getline(cin, snprice);
        while (!check(snprice))
        {
            cout << endl
                 << "Invalid Input" << endl;
            cout << "Enter Price Again : ";
            getline(cin, snprice);
            cout << endl;
        }
        nprice = stoi(snprice);
        for (auto i : store ::storage)
        {
            string check = i->name;
            check.erase(remove_if(check.begin(), check.end(), ::isspace), check.end());
            transform(check.begin(), check.end(), check.begin(), ::toupper);
            if (check == uname)
            {
                i->price = nprice;
                flag = true;
                break;
            }
        }
    }

    // UPDATE- CHANGE MIN. REQUIREMENT

    void change_minreq(string uname, bool &flag)
    {
        int nminr;
        string snminr;
        cout << "Enter New Min. Requirement : ";
        getline(cin, snminr);
        while (!check(snminr))
        {
            cout << endl
                 << "Invalid Input" << endl;
            cout << "Enter Min. Requirement Again : ";
            getline(cin, snminr);
            cout << endl;
        }
        nminr = stoi(snminr);
        for (auto i : store ::storage)
        {
            string check = i->name;
            check.erase(remove_if(check.begin(), check.end(), ::isspace), check.end());
            transform(check.begin(), check.end(), check.begin(), ::toupper);
            if (check == uname)
            {
                i->atleast = nminr;
                flag = true;
                break;
            }
        }
    }

    // PURCHASE ITEM

    void purchaseitem()
    {
        string iname;
        cout << "Enter the name of Product : ";
        getline(cin, iname);
        iname.erase(remove_if(iname.begin(), iname.end(), ::isspace), iname.end());
        transform(iname.begin(), iname.end(), iname.begin(), ::toupper);
        int quant;
        string squant;
        cout << "Enter Quantity : ";
        getline(cin, squant);
        while (!check(squant))
        {
            cout << endl
                 << "Invalid Input" << endl
                 << endl;
            cout << "Enter Quantity Again : ";
            getline(cin, squant);
            cout << endl;
        }
        quant = stoi(squant);
        bool flag = false;
        for (auto i : storage)
        {
            string checki = i->name;
            checki.erase(remove_if(checki.begin(), checki.end(), ::isspace), checki.end());
            transform(checki.begin(), checki.end(), checki.begin(), ::toupper);
            if (checki == iname)
            {
            A:
                cout << "\nYou are buying \"" << i->name << "\" at Rs." << i->price * quant << endl;
                cout << "Continue ? " << endl;
                cout << "1.Yes \n2.No \n";
                cout << "Enter Choice : ";
                flag = true;
                string sch;
                int ch;
                getline(cin, sch);
                while (!check(sch))
                {
                    cout << endl
                         << "Invalid Input" << endl
                         << endl;
                    cout << "Enter Choice Again : ";
                    getline(cin, sch);
                    cout << endl;
                }
                ch = stoi(sch);
                switch (ch)
                {
                case 1:
                {
                    if (quant > i->quantity)
                    {
                        cout << "\nSorry,Out of Stock !!" << endl;
                        break;
                    }
                    cout << "\nItem Bought !!" << endl;
                    bill *billy = new bill(i->name, quant, i->price * quant);
                    b.push_back(billy);
                    i->quantity -= quant;
                    break;
                }
                case 2:
                {
                    cout << "Purchase Cancelled !!";
                    break;
                }
                default:
                {
                    cout << "\nInvalid Input\n\n ";
                    goto A;
                };
                }
            }
        }
        if (!flag)
            cout << "\n ITEM NOT FOUND, PURCHASE CANCELLED !!!\n\n";
    }
    void show_bill()
    {
        if (b.size() == 0)
        {
            cout << "\nYOU HAVEN'T BOUGHT ANYTHING\n\n";
            return;
        }
        const int nameWidth = 20;
        const int priceWidth = 7;
        const int quantityWidth = 10;

        cout << "  " << setw((nameWidth - 6) / 2) << "ITEMS" << setw((nameWidth + 6) / 2) << "  "
             << right << setw(priceWidth) << "PRICE" << right << setw(quantityWidth) << "QUANTITY" << endl;

        cout << "  " << setfill('-') << setw(nameWidth + priceWidth + quantityWidth + 7) << "" << setfill(' ') << endl;
        int total = 0;
        for (bill *i : store::b)
        {
            cout << "  " << left << setw(nameWidth) << i->name
                 << right << setw(priceWidth) << fixed << setprecision(2) << i->price
                 << right << setw(quantityWidth) << i->quantity << endl;
            total += i->price;
        }
        cout << "\n TOTAL : " << total << "\n\n";
    }

};

vector<store *> store::storage;
vector<bill *> store::b;
// FILE HANDLING

void remove_item()
    {
        string iname;
        cout << "Enter the name of Product : ";
        getline(cin, iname);
        iname.erase(remove_if(iname.begin(), iname.end(), ::isspace), iname.end());
        transform(iname.begin(), iname.end(), iname.begin(), ::toupper);
        bool flag=false;
        for (auto i=store::storage.begin();i!=store::storage.end();i++)
        {
            string checki = (*i)->name;
            checki.erase(remove_if(checki.begin(), checki.end(), ::isspace), checki.end());
            transform(checki.begin(), checki.end(), checki.begin(), ::toupper);
            if (checki == iname)
            {store::storage.erase(i);
            flag=true;
            break;
            }}
            if(flag)
            {
                cout<<"\nITEM REMOVED \n\n";
            }
            else cout<<"\nITEM NOT FOUND\n\n";
    }
void outputToFile(string s)
{
    ofstream fout{s, ios::out | ios::trunc};
    for (auto i : store ::storage)
    {
        fout << i->name << ' ' << i->price << ' ' << i->quantity << ' ' << i->atleast << ' ' << '\n';
    }
}

void outputToBill(string s)
{
    ofstream fout{s, ios::out | ios::trunc};
    if (store::b.size() == 0)
    {
        fout << "\nYOU HAVEN'T BOUGHT ANYTHING\n\n";
        return;
    }
    const int nameWidth = 20;
    const int priceWidth = 7;
    const int quantityWidth = 10;

    fout << "  " << setw((nameWidth - 6) / 2) << "ITEMS" << setw((nameWidth + 6) / 2) << "  "
         << right << setw(priceWidth) << "PRICE" << right << setw(quantityWidth) << "QUANTITY" << endl;

    fout << "  " << setfill('-') << setw(nameWidth + priceWidth + quantityWidth + 7) << "" << setfill(' ') << endl;
    int total = 0;
    for (bill *i : store::b)
    {
        fout << "  " << left << setw(nameWidth) << i->name
             << right << setw(priceWidth) << fixed << setprecision(2) << i->price
             << right << setw(quantityWidth) << i->quantity << endl;
        total += i->price;
    }
    fout << "\n TOTAL : " << total << "\n\n";
}
void inputFromFile(string s)
{
    std::ifstream fin{s};
    if (!fin)
    {
        cout << "Error: input.txt could not open for reading.\n";
        return;
    }
    string name;
    int price;
    int quantity, atleast;
    while (fin >> name >> quantity >> price >> atleast)
    {
        store *p = new store;
        p->name = name;
        p->quantity = quantity;
        p->price = price;
        p->atleast;
        store::storage.push_back(p);
    }
}
int main()
{
    cout << "********************************************************************************" << endl;
    cout << "*                                                                              *" << endl;
    cout << "*                        WELCOME TO SUPERMARKET MANAGEMENT                     *" << endl;
    cout << "*                                                                              *" << endl;
    cout << "********************************************************************************" << endl;
    cout << endl
         << endl;
    inputFromFile("output.txt");
    while (1)
    {
        int mainchoice;
        string smainchoice;
        cout << "Who are You ? (CHOOSE ONE) \n";
        cout << "______________________________" << endl;
        cout << "|                             |\n";
        cout << "|        1.Seller             |\n";
        cout << "|        2.Customer           |\n";
        cout << "|        3.Exit               |\n";
        cout << "|_____________________________|\n";
        cout << "-------------------------------\n";
        cout << "Enter Choice : ";
        getline(cin, smainchoice);
        while (!check(smainchoice))
        {
            cout << endl
                 << "Invalid Input" << endl
                 << endl;
            cout << "Enter Choice Again : ";
            getline(cin, smainchoice);
            cout << endl;
        }
        mainchoice = stoi(smainchoice);
        cout << endl;
        if (mainchoice == 3)
        {
            cout << "\nTHANK YOU !!!\n\n";
            break;
        }
        switch (mainchoice)
        {
        case 1:
        {
            while (1)
            {
                string schoice;
                cout << " _____________________________________\n";
                cout << "|                                     |\n";
                cout << "|        1.Add item                   |" << endl;
                cout << "|        2.Update item                |" << endl;
                cout << "|        3.Show Store                 |" << endl;
                cout << "|        4.Demand List                |" << endl;
                cout << "|        5.Remove Item                |" << endl;
                cout << "|        6.Return to Main Menu        |" << endl;
                cout << "|_____________________________________|" << endl;
                cout << "--------------------------------------" << endl
                     << endl;
                cout << "Enter the Choice : ";
                getline(cin, schoice);
                while (!check(schoice))
                {
                    cout << endl
                         << "Invalid Input" << endl
                         << endl;
                    cout << "Enter Choice Again : ";
                    getline(cin, schoice);
                    cout << endl;
                }
                int choice = stoi(schoice);
                cout << endl;
                if (choice == 6)
                    break;
                store *s = new store;
                bool flag = false;
                switch (choice)
                {
                case 1:
                {
                    s->add_item(flag);
                    if (flag)
                        store::storage.push_back(s);
                    outputToFile("output.txt");

                    break;
                }
                case 2:
                    s->update_item();
                    break;
                case 3:
                    store::show_store();
                    break;
                case 4:
                    store::demand_list();
                    break;
                    case 5:
                    {
                        remove_item();
                        break;
                    }
                default:
                    cout << "\n INVALID CHOICE \n \n";
                }
                cout << endl;
            }
            break;
        }
        case 2:
        {
            while (1)
            {
                string schoice;
                cout << "_____________________________________\n";
                cout << "|                                    |\n";
                cout << "|        1.Show Store                |\n";
                cout << "|        2.Purchase Item             |" << endl;
                cout << "|        3.Show Bill                 |" << endl;
                cout << "|        4.Return to Main Menu       |" << endl;
                cout << "|____________________________________|" << endl;
                cout << "---------------------------------------\n";
                cout << "Enter the Choice : ";
                getline(cin, schoice);
                while (!check(schoice))
                {
                    cout << endl
                         << "Invalid Input" << endl
                         << endl;
                    cout << "Enter Choice Again : ";
                    getline(cin, schoice);
                    cout << endl;
                }
                int choice = stoi(schoice);
                cout << endl;
                if (choice == 4)
                    break;
                store *s = new store;
                bool flag = false;
                string sch;
                int ch;
                switch (choice)
                {
                case 1:
                    store::show_store();
                    break;
                case 2:
                    s->purchaseitem();
                    break;
                case 3:
                    s->show_bill();
                B:
                    cout << endl
                         << endl
                         << "Do you want Bill to be saved in a text file ? " << endl;
                    cout << "1.Yes \n2.No \n";
                    cout << "Enter Choice : ";

                    getline(cin, sch);
                    while (!check(sch))
                    {
                        cout << endl
                             << "Invalid Input" << endl
                             << endl;
                        cout << "Enter Choice Again : ";
                        getline(cin, sch);
                        cout << endl;
                    }
                    ch = stoi(sch);
                    if (ch != 1 && ch != 2)
                    {
                        cout << "\nInvalid Input\n\n";
                        goto B;
                    }
                    switch (ch)
                    {
                    case 1:
                    {
                        outputToBill("bill.txt");
                        cout << "\nSaved !! \n\n";
                        break;
                    }
                    case 2:
                    {
                        cout << "\nNot Saved\n\n";
                        break;
                    }
                    }
                    break;
                default:
                    cout << "\n INVALID CHOICE \n \n";
                }
                cout << endl;
            }
            break;
        }
        default:
            cout << "INVALID INPUT" << endl
                 << endl;
        }
    }
    outputToFile("output.txt");
}