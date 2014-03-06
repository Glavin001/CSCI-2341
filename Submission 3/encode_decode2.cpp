//encode_decode2.cpp
//Iqbal:Arsum:A00351433:csc34125
//Submission 03
//Command-Line Encoding and Decoding of Textfiles Using Menus

/*
UPDATE 1 @ 8:33 PM on 25/09/2012 : Started Program
UPDATE 2 @ 5:10 PM on 28/09/2012 : Finished Encoding/Decoding
UPDATE 3 @ 4:17 PM on 29/09/2012 : Finished Fc Command Function
UPDATE 4 @ 4:46 PM on 29/09/2012 : Finished doxygen-style formatting
UPDATE 5 @ 6:42 PM on 30/09/2012 : Finished Program
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "utilities.h"

using Scobey::DisplayOpeningScreen;
using Scobey::TextItems;
using Scobey::numberOfDigits;
using Scobey::isEven;
using Scobey::isOdd;
using Scobey::ReadString;
using Scobey::userSaysYes;
using Scobey::Menu;
using Scobey::DisplayTextfile;
using Scobey::Pause;

const TextItems TEXT("encode_decode2.txt");

void BuildMenu
    (
    Menu& menu
    );

/**<
@return void
@param menu is the menu that is going to be built.
@pre menu has been initialized.
@post menu was succesfully built. Titles are set as well as user options.
*/

void EncodeFiles
    (
    ifstream& inFile, // in
    ofstream& outFile // out
    );

/**<
@return void
@param inFile is the file that is going to be encoded.
@param outFile is the file in which the encoded file will be stored in.
@pre inFile and outFile are initialized and open.
@post Encoding was succesful from inFile onto outFile. outFile should now
contain numbers. Files are still open.
*/

void DecodeFiles
    (
    ifstream& inFile, // in
    ofstream& outFile // out
    );

/**<
@return void
@param inFile is the file that contains the encoded message
@param outFile is the file in which the encoded message is decoded in
@pre inFile and outFile are initialized and open.
@post Decoding was succesful from inFile onto outFile. outFile should now
contain plain text. Files are still open.
*/

void CompareFiles
    (
    string& originalFile,
    string& decodedFile
    );

/**<
@return void
@param originalFile is the original file that was supposed to be encoded
@param decodedFile is the file that was decoded using DecodedFiles().
@pre originalFile and decodedFile are initialized and open.
@post both originalFile and decodedFile were succesfully compared.
*/

int main()
{
    DisplayOpeningScreen("Iqbal:Arsum:A00351433:csc34125",
        "Submission 03: Menu-Driven Encoding and Decoding of Textfiles");
    Menu menu;
    BuildMenu(menu);
    menu.display();
    int choice;
    choice = menu.getChoice();
    while(choice > 0)
    {
        //if user chooses 1, terminate program
        if(choice == 1)
        {
            cout << "Program is now terminating.\n";
            Pause();
            return 0;
        }

        //if user chooses 2, display program info
        if(choice == 2)
        {
            TEXT.displayItem("ProgramDescription");
        }

        //if user chooses 3 , encode files
        if(choice == 3)
        {
            string answer;
            do
            {
                string inputFileName;
                ReadString("Enter name of input file: ", inputFileName);
                ifstream infile;
                infile.open(inputFileName.c_str());

                //if the input file is not valid, display error
                if(!infile)
                {
                    TEXT.displayItem("Error:CannotOpenInputFile");
                }

                //if input file is ok , ask for output file
                else
                {
                    string outputFileName;
                    ReadString("Enter name of output file: ", outputFileName);
                    ofstream outfile;
                    outfile.open(outputFileName.c_str());

                    //if the output file is not valid , display error
                    if(!outfile)
                    {
                        TEXT.displayItem("Error:CannotOpenOutputFile");
                    }

                    //if everything is ok , encode the files
                    else
                    {
                        EncodeFiles(infile,outfile);
                        TEXT.displayItem("Information:EncodingComplete");
                        infile.close(), infile.clear();
                        outfile.close(), outfile.clear();
                    }
                }
                cout <<"Encode another file? ";          
            }
            while(userSaysYes(answer));    
        }

        //if user chooses 4 , decode files
        if(choice == 4)
        {
            string answer;
            do
            {
                string inputFileName;
                ReadString("Enter name of input file: ", inputFileName);
                ifstream infile;
                infile.open(inputFileName.c_str());

                //if the input file is not valid, display error
                if(!infile)
                {
                    TEXT.displayItem("Error:CannotOpenInputFile");
                }

                //if the input file is ok, ask for output file
                else
                {
                    string outputFileName;
                    ReadString("Enter name of output file: ", outputFileName);
                    ofstream outfile;
                    outfile.open(outputFileName.c_str());

                    //if the output file is not valid , display error
                    if(!outfile)
                    {
                        TEXT.displayItem("Error:CannotOpenOutputFile");
                    }

                    //if everything is ok, decode the files
                    else
                    {
                        DecodeFiles(infile,outfile);
                        TEXT.displayItem("Information:DecodingComplete");
                        infile.close(), infile.clear();
                        outfile.close(), outfile.clear();
                    }
                }
                cout <<"Decode another file? ";
            }
            while(userSaysYes(answer));
        }

        //if user chooses 5, display file
        if(choice == 5)
        {
            string fileName;
            ReadString("Enter name of file to display: ", fileName);
            DisplayTextfile(fileName);
        }

        //if user chooses 6, compare files
        if(choice == 6)
        {
            string answer;
            do
            {
                string fileName1;
                ReadString("Enter name of first file: ", fileName1);
                string fileName2;
                ReadString("Enter name of second file: ", fileName2);
                CompareFiles(fileName1,fileName2);
                cout << "Compare another file? ";
            }
            while(userSaysYes(answer));
        }

        //display menu again and then ask for user's choice
        menu.display();
        choice = menu.getChoice();
    }
}

