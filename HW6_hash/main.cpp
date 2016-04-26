#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stack>
#include <cmath>

using namespace std;

bool getFile (char* filepath, int *& my_array)      //gets file from filepath
{
    if(my_array!=NULL) delete my_array;
    my_array = new int[500];                   //sets up array for integers to go into
    char lineData[50];
    int number;
    ifstream in;
    in.open(filepath);
    if(!in.is_open())
    {
        cout << "I cannot find the file.\n";
        return false;
    }
    int i=0;
    while(in.peek()!=EOF)
    {
        in.getline(lineData,50,' ');
        number=atoi(lineData);
        my_array[i]=number;
        i++;
    }
    in.clear();
    in.close();
    return true;
}

int hash (int val)
{
    stack<int> digits;
    int temp;

    val = val/10;   //ignores 9th digit

    while(val>100) //goes through each digit up to the 3rd to create a stack
    {
        temp = val % 10;    //
        val = val/10;
        digits.push(temp);
    }

    int index = 0;
    double exp = 3.0;                        //digits will start in the thousands place (10^3)

    while (digits.size() > 2)
    {
        temp = digits.top();            //pull off top digit
        temp = temp * pow(10.0, exp);   //multiply to put digit in the correct place
        index = index + temp;
        digits.pop();                   //remove following two digits
        digits.pop();
        exp--;                  //decrease exponent
    }

    temp = digits.top() * 10;
    digits.pop();
    index = index + temp + digits.top() + 1;
    return index;
}

int main()
{
    //int SSarray[899999999];

    cout << hash(123456789) << endl;
    cout << hash(987654321) << endl;
    cout << hash(111111111) << endl;
    cout << hash(100000000) << endl;
    return 0;
}
