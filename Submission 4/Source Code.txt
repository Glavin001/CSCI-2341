//fraction.cpp
//Iqbal:Arsum:A00351433:csc34125
//Submission 04
//Computing with Fractions, Part 1

/*
UPDATE 1 @ 5:44 PM on 4/10/2012 : Started Program
UPDATE 2 @ 5:44 PM(coincidence) on 5/10/2012 : Finished friend classes
UPDATE 3 @ 7:18 PM on 5/10/2012 : Finished all operator classes
*/

#include <iostream>

using namespace std;

#include "fraction.h"

extern const string MY_ID_INFO = "Iqbal:Arsum:A00351433:CSC34125";

Fraction::Fraction(int numer,int denom)
{
    numerator = numer;
    denominator = denom;
    //if denominator is 0 print the error
    if(denominator == 0)
    {
        cout << "Error: Zero denominator not permitted.\n       Program is now"
            " terminating\n       directly from class constructor.\n" << endl;
        cout << "Press Enter to continue ...";
        cin.ignore(1);
        exit(1);
    }  
}

void Fraction::set(int numer , int denom )
{
    numerator = numer;
    denominator = denom;
    //if denominator is 0 , print the error
    if(denominator == 0)
    {
        cout << "Error: Zero denominator not permitted.\n       Program is now"
            " terminating\n       directly from class constructor.\n" << endl;
        cout << "Press Enter to continue ...";
        cin.ignore(2);
        exit(2);
    }
}

//finds the greatest common divisor using recursion
int gcd(int numerator, int denominator) 
{
    //if denominator is 0 , return the gcd
    if (denominator == 0) 
    {
        return numerator;
    }
    //find the the greatest common divisor
    else
    {
        return gcd(denominator, numerator % denominator); 
    }
}

istream& operator>>(istream& inStream,Fraction& f)
{
    //read the numerator
    int top;
    inStream >> top;
    f.numerator = top;
    //read the /
    char slash;
    inStream >> slash;
    //read the denominator
    int bottom;
    inStream >> bottom;
    f.denominator = bottom;
    return inStream;
}

ostream& operator<<(ostream& outStream,const Fraction& f)
{
    //if both numerator and denominator are negative
    if(f.numerator < 1 && f.denominator < 1)
    {
        //find gcd and multiply it by -1 to turn it positive
        int temp = gcd (f.numerator,f.denominator) * -1;
        //turn everything positive
        outStream << (f.numerator * -1) / temp << "/"
            << (f.denominator * -1) / temp;
    }
    //if denominator is 1
    else if(f.denominator == 1)
    {
        //only display numerator
        outStream << f.numerator;
    }
    else if(f.numerator > 1 && f.denominator < 1)
    {
        //find the gcd
        int temp = gcd (f.numerator,f.denominator);
        outStream << (f.numerator * -1) / temp << "/"
            << (f.denominator *-1) / temp;
    }
    //for regular fractions print it
    else
    {
        //find the gcd
        int temp = gcd (f.numerator,f.denominator);
        outStream << f.numerator / temp  << "/" << f.denominator / temp;
    }
    return outStream;
}

Fraction Fraction::operator+(const Fraction& otherFraction) const
{
    //if denominators are the same
    if(denominator == otherFraction.denominator)
    {
        //just add the numerators
        int newNumer = numerator + otherFraction.numerator;
        Fraction F1(newNumer,denominator);
        //find the gcd
        int temp = gcd (newNumer,denominator);
        F1.set(newNumer / temp,denominator / temp);
        return F1;
    }
    //if denominators are not the same
    else if(denominator != otherFraction.denominator)
    {
        //take the first numerator and multiply it by the second denominator
        int newNumer1 = numerator * otherFraction.denominator;
        //take the second numerator and multiply it by the first denominator
        int newNumer2 = otherFraction.numerator * denominator;
        //get common denominator by multiplying both denoms with each other 
        int newDenum = denominator * otherFraction.denominator;
        //add both first and second numerators into 1 final numerator
        int finalNumer = newNumer1 + newNumer2;
        Fraction F2(finalNumer,newDenum);
        //find the gcd
        int temp = gcd (finalNumer,newDenum);
        F2.set(finalNumer / temp,newDenum / temp);
        return F2;
    }
    return otherFraction;
}

