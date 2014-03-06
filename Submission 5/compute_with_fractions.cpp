//compute_with_fractions.cpp
//Iqbal:Arsum:A00351433:csc34125
//Submission 05
//Computing with Fractions, Part 2

/*
UPDATE 1 @ 8:37 PM on 11/10/2012 : Started Program
UPDATE 2 @ 9:18 PM on 11/10/2012 : Finished stubs for menu options
UPDATE 3 @ 10:45 PM on 11/10/2012 : Finished Program
UPDATE 4 @ 4:27 PM on 14/10/2012 : Applied some finishing touches
*/

#include <iostream>

using namespace std;

#include "fraction.h"
#include "utilities.h"

using Scobey::DisplayOpeningScreen;
using Scobey::TextItems;
using Scobey::Menu;
using Scobey::Pause;
using Scobey::userSaysYes;

extern const string MY_ID_INFO;
const TextItems TEXT("compute_with_fractions.txt");

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

int main()
{
    DisplayOpeningScreen(MY_ID_INFO,
        "Submission 05: Computing with Fractions, Part 2");
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
            TEXT.displayItem("Program Description");
        }

        //if user chooses 3 , evaluate the fractions
        if(choice == 3)
        {
            string answer;
            do
            {
                cout << "\nEnter fractional expression to be evaluated: ";
                //declare all variables in this scope
                Fraction fraction1, fraction2, finalFraction;
                char operators;
                cin >> fraction1;
                cin >> operators;
                cin >> fraction2;
                
                //if operator is + , do addition
                if(operators == '+')
                    finalFraction = fraction1+fraction2;
                
                //if operator is - , do subtraction
                else if(operators == '-')
                    finalFraction = fraction1-fraction2;
                
                //if operator is * , do multiplication
                else if(operators == '*')
                    finalFraction = fraction1*fraction2;
                
                //if operator is / , do division
                else if(operators == '/')
                    finalFraction = fraction1/fraction2;

                cout << "Answer: " << fraction1 << " " << operators << " "
                    << fraction2 << " = " << finalFraction;
                cout << "\nDo another calculation?";
                cin.ignore();
            }
            while(userSaysYes(answer));
        }

        //if user chooses 4, compare the fractions
        if(choice == 4)
        {
            string answer;
            do
            {
                cout << "\nEnter two fractions to be compared: ";
                //declare all variables in this scope
                Fraction fraction1, fraction2, differenceFraction1,
                    differenceFraction2; 
                cin >> fraction1;                
                cin >> fraction2;
                //if the 2nd one is bigger than the first , calculate the
                //difference between the two
                differenceFraction1 = fraction2 - fraction1;
                //if the 1st one is bigger than the second , calculate the
                //difference between the two
                differenceFraction2 = fraction1 - fraction2;

                //if the 1st fraction is less than the second, print it as well
                //as the difference between the two
                if(fraction1 < fraction2)
                {
                    cout << fraction2 << " is greater than " << fraction1
                        << " and the difference is " << differenceFraction1
                        << ".";
                }

                //if the 2nd fraction is less than the first, print it as well
                //as the difference between the two
                if(fraction2 < fraction1)
                {
                    cout << fraction1 << " is greater than " << fraction2
                        << " and the difference is " << differenceFraction2
                        << ".";
                }

                //if the fractions are equal print it
                else if(fraction1==fraction2)
                {
                    cout << "The two fractions are equal.";
                }
                cout << "\nDo another comparison?";
                cin.ignore();
            }
            while(userSaysYes(answer));
            
        }

        //if user chooses 5 , conduct specific fraction tests
        if(choice == 5)
        {
            string choice;
            TEXT.displayItem("TestInfo:Part0");

            //first test to check constructors and the set function
            cout << "Test your constructors and set()?";
            if(userSaysYes(choice))
            {
                TEXT.displayItem("TestInfo:Part1");
                cout << "\nAnd here are the corresponding values "
                    << "according to *your* Fraction class: "   << endl;
                Fraction f11(3,4), f12(-3,-4), f13(15,20), f14(-9,-12);
                cout << f11 << "  " << f12 << "  " << f13 << "  " << f14
                    << endl;
                Fraction f21(3,1), f22(3);
                cout << f21 << "  " << f22 << endl;
                Fraction f31(-3,1), f32(-3);
                cout << f31 << "  " << f32 << endl;
                Fraction f4;
                cout << f4 << endl;
                Fraction f51, f52, f53, f54;
                f51.set(3,4); f52.set(-3,-4); f53.set(15,20); f54.set(-9,-12);
                cout << f51 << "  " << f52 << "  " << f53 << "  " << f54
                    << endl;
                Fraction f61, f62;
                f61.set(3,1);  f62.set(3);
                cout << f61 << "  " << f62 << endl;
                Fraction f71(-3,1), f72(-3);
                cout << f71 << "  " << f72 << endl;
                Fraction f8;
                f8.set();
                cout << f8 << endl;
                Pause();
            }    
            
            //2nd test to test input/output operators
            cout << "Test your input/output operators?";
            if(userSaysYes(choice))
            {
                TEXT.displayItem("TestInfo:Part2a");
                Fraction a,b,c,d,e,f;
                cin >> a >> b >> c >> d >> e >> f;
                cout << " " << endl;
                TEXT.displayItem("TestInfo:Part2b");
                cout << "And here are the actual values as read in and then "
                    "displayed by your program:";
                cout << "\n" << a << "  " << b << "  " << c << "  "  << d
                    << "  " << e << "  " << f << endl;
                //clear input stream for pause function to work
                cin.ignore();
                Pause();
            }

            //3rd test to test the constructors error reporting
            cout << "Check your constructor error-reporting?";
            if(userSaysYes(choice))
            {
                TEXT.displayItem("TestInfo:Part3");
                Fraction f1(1,0);
            }

            //4th and final test to test the set function errror reporting
            cout << "Check your set() function error-reporting?";
            if(userSaysYes(choice))
            {
                TEXT.displayItem("TestInfo:Part4");
                Fraction f2;
                f2.set(1,0);
            }            
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
    menu.addOption("Compute the value of a fractional expression");
    menu.addOption("Compare the values of two fractions");
    menu.addOption("Display specific fraction tests");
}