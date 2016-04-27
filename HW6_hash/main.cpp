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
    my_array = new int[65000];                   //sets up array for integers to go into
    char lineData[10];
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
        in.getline(lineData,10,',');
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
        //cout << temp << "\t" << pow(10,exp) << endl;
        if(exp==2) temp=temp*100;
        else temp = temp * pow(10, exp);   //multiply to put digit in the correct place
        //cout << index << "+" << temp << endl;
        index = index + temp;
        digits.pop();                   //remove following two digits
        digits.pop();
        exp-=1.0;                  //decrease exponent
    }

    temp = digits.top() * 10;
    digits.pop();
    index = index + temp + digits.top();
    //cout << index << "\t" << temp << "\t" << digits.top() << endl << endl;
    return index;
}

//to fix collisions
bool quad_probing_without_replacement(int key, int hash_table[], int M)
{
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
            if(hash_table[i]==0)                    //if new position is empty
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
    /* testing hash function
    cout << hash(123456789) << endl;
    cout << hash(987654321) << endl;
    cout << hash(100203001) << endl;
    */

    int *array_of_numbers = new int[65000];

    getFile("everybodys_socials.txt",array_of_numbers);     //read in SSNs to array

    int M;          //get M to use in quad probing
    cout << "Enter a number from 0 to 45,000,000: ";
    cin >> M;

    int nSS = 65000;        //nSS is the number of social security numbers;
    int *hash_table=new int [nSS];
    int index;

    for(int i=0;i<M;i++)    //initialize the hash table to contain 0s
        hash_table[i]=0;

    for(int i=0;i<M;i++)    //hash the elements in array_of_numbers into the hash_table
    {
        index=hash(array_of_numbers[i]);
        if(hash_table[index]==0)        //position is empty
            hash_table[index]=array_of_numbers[i];
        else                            //position is already filled -> collision!
        {
            cout << "COLLISION! Fear not... I'll resolve it!\n";
            quad_probing_without_replacement(array_of_numbers[i],hash_table,M);
        }
    }

    ofstream out;                               //open new o fstream to write results to
    out.open("hashed_socials.txt");


    for (int i=0; i<(nSS-1); i++)               //write out all but the last value of the hash_table
    {
        out << hash_table[i] << " , ";
    }

    out << hash_table[nSS-1] << endl;     //write out last value of the hash_table
    out.close();                                //close out fstream

    return 1;
}
