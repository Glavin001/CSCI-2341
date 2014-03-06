//textitem1.cpp
//Iqbal:Arsum:A00351433:csc34125
//Submission 07
//Implementing the Student::TextItem Class, Part 1

/*
UPDATE 1 @ 10:18 PM on 22/10/2012 : Started Program
UPDATE 2 @ 11:03 PM on 22/10/2012 : Finished Default Constructor
UPDATE 3 @ 2:47 PM on 27/10/2012 : Finished Everything except pause at 40(!)
UPDATE 4 @ 5:33 PM on 28/10/2012 : Finished Program
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "textitem1.h"

extern const std::string MY_ID_INFO = "Iqbal:Arsum:A00351433:csc34125";
bool tracingOn = false;

namespace Student
{
    TextItem::TextItem()
    {
        cout << "Error:\nA file name must be supplied when declaring a "
            "TextItem object.\nExample of a proper declaration:\nTextItem "
            "myTextItems(\"my_text_item_file.dat\");\n\nProgram is now "
            "terminating.\nPress Enter to continue ...";
        //pauses
        cin.ignore(80,'\n');
        exit(1);
    }

    TextItem::TextItem(const string& fileName)
    {
        ifstream infile;
        string choice;
        string sentence;
        bool beforeEquals = true;
        bool fileBody = false;
        string linesBeforeEqual;
        
        //make a new node
        firstLinePtr = new LineNode;
        //make a new pointer
        LineNode* current;
        //point the new pointer to the node
        current = firstLinePtr;
        //open the file
        infile.open(fileName);

        //If the file is open
        if(infile.is_open())
        {
            //[Case 2] Check if file is empty
            if(infile.peek() == EOF)
            {
                cout << "\nError: Input text item file is empty.\nProgram is "
                    "now terminating.\n\nPress Enter to continue ... ";
                infile.close();
                cin.ignore(80,'\n');
                exit(1);
            }//end of if file is empty

            //[Case 1] If its not empty, store info into nodes
            while(infile)
            {
                //pretty much ignores the = sign and moves on to store info
                if(beforeEquals == true)
                {
                    string equalSign = "========================================";
                    getline(infile,linesBeforeEqual);
                    if(linesBeforeEqual == equalSign)
                    {
                        beforeEquals = false;
                        fileBody = true;
                    }
                }
                if(fileBody == true)
                {
                    //get the line from the file and store it into sentence
                    getline(infile,sentence);
                    //store line into the 'data' of the node
                    current -> lineText = sentence;
                    //if the file has reached its end
                    if(infile.peek() == EOF)
                    {
                        //make the link into NULL
                        current -> next = nullptr;
                        //point the pointer to the beginning
                        current = firstLinePtr;                 
                    }
                    else
                    {
                        //create a new node
                        current -> next = new LineNode;
                        //point the pointer to the new node
                        current = current -> next;
                    }
                }
            }//end of storing info into nodes

            //if user says yes to trace
            if(tracingOn == true)
            {
                ofstream outfile;
                string traceFile;
                cout << "\nEnter name of trace file for constructor: ";
                cin >> traceFile;
                cin.ignore();
                outfile.open(traceFile);
                outfile << "=====Starting item construction by getting a first"
                    "line node." << endl;
                //make new pointer and point it to the start of the node
                LineNode* trace = firstLinePtr;
                while(trace != nullptr)
                {
                    outfile << "-----Inserting this line:" << endl;
                    //show the 'data' of the node
                    outfile << trace ->lineText << endl;
                    //link to the next node
                    trace = trace -> next;
                    if(trace != nullptr)
                    {
                        outfile << ">>>>>Getting another line node." << endl;
                    }                  
                }
                outfile << "=====Ending item construction by terminating the "
                    "sequence of line nodes." << endl;
                outfile.close();
            }//end of trace
        }

        //[Case 3] If file doesn't exist
        else
        {
            if(!infile)
            {
                cout << "\nError: Cannot find file " << fileName << ".\nPlease"
                    " enter name (and path, if necessary) of the\nappropriate"
                    "text item file, if you know it.\nOtherwise, just press "
                    "Enter to terminate: ";
                getline(cin,choice);
                infile.open(choice);
                //if file doesnt exist
                if(!infile)
                {
                    cout << "\nError: Input text item file does not exist.\n"
                        "Program is now terminating.\nPress Enter to "
                        "continue ... ";
                    cin.ignore(80,'\n');
                    exit(1);
                }
                else
                {
                    if(infile.is_open())
                    {
                        //check if file is empty
                        if(infile.peek() == EOF)
                        {
                            cout << "\nError: Input text item file is empty.\n"
                                "Program is now terminating.\n\nPress Enter to"
                                "continue ... ";
                            infile.close();
                            cin.ignore(80,'\n');
                            exit(1);
                        }//end of check if file is empty

                        //store info into nodes
                        while(infile)
                        {
                            //pretty much ignores the = sign and moves on to store info
                            if(beforeEquals == true)
                            {
                                string equalSign ="=============================="
                                    "=========="; 
                                getline(infile,linesBeforeEqual);
                                if(linesBeforeEqual == equalSign)
                                {
                                    beforeEquals = false;
                                    fileBody = true;
                                }
                            }
                            if(fileBody == true)
                            {
                                //get the line from the file and store it into
                                //sentence
                                getline(infile,sentence);   
                                //store line into the 'data' of the node
                                current -> lineText = sentence;
                                //if the file has reached its end
                                if(infile.peek() == EOF)
                                {
                                    //make the link into NULL
                                    current -> next = nullptr;
                                    //point the pointer to the new node
                                    current = firstLinePtr;                 
                                }
                                else
                                {
                                    //create a new node
                                    current -> next = new LineNode;    
                                    //point the pointer to the new node
                                    current = current -> next;
                                }
                            }
                        }//end of storing info into nodes
                    }//end of check if file is open
                }//end of else
            }//end of [Case 3]
        }//end of else
    }//end of constructor

    ostream& operator<<(ostream& outStream,const TextItem& item)
    {
        TextItem::LineNode* informationNode = item.firstLinePtr;
        while(informationNode != nullptr)
        {
            string pauseSign = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
            if(informationNode -> lineText == pauseSign)
            {
                //pause
                outStream << "Press Enter to continue ... ";
                cin.ignore(80,'\n');
                //link to next node
                informationNode = informationNode ->next;
            }
            else
            {
                //print data of the node
                outStream << informationNode -> lineText << "\n";
                //link to next node
                informationNode = informationNode ->next;
            }
        }
        return outStream;
    }
}