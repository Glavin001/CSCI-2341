//generate_random_values.cpp
//Iqbal:Arsum:A00351433:csc34125
//Submission 06
//Generating Random Values Using Command Line

/*
UPDATE 1 @ 3:06 PM on 19/10/2012 : Started Program
UPDATE 2 @ 5:06 PM on 21/10/2012 : Finished Program
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

#include "utilities.h"

using Scobey::DisplayOpeningScreen;
using Scobey::TextItems;
using Scobey::RandomGenerator;

const TextItems TEXT("generate_random_values.txt");

int main(int argc,char* argv[])
{
    int numbers = 0;
    int count = 0;
    double reals = 0.0;
    string line;
    //if no command line arguments
    if(argc == 1)
    {
        //display ID screen and program description
        DisplayOpeningScreen("Iqbal:Arsum:A00351433:csc34125",
        "Submission 06: Generating Random Values");
        TEXT.displayItem("ProgramDescription");
    }
    else
    {
        //if seed is < or = 0 - print random
        if(atoi(argv[1]) <= 0 )
        {
            //if user chooses ints
            if(strcmp(argv[2] , "i") == 0)
            {
                RandomGenerator g1;
                for(int i = 0; i < atoi(argv[3]) ; i++)
                {
                    numbers = g1.getNextInt(atoi(argv[4]),atoi(argv[5]));
                    //set the field width
                    cout << setw(atoi(argv[7]));
                    //right justify the numbers
                    cout << right << numbers;
                    count ++;
                    //if the # on a line exceeds argv[6] , make new line
                    if(count == atoi(argv[6]))
                    {
                        cout << " " << endl;
                        count = 0;
                    }
                }
                g1.reset();
            }//end of user chooses ints

            //if user chooses doubles/reals
            if(strcmp(argv[2] , "r") == 0)
            {
                RandomGenerator g2;
                for(int i = 0; i < atoi(argv[3]) ; i++)
                {
                    reals = g2.getNextDouble(atoi(argv[4]),atoi(argv[5]));
                    //set the field width
                    cout << setw(atoi(argv[7]));
                    //right justify the numbers and set the precision we want
                    cout << right << fixed << setprecision(atoi(argv[8]))
                        << reals;
                    count ++;
                    //if the # on a line exceeds argv[6] , make new line
                    if(count == atoi(argv[6]))
                    {
                        cout << " " << endl;
                        count = 0;
                    }
                }
                g2.reset();
            }//end of user chooses double/reals

            //if user chooses string
            if(strcmp(argv[2] , "s") == 0)
            {
                RandomGenerator g3;
                for(int i = 0; i < atoi(argv[3]) ; i++)
                {
                    line = g3.getNextString(argv[4],argv[5]);
                    //set the field width
                    cout << setw(atoi(argv[7]));
                    //left justify the strings
                    cout << left << line;
                    count ++;
                    //if the # on a line exceeds argv[6] , make new line
                    if(count == atoi(argv[6]))
                    {
                        cout << " " << endl;
                        count = 0;
                    }
                }
                g3.reset();
            }// end of user chooses string
        }// end of user chooses seed value of less than or 0

        //if seed value is greater than 0
        if(atoi(argv[1]) > 0)
        {
            //if user chooses ints
            if(strcmp(argv[2] , "i") == 0)
            {
                RandomGenerator g1 = RandomGenerator(atoi(argv[1]));
                for(int i = 0; i < atoi(argv[3]) ; i++)
                {
                    numbers = g1.getNextInt(atoi(argv[4]),atoi(argv[5]));
                    //set the field width
                    cout << setw(atoi(argv[7]));
                    //right justify the numbers
                    cout << right << numbers;
                    count ++;
                    //if the # on a line exceeds argv[6] , make new line
                    if(count == atoi(argv[6]))
                    {
                        cout << " " << endl;
                        count = 0;
                    }
                }
                g1.reset();
            }//end of user chooses ints

            //if user chooses double/reals
            if(strcmp(argv[2] , "r") == 0)
            {
                RandomGenerator g2 = RandomGenerator(atoi(argv[1]));
                for(int i = 0; i < atoi(argv[3]) ; i++)
                {
                    reals = g2.getNextDouble(atoi(argv[4]),atoi(argv[5]));
                    //set the field width
                    cout << setw(atoi(argv[7]));
                    //right justify the numbers and set the precision we want
                    cout << right << fixed << setprecision(atoi(argv[8]))
                        << reals;
                    count ++;
                    //if the # on a line exceeds argv[6] , make new line
                    if(count == atoi(argv[6]))
                    {
                        cout << " " << endl;
                        count = 0;
                    }
                }
                g2.reset();
            }//end of user chooses doubles/reals

            //if user chooses string
            if(strcmp(argv[2] , "s") == 0)
            {
                RandomGenerator g3 = RandomGenerator(atoi(argv[1]));
                for(int i = 0; i < atoi(argv[3]) ; i++)
                {
                    line = g3.getNextString(argv[4],argv[5]);
                    //set the field width
                    cout << setw(atoi(argv[7]));
                    //left justify the strings
                    cout << left << line;
                    count ++;
                    //if the # on a line exceeds argv[6] , make new line
                    if(count == atoi(argv[6]))
                    {
                        cout << " " << endl;
                        count = 0;
                    }
                }
                g3.reset();
            }// end of user chooses string
        }//end of user chooses seed value of greater than 0
    }
}//end of main