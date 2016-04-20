#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
//#include <stdio.h>

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

/**Bubble Sort**/
void bubblesort(int A[], int n)
{
    int temp, n_comp, n_exch;
    n_comp = n_exch =0;
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
//function partition to be called in quickSort
int partition(int A[], int low, int high)
{
    int pivot, i, j, n_comp, n_exch;
    pivot=A[low];
    j=high+1;
    do
    {
        i++;
        while(A[i]<pivot && low<=high)
        do
        {
            j++;
            n_comp++;
        } while (pivot < A[j]);
        if (i<j)
        {
            swap(A[i], A[j]);
            n_exch++;
        }
    }
    while (i<j);
    A[low] = A[j];
    A[j] = pivot;
    return j;
}

void quickSort(int A[], int low, int high)
{
    int k;
    int n_comp;
    int n_exch;
    if (low < high)//compare values
    {
        n_comp++;
        k = partition(A, low, high);
        quickSort(A, low, k-1);
        quickSort(A, k+1, high);
    }
    cout << "Quick Sort. Exchanges: " << n_exch << " Comparisons: " << n_comp << endl;
}

/**Shell Sort**/
void shell_sort(int A[], int n)
{
    int temp, gap, i;
    int swapped;
    int n_comp;
    int n_exch;
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
                    n_exch++;
                    temp = A[i];
                    A[i]=A[i+gap];
                    A[i+gap]=temp;
                    swapped = 1;
                }
                n_comp++;
            }
        } while(swapped == 1);
    } while ((gap = gap/2)>= 1);

    cout << "Shell Sort. Exchanges: " << n_exch << " Comparisons: " << n_comp << endl;
}

/**Merge Sort**/
//function merge to be called in mergeSort
void merge(int A[], int low, int high, int mid)
{
    int n_comp;
    int n_exch;

    int i, j, k, C[10000];
    i = low;
    j = mid + 1;
    k = 0;
    while((i<=mid) && (j<=high))
    {
        n_comp++;
        if (A[i] < A[j])
        {
            C[k]=A[i++];
            n_exch++;
        }
        else
        {
            C[k]=A[j++];
            n_exch++;
        }
        k++;
    }
    while (i<=mid)
        C[k++]=A[i++];
    while (j<=high)
        C[k++]=A[j++];
    for (i=low, j=0; i<=high; i++, j++)
    {
        A[i] = C[j];
    }
}

void mergeSort(int A[], int low, int high)
{
    int n_exch;
    int n_comp;

    int mid;
    if(low<high)
    {
        n_comp++;
        mid = (low+high)/2;
        mergeSort(A, low, mid);
        mergeSort(A, mid+1, high);
        merge(A, low, high, mid);
    }
    else
        cout << "Merge Sort. Exchanges: " << n_exch << " Comparisons: " << n_comp << endl;
}

int main()
{
    cout << "Few Unique" << endl;
    //apply to few unique
    int fewU[10000];
    readFile("fewUnique.txt", fewU);

    bubblesort(fewU, 10000);
    InsertionSort(fewU, 10000);
    //quickSort(fewU, 0, 10000);
    shell_sort(fewU, 10000);
    //mergeSort(fewU, 0, 10000);

    cout<<"\nNearly Sorted"<<endl;

    //apply to nearly sorted
    int nSorted[10000];
    readFile("nearlySorted.txt", nSorted);

    bubblesort(nSorted, 10000);
    InsertionSort(nSorted, 10000);
    //quickSort(nSorted, 0, 10000);
    shell_sort(nSorted, 10000);
    //mergeSort(nSorted, 0, 10000);

    cout<<"\nReversed" << endl;

    //apply to reversed
    int rev[10000];
    readFile("Reversed.txt", rev);

    bubblesort(rev, 10000);
    InsertionSort(rev, 10000);
    //quickSort(rev, 0, 10000);
    shell_sort(rev, 10000);
    //mergeSort(rev, 0, 10000);

    cout<<"\nRandom" << endl;

    //apply to random file
    int rand[10000];
    readFile("Random.txt", rand);

    bubblesort(rand, 10000);
    InsertionSort(rand, 10000);
    //quickSort(rand, 0, 10000);
    shell_sort(rand, 10000);
    //mergeSort(rand, 0, 10000);



}
