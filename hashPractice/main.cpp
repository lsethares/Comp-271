#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

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

int division_method(int val, int M)
{
    return val%M;
}

bool linear_probing_with_replacement(int key, int hash_table[], int M)
{
    /** WRITE THIS FUNCTION. IT SHOULD RETURN TRUE IF THE VALUE IS ADDED, FALSE IF THE HASH
    TABLE IS FULL (I.E. THERE ARE NO MORE PLACES FOR THE DATA TO BE ENTERED).
    DON'T FORGET THIS IS LINEAR PROBING WITH REPLACEMENT. **/
    int pos, i;
    pos = division_method(key, M);
    if(hash_table[pos]==0)  //if space is empty
    {
        hash_table[pos]=key;
        return true;
    }
    else                    //if space is not empty
    {
        if (division_method(hash_table[pos], M)==pos)      //and the present int is in its correct spot
        {
            for(i=pos+1; i%M!=pos; i++)     //put key in the next empty place
            {
                if(hash_table[i]==0)
                {
                    hash_table[i]=key;
                    return true;
                }
            }
        }
        else            //if the present int is not in its proper place
        {
            int temp;
            temp = hash_table[pos];     //store the present int
            hash_table[pos]=key;        //put key in its proper place

            for(i=pos+1; i%M!=pos; i++)     //put old int in the next empty place
            {
                if(hash_table[i]==0)
                {
                    hash_table[i]=temp;
                    return true;
                }
            }

        }
    }
    return false;       //table overflow
}

int main()
{
    int * array_of_numbers;
    int index;

    getFile("sample_numbers.txt",array_of_numbers);

    int M=500;
    int *hash_table=new int [500];

    for(int i=0;i<M;i++)    //initialize the hash table to contain 0s
        hash_table[i]=0;

    for(int i=0;i<M;i++)    //hash the elements in array_of_numbers into the hash_table
    {
        index=division_method(array_of_numbers[i],M);
        if(hash_table[index]==0)
            hash_table[index]=array_of_numbers[i];
        else
        {
            cout << "COLLISION! Fear not... I'll resolve it!\n";
            linear_probing_with_replacement(array_of_numbers[i],hash_table,M);
        }
    }

    return 1;
}
