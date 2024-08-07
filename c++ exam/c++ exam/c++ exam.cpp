#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
#include <windows.h>
using namespace std;
class Human 
{
public:
    Human() {}
    Human(string n, string s) : name(n), surname(s)
    {
    }
    virtual void Showinfo() 
    {
        cout << "\n Name: " << name;
        cout << "\n Surname: " << surname;
    }
private:
    string name;
    string surname;
};
class IDCard // This class shows the association relations and stores one person value
{
private:
    string number;
    string type;
    string data;
public:
    IDCard(string n)
    {
        number = n;
        type = "No info ";
        data = "No data ";
    }
    IDCard(string n, string t)
    {
        number = n;
        type = t;
        data = " No data ";
    }
    IDCard(string n, string t, string d)
    {
        number = n;
        type = t;
        data = d;
    }
    string getNumber()
    {
        return number;
    }
    void setNumber(string n)
    {
        number = n;
    }
    string getType()
    {
        return type;
    }
    void setType(string t)
    {
        type = t;
    }
    void Showinfo()
    {
        cout << "\nData: " << data << " Type:" << type << " Number: " << number;
    }
    string Stringinfo()
    {
        string res;
        res = "\nData: " + data + " Type:" + type + " Number: " + number + "\n";
        return res;
    }
    friend bool operator== (const IDCard& p1, const IDCard& p2)
    {
        return (p1.number == p2.number) ? true : false;
    }
    friend bool operator!= (const IDCard& p1, const IDCard& p2)
    {
        return !(p1 == p2);
    }
};
class Colleague : public Human // GoF prototype?
{
public:
    Colleague(string name, string surname, IDCard* ph) : Human(name, surname)
    {
        setPhonec(ph);
    }
    ~Colleague()
    {
        cout << "Deleted";
    }
    void Showinfo()
    {
        Human::Showinfo();
        cout << "\nType: " << type;
    }
    void setPhonec(IDCard* phon)
    {
        p = phon;
    }
    IDCard getPhonec()
    {
        return *p;
    }
private:
    const string type = "Colleague";
    IDCard* p;
};

class Friend : public Human 
{
private:
    const string type = "Friend";
    IDCard* p;
public:
    Friend(string name, string surname, IDCard* ph) : Human(name, surname)
    {
        setPhonec(ph);
    }
    ~Friend()
    {
        cout << "Deleted";
    }
    void Showinfo()
    {
        Human::Showinfo();
        cout << "\nType: " << type;
    }
    void setPhonec(IDCard* phon)
    {
        p = phon;
    }
    IDCard getPhonec()
    {
        return *p;
    }

};
class Phonebook 
{
private:
    list <IDCard> masph;
    list <IDCard>::iterator iter;
    string name;
public:
    Phonebook(string n) {
        name = n;
    }
    int getSize()
    {
        return masph.size();
    }
    void addPhone(IDCard card)
    {
        masph.push_back(card);
    }
    void delPhone(IDCard card)
    {
        masph.remove(card);
    }
    void BookOut()
    {
        iter = masph.begin();
        while (iter != masph.end())
            (*iter++).Showinfo();
    }
    string BookString()
    {
        string result;
        iter = masph.begin();
        while (iter != masph.end())
            result += (*iter++).Stringinfo();
        return result;
    }
};
class Interface
{
public:
    Interface(string n)
    {
        name = n;
    }
    void InterStart()
    {
        Phonebook phbk("book");
        
        std::cout << "Phone book app\n";
        while (true) {
            cout << "\nMenu:\n" << "Print 'a' to add new contact, 's' to show contacts,'f' to save to file, 'q' to quit";
            string inp;
            getline(cin, inp);
            if (inp == "q") {
                break;
            }
            else if (inp == "a")
            {
                string name, surname, number;
                cout << "Print 'f' to add new friend, 'e' to add employee contact";
                getline(cin, inp);
                if (inp == "f")
                {
                    cout << "\nEnter name (friend): \t";
                    getline(cin, name);
                    cout << "\nEnter surname (friend): \t";
                    getline(cin, surname);
                    cout << "\nEnter number (friend): \t";
                    getline(cin, number);
                    IDCard* p = new IDCard(number, "friend", name + " " + surname);
                    Friend* f = new Friend(name, surname, p);
                    phbk.addPhone(*p);
                }
                else if (inp == "e")
                {
                    cout << "\nEnter name (employee): \t";
                    getline(cin, name);
                    cout << "\nEnter surname (employee): \t";
                    getline(cin, surname);
                    cout << "\nEnter number (employee): \t";
                    getline(cin, number);
                    IDCard* p = new IDCard(number, "Employee", name + " " + surname);
                    Colleague* e = new Colleague(name, surname, p);
                    phbk.addPhone(*p);
                }
            }
            else if (inp == "s")
            {
                phbk.BookOut();
            }
            else if (inp == "f")
            {
                ofstream fout("phonebook.txt", ios::app);
                fout << "Phonebook repository:\n" << phbk.BookString();
                fout << endl;
                fout.close();
                cout << "Phonebook copied to the file";
            }
            else
            {
                cout << "Unknown symbol, try again";
            }
        }
    }
private:
    string name;
};



int main()
{
    Interface i1("Main interface");
    i1.InterStart();
}
