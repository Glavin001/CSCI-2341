//encode_decode1.cpp
//Iqbal:Arsum:A00351433:csc34125
//Submission 02
//Command-Line Encoding and Decoding of Textfiles

/*
UPDATE 1 @ 11:35 AM on 17/09/2012 : Started Program
UPDATE 2 @ 8:07 PM on 19/09/2012 : Started to work on functions
UPDATE 3 @ 9:30 PM on 20/09/2012 : Finished encoding/decoding but not '\n'
UPDATE 4 @ 7:52 PM on 22/09/2012 : Extra newline character in en/de-coded file
UPDATE 5 @ 7:54 PM on 23/09/2012 : 0221 instead of 0198 shows up in encode file
*/

#include <iostream>
#include <fstream>

using namespace std;

#include "utilities.h"

using Scobey::DisplayOpeningScreen;
using Scobey::TextItems;
using Scobey::numberOfDigits;
using Scobey::isEven;
using Scobey::isOdd;

const TextItems TEXT("encode_decode1.txt");

void EncodeFile
    (
    ifstream& inFile, //in
    ofstream& outFile //out
    );

/**<
Encodes a single file of plain text and writes out the result to a
an encoded output file.
@param inFile The plain text input file.
@param outFile The encoded output file.
@pre inFile and outFile have been initialized and are open.
@post The text in inFile has been encoded and the encoding has been
written out to outFile. Both files remain open.
*/

void DecodeFile
    (
    ifstream& inFile, //in
    ofstream& outFile //out
    );

/**<
Decodes a single file of encoded text and writes out the resulting
plain text to a an output file.
@param inFile The encoded input file.
@param outFile The plain text output file.
@pre inFile and outFile have been initialized and are open.
@post The text in inFile has been decoded and the plain text has
been written out to outFile. Both files remain open.
*/

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        DisplayOpeningScreen("Iqbal:Arsum:A00351433:csc34125",
            "Submission 02: Command-Line Encoding and Decoding of Textfiles");
        TEXT.displayItem("ProgramDescription");
        return 0;
    }
    if(argc !=4)
    {
        TEXT.displayItem("Error:BadParameterCount");
        return 0;
    }
    if(strcmp(argv[1],"d") != false && strcmp(argv[1],"e") != false)
    {
        TEXT.displayItem("Error:BadFirstParameter");
        return 0;
    }
    ifstream inputfile(argv[2]);
    if(!inputfile)
    {
        TEXT.displayItem("Error:CannotOpenInputFile");
        return 0;
    }
    ofstream outputfile(argv[3]);
    if(!outputfile)
    {
        TEXT.displayItem("Error:CannotOpenOutputFile");
        return 0;
    }
    if(strcmp(argv[1],"e") == 0)
    {
        EncodeFile(inputfile,outputfile);
        TEXT.displayItem("Information:EncodingComplete");
        return 0;
    }
    if(strcmp(argv[1],"d") == 0)
    {
        DecodeFile(inputfile,outputfile);
        TEXT.displayItem("Information:DecodingComplete");
        return 0;
    }
}

void EncodeFile(ifstream& inFile, ofstream& outFile)
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
void DecodeFile(ifstream& inFile, ofstream& outFile)
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