Fraction Fraction::operator-(const Fraction& otherFraction)const
{
    //if denominators are the same
    if(denominator == otherFraction.denominator)
    {
        //subtract the numerators
        int newNumer = numerator - otherFraction.numerator;
        Fraction F1(newNumer,denominator);
        //find the gcd
        int temp = gcd (newNumer,denominator);
        F1.set(newNumer / temp,denominator / temp);
        return F1;
    }
    //if denominators are not the same
    else if(denominator != otherFraction.denominator)
    {
        //take the first numer and multiply it by the second denominator
        int newNumer1 = numerator * otherFraction.denominator;
        //take the second numerator and multiply it by the first denominator
        int newNumer2 = otherFraction.numerator * denominator;
        //get common denoms by multiplying both denoms with each other
        int newDenum = denominator * otherFraction.denominator;
        //get the final numerator by subtracting both numerators
        int finalNumer = newNumer1 - newNumer2;
        Fraction F2(finalNumer,newDenum);
        //find the gcd
        int temp = gcd (finalNumer,newDenum);
        F2.set(finalNumer / temp,newDenum / temp);
        return F2;
    }
    return otherFraction;
}

Fraction Fraction::operator*(const Fraction& otherFraction)const
{
    //get the numer by multiplying both numerators with each other
    int newNumer = numerator * otherFraction.numerator;
    //get the denum by multipling both denominators with each other
    int newDenum = denominator * otherFraction.denominator;
    Fraction F3(newNumer,newDenum);
    //find the gcd
    int temp = gcd (newNumer,newDenum);
    F3.set(newNumer / temp,newDenum / temp);
    return F3;
    return otherFraction;
}

Fraction Fraction::operator/(const Fraction &otherFraction)const
{
    //get the numer by multipling the numerator with the 2nd denominator
    int newNumer = numerator * otherFraction.denominator;
    //get the denum by multiplying the denominator with the 2nd numerator
    int newDenum = denominator * otherFraction.numerator;
    Fraction F4(newNumer,newDenum);
    //find the gcd
    int temp = gcd (newNumer,newDenum);
    F4.set(newNumer / temp,newDenum / temp);
    return F4;
    return otherFraction;
}

bool Fraction:: operator<(const Fraction& otherFraction) const
{
    double top1,bottom1,decimal1;
    double top2,bottom2,decimal2;
    //assign the numerators, denominators of the 2nd fraction
    top1 = otherFraction.numerator;
    bottom1 = otherFraction.denominator;
    //turn the numerator / denominator to decimal so we can compare
    decimal1 = top1 / bottom1;
    //assign the numerators, denominators of the 1st fraction
    top2 = numerator;
    bottom2 = denominator;
    //turn the numerator / denominator to decimal so we can compare
    decimal2 = top2/bottom2;
    //compare and see if its less than or not
    if(decimal2 < decimal1)
    {
        //if less than , then return true
        return true;
    }
    else
    {
        //if not , return false
        return false;
    }
}

bool Fraction::operator==(const Fraction& otherFraction) const
{
    double top1,bottom1,decimal1;
    double top2,bottom2,decimal2;
    //assign the numerators, denominators of the 2nd fraction
    top1 = otherFraction.numerator;
    bottom1 = otherFraction.denominator;
    //turn the numerator / denominator to decimal so we can compare
    decimal1 = top1 / bottom1;
    //assign the numerators, denominators of the 1st fraction
    top2= numerator;
    bottom2 = denominator;
    //turn the numerator / denominator to decimal so we can compare
    decimal2 = top2 / bottom2;
    //compare and see if its equal to or not
    if(decimal1 == decimal2)
    {
        //if equal return true
        return true;
    }
    else
    {
        //if not equal return false
        return false;
    }
}