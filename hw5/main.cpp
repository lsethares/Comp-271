#include <iostream>
#include <fstream>
#include <array>
#include <stdlib.h>

using namespace std;

/**read file to an array**/
/*
bool readFile(char* filename, int A[max])
{
    int i=0;
    char* temp;

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
        A[i] = atoi(temp);
        i++;
    }

    in.clear();
    in.close();
    return true;
}
*/

/**Bubble Sort**/
void bubblesort(int A[max], int n)
{
    int temp, n_comp, n_exch;
    n_exch = n_comp = 0;
    for (int i=1; i<n; i++)
    {
        for (int j=0; j<n-1; j++)
        {
            if (A[j]>A[j+1]) //Compare two successive numbers
            {
                temp = A[j];    //switch values if they are not in the correct order
                A[j] = A[j+1];
                A[j+1] = temp;
                n_exch++;       //increase counter for number of exchanges
            }
            n_comp++;           //increase count for number of comparisons
        }
    }
    cout << "Bubble Sort. Exchanges: " << n_exch << " Comparisons: " << n_comp << endl;
}

/**Insertion Sort**/
void InsertionSort(int A[], int n)
{
    int element, n_comp, n_exch;
    n_exch = n_comp = 0;
    for (int i =1; i<n; i++)
    {
        element = A[i];
        int j=i;
        while ((j>0)&&(A[j-1] > element)) //compare A[j-1] to A[i]
        {
            A[j] = A[j-1];      //shifts elements
            j=j-1;
            n_exch++;
        }
        n_comp++; //increase comparison counter
        A[j] = element;
    }
    cout << "Insertion Sort. Exchanges: " << n_exch << " Comparisons: " << n_comp << endl;
}

/**Quick Sort**/
/*
void quickSort(int A[], int low, int high)
{
    int k;
    if (low < high)//compare values
    {
        k = partitions(A, low, high);
        quickSort(A, low, j-1);
        quickSort(A, j+1, high);
    }
}

int partitions(int A[], int low, int high)
{
    int pivot, i, j;
    pivot=A[low];
    j=high+1;
    do
    {
        i++;
        while(A[i]<pivot && low<=high)
        do
        {
            j++;
        }
        while (pivot < A[j[]);
        if (i<j)
            swap(A[i], A[j]);
    }
    while (i<j);
    A[low] = A[j];
    A[j] = pivot;
    return j;
}
*/

/**Shell Sort**/
void shell_sort(int A[], int n)
{
    int temp, gap, i;
    int swapped;
    int n_exch, n_comp;
    n_exch = n_comp = 0;
    gap = n/2;
    do
    {
        do
        {
            swapped = 0;
            for (i=0; i<n-gap; i++)
            {
                if(A[i]>A[i+gap]) //compare to values
                {
                    //swap values
                    temp = A[i];
                    A[i]=A[i+gap];
                    A[i+gap]=temp;
                    swapped = 1;
                    n_exch++;
                }
                n_comp++;
            }
        } while(swapped == 1);
    } while ((gap = gap/2)>= 1);

    cout << "Insertion Sort. Exchanges: " << n_exch << " Comparisons: " << n_comp << endl;
}

/**Merge Sort**/
void mergeSort(int A[], int low, int high)
{
    int mid;
    if(low<high)
    {
        mid = (low+high)/2;
        mergeSort(A, low, mid);
        mergeSort(A, mid+1, high);
        merge(A, low, high, mid);
    }
}

int main()
{
    int Array_A[10000];

    //readFile("smallSample.txt", Array_A);
}
