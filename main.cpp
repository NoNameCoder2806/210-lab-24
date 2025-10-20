// COMSC-210 | Lab 24 | Dat Hoang Vien
// IDE used: Visual Studio Code

// Libraries
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
using namespace std;

// Constants
const int MIN_CHOICE = 1;
const int MAX_CHOICE = 4;
const int SIZE_NAMES = 200;
const int SIZE_COLORS = 25;
const int MAX_AGE = 20;
const string NAMES_PATH = "names.txt";
const string COLORS_PATH = "colors.txt";

// Function prototypes
int main_menu();
void add_goat(set<Goat> &trip, string names[], string colors[]);
void delete_goat(set<Goat> &trip);
int select_goat(set<Goat> trip);
void display_trip(set<Goat> trip);

// Main function
int main()
{
    // Call srand() and time() to generate a seed
    srand(time(0));

    // Create a Goat set
    set<Goat> trip;

    // Create some variables
    bool again = true;        // Loop the program
    int i = 0;                // An int counter

    // Create arrays for names and colors
    string names[SIZE_NAMES];
    string colors[SIZE_COLORS];

    // Read and populate array for names
    ifstream fin(NAMES_PATH);
    while (fin >> names[i++]);
    fin.close();

    // Reset the i counter
    i = 0;

    // Read and populate array for colors
    ifstream fin1(COLORS_PATH);
    while (fin1 >> colors[i++]);
    fin1.close();

    // Create a loop to run the program
    while (true)
    {
        // Prompt the user to select the operation
        int operation = main_menu();

        // Perform the operation
        switch(operation)
        {
            // Add a Goat into the trip
            case 1: 
            {
                // Call add_goat()
                add_goat(trip, names, colors);

                break;
            }

            // Delete a Goat from the trip
            case 2:
            {
                // Call delete_goat()
                delete_goat(trip);

                break;
            }

            // Display the Goat set / trip
            case 3:
            {
                // Call display_trip()
                display_trip(trip);

                break;
            }

            // Exit the program
            case 4:
            {
                // Display a message
                cout << "Thank you for using the program!" << endl;
                cout << "--- Exiting... ---" << endl;

                // Exit the main function
                return 0;
            }
        }
    }

    return 0;
}

// Function implementations
/*
    main_menu()
    Display the menu of operations the user can implement on the set
    Arguments: none
    Return: 
        - the user's operation choice (between 1 and 4)
*/
int main_menu()
{
    // Declare an int to store user's choice
    int choice;

    // Display the options for the user
    cout << "*** Goat Manager 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;

    // Let user input their choice and store it in the choice variable
    cout << "Choice --> ";
    cin >> choice;
    cin.ignore(1000, 10);

    // Validate the input
    while (choice < MIN_CHOICE || choice > MAX_CHOICE)
    {
        // Display an error message
        cout << "--- Invalid! Your choice must be between 1 and 4! ----" << endl;

        // Prompt the user to enter a new choice
        cout << "New choice --> ";
        cin >> choice;
        cin.ignore(1000, 10);
    }

    // Return the user's choice
    return choice;
}

/*
    add_goat()
    Add a Goat object into the Goat set (trip)
    Arguments:
        - trip: the set of Goat objects (passed by reference)
        - names: an array containing all the Goat names (passed by value)
        - colors: an array containing all the Goat colors (passed by value)
    Return: none
*/
void add_goat(set<Goat>& trip, string names[], string colors[])
{
    // Create 3 variables as the Goat object's member variables
    string n = names[rand() % SIZE_NAMES];
    string c = colors[rand() % SIZE_COLORS];
    int a = rand() % (MAX_AGE + 1);

    // Create a temporary Goat object using the parameter Constructor
    Goat temp(n, a, c);

    // Add the Goat object to the trip
    trip.insert(temp);

    // Display a message
    cout << "--- Added ";
    temp.print();
    cout << " to the Goat trip! ---" << endl;

    // Enter a new line
    cout << endl;
}

/*
    delete_goat()
    Delete a Goat object from the Goat set (trip)
    Arguments:
        - trip: the set of Goat objects (passed by reference)
    Return: none
*/
void delete_goat(set<Goat> &trip)
{
    // Create variables to get the user's choices
    int goatChoice = select_goat(trip);
    char c;

    // Display confirmation message
    cout << "Are you sure? (Y/N): ";
    cin >> c;
    cin.ignore(1000, 10);

    // Validate the input
    while (toupper(c) != 'Y' && toupper(c) != 'N')
    {
        // Display an error message
        cout << "--- Invalid! Please enter a valid choice (Y/N): ";
        cin >> c;
        cin.ignore(1000, 10);
    }

    // If user no longer wants to delete the Goat object
    if (toupper(c) == 'N')
    {
        // Enter a new line (for formatting purposes)
        cout << endl;

        return;        // Exit the function
    }
    else
    {
        // Create a counter
        int i = 0;

        // Iterate thourgh the set and delete the Goat
        for (auto it : trip)
        {
            // Compare i with the selected Goat index
            if (goatChoice == i + 1)        // If the index matches
            {
                // Delete the Goat object from the set / trip
                trip.erase(it);

                // Display a message
                cout << "--- Goat number [" << goatChoice << "] is deleted! ---" << endl;
                cout << endl;

                // Exit the function
                return;
            }
            else                            // Otherwise
            {
                // Increment the counter
                i++;
            }
        }
    }
}

/*
    select_goat()
    Allow user to select a Goat object from the trip
    Arguments:
        - trip: the set of Goat objects (passed by value)
    Return:
        - the index of the Goat in the set
*/
int select_goat(set<Goat> trip)
{
    // Create a variable to get the user's choice
    int position = 0;

    // Display the Goat trip using display_trip()
    display_trip(trip);

    // Prompt the user to enter their choice
    cout << "- Please select a Goat: ";
    cin >> position;
    cin.ignore(1000, 10);

    // Validate user's input
    while (position < 1 || position > trip.size())
    {
        // Display an error message
        cout << "--- Invalid! Please select a Goat in the set! ---" << endl;

        // Prompt the user to enter the choice again
        cout << "- Please select a Goat: ";
        cin >> position;
        cin.ignore(1000, 10);
    }

    // Return the Goat's position
    return position;
}

/*
    display_trip()
    Display the whole Goat set
    Arguments: 
        - trip: the set of Goat objects (passed by value)
    Return: none
*/
void display_trip(set<Goat> trip)
{
    // Display a header
    cout << "--- Current Goat trip ---" << endl;
    
    // Create a counter
    int count = 0;

    // Iterate through the Goat set
    for (auto it : trip)
    {
        // Display the Goat object
        cout << "    [" << count + 1 << "] ";        // The index
        it.print();                                 // The print() member function
        cout << endl;                                // Enter a new line

        // Increment the counter
        count++;
    }

    // Enter a new line
    cout << endl;
}