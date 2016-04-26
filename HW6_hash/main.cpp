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

    while(digits.size() !=6) //goes through each digit up to the 3rd to create a stack
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
    index = index + temp + digits.top();
    return index;
}

bool quad_probing_without_replacement(int key, int hash_table[], int M)
{
    /** WRITE THIS FUNCTION. IT SHOULD RETURN TRUE IF THE VALUE IS ADDED, FALSE IF THE HASH
    TABLE IS FULL (I.E. THERE ARE NO MORE PLACES FOR THE DATA TO BE ENTERED).
    DON'T FORGET THIS IS LINEAR PROBING WITH REPLACEMENT. **/
    int pos, i;
    pos = hash(key);
    if(hash_table[pos]==0)  //if space is empty
    {
        hash_table[pos]=key;
        return true;
    }
    else                    //if space is not empty
    {
        for(i=pos+1; (pos+(i * i))%M!=pos; i++)     //look for open spot using quad probing
        {
            if(hash_table[i]==0)
            {
                hash_table[i]=key;
                return true;
            }
        }
    }
    return false;       //table overflow
}

int main()
{
    int SSarray[899999999];

    cout << hash(123456789) << endl;
    cout << hash(987654321) << endl;
    cout << hash(111111111) << endl;
    cout << hash(000000000) << endl;
    return 0;
}