void BuildMenu(Menu& menu)
{
    menu.setTitle("Menu");
    menu.addOption("Quit");
    menu.addOption("Get information");
    menu.addOption("Encode a file of plain text");
    menu.addOption("Decode an encoded file of text");
    menu.addOption("Display any file of text");
    menu.addOption("Compare two files using the (non-portable) fc command");
}
void EncodeFiles(ifstream& inFile,ofstream& outFile)
{
    string temp;
    int count = 0;
    char ch;
    while(getline(inFile,temp,'\0'))
    {
        for(int i = 0 ; i < temp.length() ; i++)
        {
            //select each character from the line
            ch = temp[i];
            
            //if number is even
            if(isEven(ch))
            {
                //encode the even numbers
                int a = (int) ch * 19 + 31;
                //if the number of digits in the encoded number is less than 4
                if(numberOfDigits(a) < 4)
                {
                    outFile << '0' << a;
                }
                else
                {
                    outFile << a;
                }
                //add 4 to count because of 4 digits
                count = count + 4;
            }
            //number is odd
            if(isOdd(ch))
            {
                //encode the odd numbers
                int b = (int) ch * 13 + 29;
                //if the number of digits in the encoded number is less than 4
                if(numberOfDigits(b) < 4)
                {
                    outFile << '0' << b;
                }
                else
                {
                    outFile << b;
                }
                //add 4 to count because of 4 digits
                count = count + 4;
            }
            //if more then 60 numbers in line , go to next line
            if(count >= 60)
            {
                outFile << "\n";
                count = 0;
            }
        }
    }
}
void DecodeFiles(ifstream& inFile,ofstream& outFile)
{
    string temp;
    while(getline(inFile,temp))
    {
        for(int i = 0 ; i < temp.length() ; i=i+4)
        {
            int a,b,c,d,letter;
            
            char ch1 = temp[i];
            //finding the int value of ch1
            a = int(ch1)-(int)'0';
            //multiplying by 1000 to find the 1st digit out of the 4 digits
            a = a*1000;

            char ch2 = temp[i+1];
            //finding the int value of ch2
            b = int(ch2)-(int)'0';
            //multiplying by 100 to find the 2nd digit out of the 4 digits
            b = b*100;

            char ch3 = temp[i+2];
            //finding the int value of ch3
            c = int(ch3)-(int)'0';
            //multiplying by 10 to find the 3rd digit out of the 4 digits
            c = c*10;

            char ch4 = temp[i+3];
            //finding the int value of ch4
            d = int(ch4)-(int)'0';
            //multiplying by 1 to find the 4th digit out of the 4 digits
            d = d*1;

            //add all together to form a 4 digit number that will later turn
            //back into letters
            letter = a+b+c+d;

            if(isEven(letter))
            {
                //return the numbers back to their ASCII values
                letter = (letter-29)/13;
            }
            else if(isOdd(letter))
            {
                //return the numbers back to their ASCII values
                letter = (letter-31)/19;
            }
            //print out the letters
            outFile << (char)letter;
        }
    }
}
void CompareFiles(string& originalFile,string& decodedFile)
{
    ifstream File1;
    ifstream File2;
    //open the first file
    File1.open(originalFile.c_str());
    //open the second file
    File2.open(decodedFile.c_str());
    string command = "fc ";
    command += originalFile;
    command += " ";
    command += decodedFile;
    cout << "Here is the report from the fc command:" << endl;
    system(command.c_str());
}