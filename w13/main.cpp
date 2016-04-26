#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <stack>
#include <queue>
#include <cmath>

using namespace std;

/**read file to an array**/
bool readFile(char* filename, int A[])
{
    int i=0;
    int t=0;
    char* temp=new char[100];
    ifstream in;
    in.open(filename);
    //check if file was found
    if(!in.is_open())
    {
        cout << "Sorry, that file was not found.";
        return false;
    }
    while(in.peek()!=EOF)
    {
        in.getline(temp, 100, ' ');
        t = atoi(temp);
        A[i] = t;
        i++;
    }
    in.clear();
    in.close();
    return true;
}

/**division hash**/
int division_method(int val, int M) //val= int read in      M=size of array
{
    //int A = new int[M];
    return val%M;
}

/**multiplication hash**/
int multiplication_method(int val, int M)
{
    return fmod(((float)(M*val)/3.0),M);
}

/**rotation hash**/
int rotation_method(int val)
{
    stack<int> digits;
    int temp;
    int newFirstDigit;

    newFirstDigit = val % 10;
    val = val/10;

    while(val>1) //goes through each digit of the int
    {
        temp = val % 10;    //
        val = val/10;
        digits.push(temp);
    }
    digits.push(newFirstDigit);
    int index = 0;

    while(digits.size()!=0)
    {
        int exp = digits.size()-1;  //find length to find how many digits
        temp = digits.top();        //pull off top digit
        temp = temp * (10^exp);       //multiply to put digit in the correct place
        index = index + temp;
        digits.pop();               //remove digit;
    }
    return index + val;
}


int main()
{
    int A[10];
    readFile("smallSample.txt", A);

    cout << "Division Method" <<endl;
    for (int i=0; i<10; i++)
    {
        cout << division_method(A[i], 10) << "\t";
    }

    cout << "Multiplication Method" <<endl;
    for (int i=0; i<10; i++)
    {
        cout << multiplication_method(A[i], 10) << "\t";
    }

    cout << "Rotation Method" <<endl;
    for (int i=0; i<10; i++)
    {
        cout << rotation_method(A[i]) << "\t";
    }

    int random[10000];
    readFile("Random.txt", random);
    int hashtableDIV[10000];
    int hashtableMULT[10000];
    int hashtableROT[10000];


    for (int i=0; i<10; i++)
    {
        A[i] = hashtableDIV[division_method(A[i], 10)];
    }


    for (int i=0; i<10; i++)
    {
        A[i] = hashtableMULT[multiplication_method(A[i], 10)];
    }

    for (int i=0; i<10; i++)
    {
        A[i] = hashtableROT[rotation_method(A[i])];
    }
}
