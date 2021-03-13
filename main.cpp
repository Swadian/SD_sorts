#include <fstream>
#include <time.h>
#include <windows.h>
#include <cstring>
using namespace std;
    int k;
    int v[10000];
    int backup[10000];
    int aux[10000];//pt countsort

    ofstream fout("rez.txt");
    time_t t;

    void restoreBackup()
    {
        for (int i=0;i<k;i++)
            v[i]=backup[i];
    }
    void output()
{
    for (int i=0;i<k;i++)
        fout<<v[i]<<' ';
    fout<<'\n';
    fout<<"timp: "<<((double)t)/CLOCKS_PER_SEC<<endl;

}


void bubbleS()
{
    fout<<"Bubble sort:"<<'\n';
    bool sorted=true;
    do
    {
        sorted=true;
        for (int i=0;i<k-1;i++)
            if(v[i]>v[i+1])
                {swap(v[i],v[i+1]);sorted=false;}
    }
    while(!sorted);
}

void countS()
{
    fout<<"Count sort:"<<'\n';
    for (int i=0;i<k;i++)
        aux[v[i]]++;
    int kk=0;
    for(int i=0;i<10000;i++)
    while(aux[i]>0)
        {
            v[kk++]=i;
            aux[i]--;
        }
}

void LSD(int exp)
//cu implementare de counting sort
{
    int output[k]; // output array
    int i, contor[10] = { 0 };

    // incrementz numarul de elemente cu cifra respectiva
    for (i = 0; i < k; i++)
        contor[(v[i] / exp) % 10]++;

    // Change contor[i] so that contor[i] now contains actual
    //  position of this digit in output[]
    //decalez contoarele unul in functie de celalalt
    for (i = 1; i < 10; i++)
        contor[i] += contor[i - 1];

    // Build the output array
    //iau termenii din vector si ii pun in output in functie de bucketuri
    for (i = k - 1; i >= 0; i--) {
        output[contor[(v[i] / exp) % 10] - 1] = v[i];
        contor[(v[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < k; i++)
        v[i] = output[i];


}
void radixS()
{
    fout<<"Radix Sort:"<<'\n';
    //aflu numarul maxim din vector
    int nmax=v[0];
    for (int i=0;i<k;i++)
        if (v[i]>nmax)
            nmax=v[i];

    //fac cate o sortare pentru fiecare exponent
    for(int exp=1;nmax/exp>0;exp*=10)
        LSD(exp);



}
//Radix code credit: https://www.geeksforgeeks.org/radix-sort/
void interc(int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp vays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];

    // Merge the temp arrays back into v[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int w = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[w] = L[i];
            i++;
        }
        else {
            v[w] = R[j];
            j++;
        }
        w++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        v[w] = L[i];
        i++;
        w++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        v[w] = R[j];
        j++;
        w++;
    }
}


void mergeS(int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m =l+ (r-l)/2;
    mergeS(l,m);
    mergeS(m+1,r);
    interc(l,m,r);
}
//merge sort code credit: https://www.geeksforgeeks.org/merge-sort/

int pivot(int l,int r){
//selectarea medianei din 3
int m =l+ (r-l)/2;
int med,medi;//mediana si pozitia ei
    if ((v[l] < v[m] && v[m] < v[r]) || (v[r] < v[m] && v[m] < v[l]))
       {med=v[m];medi=m;
       swap(v[m],v[r]);medi=r;
       }
    else if ((v[m] < v[l] && v[l] < v[r]) || (v[r] < v[l] && v[l] < v[m]))
       {
           med=v[l];medi=l;
           swap(v[l],v[r]);medi=r;

       }
    else
       {
        med=v[r];medi=r;
       }
       int i=l-1 ;//pozitia pe care trebuie sa ajunga pivotul
    for(int j=l;j<r;j++)
    {

        if(v[j]<med)
        {
            i++;
            swap(v[i],v[j]);
        }
    }
    swap(v[i+1],v[medi]);
    return (i+1);
}

void quickS(int l,int r){
    if(l<r)
    {
    int piv=pivot(l,r);
    quickS(l,piv-1);
    quickS(piv+1,r);
    }

}

void input(string filename)
{
        ifstream fin(filename);
    //input -- direct vectorul de sortat, fara marime
    k=0;
    while(!fin.eof())
        {fin>>v[k];
        backup[k]=v[k];
        k++;}
        fin.close();

}
void runSorts()
{
    //Bubble Sort
    t=clock();
    bubbleS();
    Sleep(1);
    t= clock()-t;
    output();
    restoreBackup();
    //Count Sort
    t=clock();
    countS();
    Sleep(1);
    t= clock()-t;
    output();
    restoreBackup();
    //Merge Sort
    fout<<"Merge Sort:"<<'\n';
    t=clock();
    mergeS(0,k-1);
    Sleep(1);
    t= clock()-t;
    output();
    restoreBackup();
    //Quick Sort
    fout<<"Quick Sort:"<<'\n';
    t=clock();
    quickS(0,k-1);
    Sleep(1);
    t= clock()-t;
    output();
    restoreBackup();
    //Radix LSD sort
    t=clock();
    radixS();
    Sleep(1);
    t= clock()-t;
    output();
    restoreBackup();

    fout<<'\n';

}
int main()
{
    ifstream files("files.txt");
    int n;
    files>>n;
    string fisier;
    for (int i=0;i<n;i++)
    {
        files>>fisier;
        input(fisier);
        runSorts();
    }
    fout.close();
    return 0;
}
