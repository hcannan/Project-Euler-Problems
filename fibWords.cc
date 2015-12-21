/*
 * Author: Camille Annan
 */

#include <iostream>
#include <string>
using namespace std;


// START & END i VALUES FOR SUMMATION, STRINGS 'A' & 'B'
int startValue = 0, endValue = 17; // change to include desired sequence values in summation
string aString = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
string bString = "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196";
unsigned long aLength = (unsigned long)aString.length(), bLength = (unsigned long)bString.length();




// FIBONACCI STRING CLASS
class fibonacciString  {
public:
    unsigned long length;
    fibonacciString *prev = nullptr, *next = nullptr;
    bool startsWithStringA;
    
    // constructor
    fibonacciString(unsigned long &digitsLength, fibonacciString *prevString, fibonacciString *nextString)  {
        length = digitsLength;
        prev = prevString;
        next = nextString;
        if((digitsLength == aLength && prev == nullptr) || prev->startsWithStringA == false)
            startsWithStringA = true;
        else
            startsWithStringA = false;
    }
};


// STARTING FIBONACCI STRINGS
fibonacciString a(aLength, nullptr, nullptr), b(bLength, &a, nullptr), *current = &b, *largest = &b;




// GET Nth DIGIT OF FIRST FIBONACCI STRING OF LENGTH >= N
short getDigit(unsigned long n)  {
    short toReturn = -1;
    unsigned long newLargestLength = 0, newN = 0;
    fibonacciString *newLargest = nullptr;
    
    if(n > 0)  {
        if(n <= a.length && current->startsWithStringA)  {
            toReturn = (short)stoi(aString.substr(n-1, 1));
        }  else if(n <= b.length && !current->startsWithStringA)  {
            toReturn = (short)stoi(bString.substr(n-1, 1));
        }  else if(current->prev->prev != nullptr && n <= current->prev->prev->length)  {
            current = current->prev->prev;
            toReturn = getDigit(n);
        }  else  {
            while(n > current->length)  {
                if(current->next == nullptr)  { // current == largest
                    newLargestLength = largest->length + largest->prev->length;
                    newLargest = new fibonacciString(newLargestLength, largest, nullptr);
                    largest->next = newLargest;
                    largest = newLargest;
                    current = largest;
                }  else
                    current = current->next;
            }
            newN = n - current->prev->prev->length;
            current = current->prev;
            toReturn = getDigit(newN);
        }
    }
    return toReturn;
}




// POWER FUNCTION
unsigned long power(int base, int exponent)  {
    if(exponent == 0)
        return (long)1;
    else if(exponent == 1)
        return (long)base;
    else
        return (long)base * power(base, exponent - 1);
}




// MAIN
int main(int argc, char *argv[])  {
    short NthDigit = 0;
    unsigned long n = 0, IthTerm = 0, sum = 0;
    
    a.next = &b;
    for(int i = startValue; i <= endValue; i++)  {
        n = (127 + (19 * i));
        n *= power(7, i);
        NthDigit = getDigit(n);
        cout << "\nFirst-encountered " << n << "-th digit of fibonacci strings = " << NthDigit << endl;
        IthTerm = NthDigit * power(10, i);
        cout << "\n" << i << "-th term of summation = " << IthTerm << endl;
        sum += IthTerm;
    }
    cout << "\n***SUMMATION OF " << startValue << " - " << endValue << " TERMS = " << sum << "***" << endl;
    
    return 0;
}
