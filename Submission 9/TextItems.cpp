//TextItems.cpp
//Iqbal:Arsum:A00351433:csc34125
//Submission 09
//Implementing the Student::TextItems Class

/*
UPDATE 1 @ 7:04 PM on 08/11/2012 : Started program
UPDATE 2 @ 3:46 PM on 09/11/2012 : Finished constructor
UPDATE 3 @ 8:21 PM on 09/11/2012 : Finished displaying entire file
UPDATE 4 @ 6:46 PM on 11/11/2012 : Finished program
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#include "textitems.h"

extern const string MY_ID_INFO = "Iqbal:Arsum:A00351433:CSC34125";
vector<string> column;

Student::TextItems::TextItems()
{
    cout << "\nError: File name must be supplied when declaring a TextItems "
        "object.\nExample of a proper declaration:\nTextItems myTextItems"
        "(\"my_text_item_file.dat\");\nProgram is now terminating.\n"
        "Press Enter to continue ... ";
    cin.ignore(80,'\n');
    exit(1);
}

Student::TextItems::TextItems(const string& fileName)
{
    ifstream inFile(fileName.c_str());
    //if file doesnt open
    if(inFile.fail())
    {
        cout << "\nError: Cannot find file " << fileName << ".\nPlease "
            "enter name (and path, if necessary) of the\nappropriate "
            "text item file, if you know it.\nOtherwise, just press "
            "Enter to terminate: ";
        string choice;
        getline(cin, choice);
            
        //if the choice isnt an enter
        if(choice !=" ")
        {
            inFile.clear();
            inFile.open(choice.c_str());
        }

        //if file doesnt open
        if(inFile.fail())
        {
            cout << "\nError: Input text item file does not exist."
                "\nProgram is now terminating.\nPress Enter to "
                "continue ... ";
            exit(1);
        }
    }

    string inputLine;
    getline(inFile, inputLine);

    //if nothing in the file
    if(inFile.eof())
    {
        cout << "\nError: Input text item file is empty."
        "\nProgram is now terminating. \n";
        cout << "\n Press Enter to continue ... "; cin.ignore(80,'\n');
        exit(1);
    }

    string equalSign = "========================================";
    while(inputLine != equalSign) getline(inFile, inputLine);
    {
        while(getline(inFile, inputLine) && inputLine != equalSign)
        {
            //store the line from the file into the column
            column.push_back(inputLine);
            //store the column into itemList
            itemList.push_back(column);
        }
    }
    inFile.close();
}

void Student::TextItems::displayItem(const string& title)const
{
    string pauses = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    string dashes = "----------------------------------------";
    int size = itemList.size();
    //int count = 0;
    vector<vector<string>>::const_iterator p = itemList.begin();
    vector<string>::const_iterator p1 = column.begin();

    while(p != itemList.end())
    {   
        while(p1 != column.end())
        { 
            //if the column contains the title
            if(*p1 == title)
            {   
                //increment to the next column
                *p1++;                
                //print it
                cout << *p1 <<endl;             
                //if the column doesnt contain the dashes , loop through

                while(*p1 != dashes)
                {
                    *p1++;
                    //if the column contains the pauses
                    if(*p1 == pauses)
                    {
                        //pause
                        cout << "Press Enter to Continue... ";
                        cin.ignore(80,'\n');
                        //increment to next column
                        *p1++;                        
                        //if its a dash , break out
                        if( *p1 == dashes)
                            break;
                    }
                    cout << *p1<<endl; 
                }
                break;
            }

            //if we looped through the entire vector and we didnt find title
            else if(p1 == column.end() - 1)
            {
                cout << "\nError: Text item " << title << " not found.\nPress "
                    "Enter to continue ...";
                cin.ignore(80,'\n');
                break;
            }
            *p1++;
        } 

        if(*p1 == dashes)
            break;
    }   
}