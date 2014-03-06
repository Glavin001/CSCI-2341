//textitem2.cpp
//Iqbal:Arsum:A00351433:csc34125
//Submission 08
//Implementing the Student::TextItem Class, Part 2

/*
UPDATE 1 @ 10:18 PM on 31/10/2012 : Started Program
UPDATE 2 @ 5:36 PM on 1/11/2012 : Finished Destructor
UPDATE 3 @ 6:49 PM on 1/11/2012 : Finished Copy Constructor
UPDATE 4 @ 1:00 PM on 4/11/2012 : Finished Assignment Operator
UPDATE 5 @ 1:29 PM on 4/11/2012 : Finished Program
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "textitem2.h"

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
        ofstream traceFile;
        string traceFileName;

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
            cout << "\n Press Enter to continue"; cin.ignore(80,'\n');
            exit(1);
        }

        string equalSign = "========================================";
        while(inputLine != equalSign) getline(inFile, inputLine);
        {
            // make a new node
            firstLinePtr = new LineNode;
            //store the line into inputLine
            getline(inFile, inputLine);
            //store inputLine into the 'data'of the node
            firstLinePtr->lineText = inputLine;

            //make current point to firstLinePtr
            LineNode* current =firstLinePtr;
            while(getline(inFile, inputLine) && inputLine != equalSign)
            {
                //make a new node
                current ->next = new LineNode;
                //make current point to the new node
                current = current -> next;
                //store inputLine into the 'data' of the node
                current->lineText = inputLine;
            }
            //make the link into NULL
            current->next = nullptr;

            //start of tracing
            if(tracingOn)
            {
                cout << "\nEnter name of trace file for constructor: ";
                cin >> traceFileName; cin.ignore(80,'\n');
                traceFile.open(traceFileName.c_str());

                traceFile<<"====Starting item construction by getting a first"
                    "line node.\n";

                LineNode* trace = firstLinePtr;
                while(trace != nullptr)
                {
                    traceFile << "-----Inserting this line:" << endl;
                    //show the 'data' of the node
                    traceFile << trace ->lineText << endl;
                    //link to the next node
                    trace = trace -> next;
                    if(trace != nullptr)
                    {
                        traceFile << ">>>>>Getting another line node." << endl;
                    }                  
                }
                traceFile << "=====Ending item construction by terminating the"
                    " sequence of line nodes." << endl;
            }//end of tracing
            inFile.close();
        }
    }//end of constructor

    //start of destructor
    TextItem::~TextItem() 
    {
        ofstream outFile;
        string traceFile;

        //if nothing to destruct
        if(firstLinePtr == nullptr) 
        {
            return;
        }

        if(tracingOn)
        {
            cout << "Enter name of trace file for destructor: ";
            cin >> traceFile;
            outFile.open(traceFile.c_str());
            outFile << "===Start item destruction.\n";
        }
        //make current point to firstLinePtr
        LineNode* current = firstLinePtr;
        while(current != nullptr)
        {
            LineNode* destroyPtr = current;
            current = current->next;
            if(tracingOn)
            {
                outFile << "..line of text:" << destroyPtr->lineText << endl;
            }

            delete destroyPtr;
        }
        //make it NULL
        firstLinePtr = nullptr;
        if(tracingOn)
        {
            outFile << "=====End";
            outFile.close();
        }
    }//end of destructor

    //start of copy constructor
    TextItem::TextItem(const TextItem& original) 
    {
        //make new node
        firstLinePtr = new LineNode;
        //make current point to firstLinePtr
        LineNode* current = firstLinePtr;
        //make the oldPtr point to the firstLinePtr
        LineNode* oldPtr = original.firstLinePtr;

        while(oldPtr != nullptr)
        {
            //copy the data
            current->lineText = oldPtr->lineText;
            //go to the next node
            oldPtr = oldPtr->next;
            if(oldPtr != nullptr)
            {
                //make a new node
                current->next = new LineNode;
                //point to the new node
                current= current->next;
            }
        }
        //make it NULL
        current->next = nullptr;
    }//end of copy constructor

    //start of overloaded assignment operator
    TextItem& TextItem::operator=(const TextItem& rhs)
    {
        if(firstLinePtr == rhs.firstLinePtr)
        {
            return *this;
        }

        else
        {
            this->~TextItem();
        }
        //make new node
        firstLinePtr = new LineNode;
        //point current to firstLinePtr
        LineNode* current = firstLinePtr;
        LineNode* oldPtr = rhs.firstLinePtr;
        while(oldPtr != nullptr)
        {
            current->lineText = oldPtr->lineText;
            oldPtr = oldPtr->next;
            if(oldPtr != nullptr)
            {
                //make new node
                current->next = new LineNode;
                //point to that new node
                current= current->next;
            }
        }
        //make it NULL
        current->next= nullptr;
        return *this;
    }//end of overloaded assignment operator

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