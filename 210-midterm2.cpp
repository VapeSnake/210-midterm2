#include <iostream>
#include <vector> // Will be used to store names.
#include <string>
#include <fstream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList
{
private:
    struct Node
    {
        string name; // Change int to string to store names.
        Node *prev;
        Node *next;
        Node(string na, Node *p = nullptr, Node *n = nullptr)
        {
            name = na; // Initialize name instead of data.
            prev = p;
            next = n;
        }
    };

    Node *head;
    Node *tail;

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void insert_after(string name, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node *newNode = new Node(name);
        if (!head)
        {
            head = tail = newNode;
            return;
        }

        Node *temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp)
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string name)
    {
        if (!head)
            return;

        Node *temp = head;

        while (temp && temp->name != name)
            temp = temp->next;

        if (!temp)
            return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos)
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1)
        {
            pop_front();
            return;
        }

        Node *temp = head;

        for (int i = 1; i < pos; i++)
        {
            if (!temp)
            {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp)
        {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next)
        {
            pop_back();
            return;
        }

        Node *tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string name)
    {
        Node *newNode = new Node(name);
        if (!tail)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(string name)
    {
        Node *newNode = new Node(name);
        if (!head)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front()
    {

        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        Node *temp = head;

        if (head->next)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back()
    {
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = tail;

        if (tail->prev)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print()
    {
        Node *current = head;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        cout << "resulting line: "; // Moved here to print before the loop to avoid printing it multiple times.
        while (current)
        {
            cout << current->name << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse()
    {
        Node *current = tail;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->name << " ";
            current = current->prev;
        }
        cout << endl;
    }
}; // Updated all functions to work with strings instead of ints.

int main()
{
    srand(time(0));                                          // Seed the random number generator
    int randomNum = rand() % (MAX_NR - MIN_NR + 1) + MIN_NR; // Generate random number between 10 and 99

    vector<string> names; // Creates vector that stores names from file.
    ifstream inFile("names.txt");
    if (!inFile)
    {
        cerr << "Unable to open file names.txt" << endl;
        return 1; // Exit with error code
    }
    string name;
    while (getline(inFile, name))
    {
        names.push_back(name);
    }
    inFile.close();

    // Create a doubly linked list named customerList. We will start with 5 customers with random names from the file
    // in our first minute.
    cout << "Store opens: " << endl;
    DoublyLinkedList customerList;
    for (int i = 0; i < 5; i++)
    {
        int randomIndex = rand() % names.size();                            // Get a random index for the names vector
        customerList.push_back(names[rand() % names.size()]);               // Add a random name to the customer list
        cout << names[rand() % names.size()] << " joins the line." << endl; // Print the name of the customer entering the store
    }
    customerList.print(); // Print the initial list of customers

    // We can use a loop to simulate periods 2-20.
    for (int minute = 2; minute <= 20; minute++)
    {
        cout << "Minute " << minute << ": " << endl;
        int prob = rand() % 100 + 1; // Generate a random number between 1 and 100 to determine the event
    }

    return 0;
}
