/*
Description: Using structs to run a program to check for seats and 
make venue selction using a file input. Program usues 2d arrays
and functions chechking for error.    
Input:The file input is prompted and the user is asked for make 
selctions on seat and venue of choice. I addition to selceting if 
they would like to continue witht he burcheses   
Output: The out put would be responds to booking seats and a reciet 
shwoing the soldout shows as well as the total cost of the tickets
including a list of the venue. 
*/
#include <iostream>
#include <iomanip> //library for parametric manipulators 
#include <fstream>//library for file stream 
#include <string>//strings libraray 
#include <cstdlib>
#include <algorithm>//library to run algorithmes 
using namespace std;
//global const 
const int VENUES = 8;
const int SEATS = 5;
//intilizing struct 
struct venueType
{
    string name;
    bool available[SEATS];
    double cost[SEATS];
};
//prototype functions 
void populateLists(ifstream &, venueType v[]);
void outputShows(const venueType v[]);
bool anyAvailableSeats(const venueType v[]);
int validateChoice(const venueType v[], string s);
double bookSeat(venueType v[], int venueIndex, char seatNumber);
string allCaps(string str);

int main()
{
    //declaration of struct variable 
    venueType venue[VENUES];
    //file stream intilixation 
    ifstream iFile;
    //declaration of files 
    string file;
    string data;
    string choice;
    //declaration of varaiables 
    char seatNumber = ' ';
    char answer = '\0';
    bool repeat = true;
    double totalCost = 0.0;
    const int eMax = 100;
    //print welcome stament 
    cout << endl;
    cout << "Welcome To The Grand Opening\n";
    do
    { // do while loop to read in correct file 
        cout << "Enter data file: ";
        cin >> file;
        iFile.open(file);
        //file check/open 
        if (!iFile.is_open())
        {
            iFile.clear();
            iFile.ignore(eMax, '\n');
            continue;
        }
        
        break;
    } while (true);
    //function to bring out menue 
    populateLists(iFile, venue);

    do
    {
        //function to check seats that are avaliable 
        anyAvailableSeats(venue);
        cout << endl;
        //stament to print 
        cout << "Welcome Patron, please choose a show\n";
        cout << "Here are our available shows, they fill up quickly so act fast\n";
        cout << endl;
        //function that prints avaliable seats and sold seats with an x 
        outputShows(venue);
        cout << endl;
        int foundIndex = -1;
        //to selcet venue based on the menue 
        while (foundIndex < 0)
        {
            cout << "Make your selection: ";
            cin >> choice;

            foundIndex = validateChoice(venue, choice);
        }
        cout << endl;
        //selceting the proper venue 
        cout << venue[foundIndex].name << " is an excellent choice!\n";
        cout << endl; 
        double costOfOneShow = 0.0;
        //loop selecting which seats to burches based on functions 
        while (costOfOneShow == 0.0)
        {
            cout << "Any particular seat or do you want to go with the cheapest seat? ";
            cin >> seatNumber;
            costOfOneShow = bookSeat(venue, foundIndex, seatNumber);
        }
        //total cost of seats to be calculated based of selction 
        cout << "Seat booked\n";
        totalCost += costOfOneShow;
        cout << endl; 
        do{
            //do..while asking for program to end or continue 
            cout << "Wish to continue? (Y/N): ";
            cin >> answer; // build fucntion to check if y/n then loop if Y/y

            if (answer == 'y' || answer == 'Y')
            {
                repeat = true;

            }
            else if (answer == 'n' || answer == 'N')
            {
                repeat = false;
            }
            //parameters for user inout 
        }while(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N'); 
        //if statment to make sure seats are sold out or not 
        if(anyAvailableSeats(venue) == false){
            cout << "Sold Out\n";
            break; 
        }
        //loop to keep the program going 
    } while (repeat);
        //print statment with total cost 
    cout << "\nMoney made $ " << totalCost;
    cout << "\nNow it\'s time to leave before Mr. Crocker finds out!\n";
    //closing the file 
    iFile.close(); 
    return 0;
}
//function to read the input file and set to struct 
void populateLists(ifstream &iFile, venueType v[VENUES])
{

    for (int i = 0; i < VENUES; i++)
    {
        iFile >> v[i].name;
        for (int j = 0; j < SEATS; j++)
        {
            v[i].available[j] = true;
            iFile >> v[i].cost[j];
        }
    }
}
//function to check if seats are avaliable 
bool anyAvailableSeats(const venueType v[])
{

    for (int i = 0; i < VENUES; i++)
    {
        for (int j = 0; j < SEATS; j++)
        {
            if (v[i].available[j])
                return true;
        }
    }
    return false;
}
//function to output menue with selection 
void outputShows(const venueType v[])
{
    bool venueSoldOut = false; 
    //header for the meanue 
    cout << left << setw(30) << "VENUES";
    for (int i = 0; i < SEATS; i++)
    {
        cout << right << setw(7) << i + 1;
    }
    cout << endl;
    //prinitng the venue name 
    for (int i = 0; i < VENUES; i++)
    {
            venueSoldOut = false;
            //checking if seats has already been selceted 
            for(int k = 0; k < SEATS; k++){
        
                if (v[i].available[k]){
                    venueSoldOut =true; 
                }
            }
            //condition of slecetion to print out sold out venue "X"
            if (venueSoldOut == true){
                cout << left << setw(30) << v[i].name;
                for (int j = 0; j < SEATS; j++)
                {
                    if (v[i].available[j])
                    {
                        cout << right << setw(7) << setprecision(2) << fixed
                            << showpoint << v[i].cost[j];
                    }
                    else
                    {
                        cout << right << setw(7) << "X";
                    }
                }
            }    
            else {
               continue; 
            }
        cout << endl;
    }
}
//function to change user input into all caps to account for error 
string allCaps(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);

    return str;
}
//function to compare user input to venue name and seats 
int validateChoice(const venueType v[], string s)
{
    s = allCaps(s);
    for (int i = 0; i < VENUES; i++)
    {
        if (allCaps(v[i].name) == s)
        {
            for (int j = 0; j < SEATS; j++)
            {
                if (v[i].available[j])
                {
                    return i;
                }
            }
            return -1;
        }
    }
    return -1;
}
//function to slecet and book seats 
double bookSeat(venueType v[], int venueIndex, char seatNumber)
{
    int cheapest = 0;
    double cheapestseat = -1; 
    //to selcet cheapest seats, 
    if (seatNumber == 'c' || seatNumber == 'C')
    {
        for (int i = 0; i < SEATS; i++)
        {
            if (v[venueIndex].available[i] && (v[venueIndex].cost[i] < cheapestseat || cheapestseat < 0))
            {
                //setting cheapest seat equal to index 
                cheapest = i;
                cheapestseat = v[venueIndex].cost[i]; 
            }

        }
        v[venueIndex].available[cheapest] = false;
        //print statment 
        cout << "Ok looking for cheapest available seat\n"; 
        return v[venueIndex].cost[cheapest];
    }
    //to selcet the seat to book based on user choice 
    int seat = seatNumber - '1';
    if (seat >= 0 && seat < 6)
    {
        //condition chechking if seat selcetion is avaliable 
        if (v[venueIndex].available[seat])
        {
            v[venueIndex].available[seat] = false;
            return v[venueIndex].cost[seat];
        }
        
    }
    return 0.0;
}

