//names_and_addresses.cpp
//Iqbal:Arsum:A00351433:csc34125
//Submission 01
//Reformatting Names and Addresses

/*
Self-assessment ...
UPDATE 1 @ 12:12 PM on 10/09/2012 : Succesfully displayed opening screen
UPDATE 2 @ 7:14 PM on 12/09/2012 : Finished writing DisplayProgramInfo function
UPDATE 3 @ 9:17 PM on 12/09/2012 : Got program to work with 1 info
UPDATE 4 @ 9:29 PM on 12/09/2012 : Got program to work with many info
UPDATE 5 @ 10:24 PM on 13/09/2012 : Got program to display 7 or less info
UPDATE 6 @ 9:40 PM on 15/09/2010 : Finished Program
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "utilities.h"

using Scobey::DisplayOpeningScreen;
using Scobey::ClearScreen;
using Scobey::Pause;

void DisplayProgramInfo();

int main(int arc,char* argv[])
{
    if(arc == 1)
    {
        DisplayOpeningScreen("Iqbal:Arsum:A00351433:csc34125",
            "Submission 01: Reformatting Names and Addresses");
        ClearScreen();
        DisplayProgramInfo();
    }
    else
    {
        ifstream fileName(argv[1]);
        string fileInfo;
        int count = 0;
        int rcount = 0;
        int finalCount = 0;
        while(getline(fileName,fileInfo))
        {
            if(count == 0)
            {
                cout << "\n" << endl;
            }
           
            string :: size_type stop = fileInfo.find('!');
            string :: size_type space = fileInfo.find(' ');
            //takes everything from the start position till first space
            string firstName = fileInfo.substr(0,space);
            //takes everything from the first space to the ! sign
            string lastName = fileInfo.substr(space+1,stop-space-1);
            //takes everything after the ! sign and stores
            string location = fileInfo.substr(stop+1);     
            cout << lastName << ", " << firstName << "\n" << location
                << "\n" << endl;
            count++;
            if(count % 7 == 0)
            {
                cout << "End of display of names #"<< count-6 <<" to #"
                    << count << endl;
                Pause();
                ClearScreen();
                rcount = rcount +7;
            }
        }
        finalCount = count - rcount;
        cout << "End of display of names #"<< count - (finalCount-1) <<" to #"
            << count << endl;
        Pause();
        ClearScreen();
        cout << "All data has now been displayed.\nProgram will now "
            "terminate.\n";
        Pause();
        fileName.close();
    }          
}
void DisplayProgramInfo()
{
    cout << "This program takes a single command-line parameter, which must "
        "be the name of\nan existing file in the current directory, or the "
        "full pathname of an existing\nfile if that file is located elsewhere."
        "\n\nThis input file must contain a (non-empty) list of names and "
        "addresses in the\nfollowing format, one name and address pair per "
        "line, and there may be any\nnumber of lines in the file: \n" << endl;
        
    cout << "Firstname Lastname!123 Main St., AnyTown\n"
        "Barack Obama!1600 Pennsylvania Avenue, Washington\n"
        "Stephen Harper!24 Sussex Drive, Ottawa\n"
        "... and so on ...\n" << endl;

    cout << "For simplicity, assume each complete name consists of a single "
        "first name,\nfollowed by a single last name, with a single blank "
        "space separating the two.\nAssume as well no blank spaces within the "
        "first or last names themselves.\n\nAn exclamation mark follows the "
        "name, and all text following this mark (on the\nsame line as the "
        "name) is to be interpreted as the corresponding address.\n\n"
        "The program reads the names and addresses from the file, and then "
        "displays them on the standard output, in the same order as they "
        "appeared in the input file.\n" << endl;

    Pause();
    ClearScreen();

    cout <<"\nThe output display is formatted as follows:\n\nFirst, each name "
        "appears by itself on a line, with the last name first,\nfollowed by "
        "a comma and a space and then the first name.\n\nNext, the address "
        "corresponding to a name must appear on the line\nimmediately under "
        "that name.\n\nA blank line must separate each name and address pair."
        "\n\nAlso, name and address pairs are displayed seven at a time,and "
        "after each\ngroup of seven is displayed a message is also displayed "
        "to inform the user\nof the numbers of those individuals in the input "
        "file. Note, of course,\nthat the last group may contain fewer than "
        "seven individuals, depending on\nthe total number of individuals in "
        "the input file.\n\n\n\n\n\n\n\n" << endl;
    Pause();
}