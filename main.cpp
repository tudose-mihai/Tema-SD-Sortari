#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

ifstream in ("input.in");
ofstream out ("output.out");

int v[100000001],copie_v[100000001], frv[2147483649]; //100M


void generator(int *arr, int n, int m) {
    arr[1] = 3242 % m;
    int prime = 100207;
    for (int i = 2; i <= n; i++) {

        arr[i] = (rand() % m) + 1;;
    }
    out << "Nr. elemente: " << n << '\n';
    out << "Element maxim: " << m << '\n';
}
void testSort(int *v, int n) {
    bool ok = 1;
    for (int i = 1; i < n; i++)
        if (v[i] > v[i + 1]) {
            ok = 0;
            break;
        }
    if (ok == 1)
        out << "sortat";
    else
        out << "eroare sort";
    out << '\n';
}
void bubbleSort(int *v, int n) {

    bool ok = 0;
    while (!ok) {
        ok = 1;
        for (int i = 1; i <= n; i++) {
            if (v[i] > v[i + 1]) {
                int aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                ok = 0;
            }
        }
    }
}
void merge(int *arr, int left, int mid, int right)
{
    int i=left,j=mid+1,k=1;
    int temp_arr[right-left+1];
    while(i<=mid && j<=right){
        if(arr[i]<arr[j])
        {
            temp_arr[k]=arr[i];
            i++;
            k++;
        } else
        {
            temp_arr[k]=arr[j];
            j++;
            k++;
        }
    }
    while(i<=mid) {
        temp_arr[k] = arr[i];
        i++;
        k++;
    }
    while(j<=right)
    {
        temp_arr[k]=arr[j];
        j++;
        k++;
    }
    for(i=left;i<=right;i++)
        arr[i]=temp_arr[i-left+1];
}
void mergeSort(int *arr, int left, int right){
    int middle=(left+right)/2;
    if(left<right)
    {
        mergeSort(arr, left, middle);
        mergeSort(arr, middle+1, right);

        merge(arr,left, middle, right);
    }
}
int partition (int *arr, int left, int right)
{
    int pivot=arr[right];
    int i,j=left-1;

    for(i=left;i<=right-1;i++)
    {
        if(arr[i]<=pivot)
        {
            j++;
            int aux=arr[i];
            arr[i]=arr[j];
            arr[j]=aux;
        }
    }
    j++;
    int aux=arr[right];
    arr[right]=arr[j];
    arr[j]=aux;
    return j;
}
void quickSort(int *arr, int left, int right)
{
    int pivot;
    if(left<right)
    {
        pivot= partition(arr, left, right);
        quickSort(arr, left, pivot-1);
        quickSort(arr, pivot+1, right);
    }
}
void countSort(int *arr, int n)
{
    int maxi=0;
    for(int i=1; i <=n; i++)
    {
        frv[arr[i]]++;
        maxi=max(maxi,arr[i]);
    }
    int j=1;
    for(int i=1;i <=maxi;i++)
    {
        for(;frv[i];frv[i]--)
            arr[j++]=i;
    }
}
void radixSort (int *arr, int n, int base){
    int i, exp=1, maxi=arr[1];
    int arr_temp[n],rest[1024];

    for(i=1;i<=n;i++)
        maxi=max(maxi,arr[i]);

    for(i=1;i<=n;i++)
        arr_temp[i]=0;

    while(maxi/exp > 0){
        for(i=0;i<base;i++)
            rest[i]=0;
        for(i=1;i<=n;i++)
            rest[arr[i]/exp % base]++;
        for(i=1;i<base;i++)
            rest[i]=rest[i]+rest[i-1];
        for(i=n;i>=1;i--)
        {

            arr_temp[rest[arr[i]/exp % base]] = arr[i];
            rest[arr[i]/exp % base]--;
        }
        for(i=1; i<=n; i++)
            arr[i]=arr_temp[i];
        exp = exp * base;
    }

}
int main(){

    int test,exp=1;
    int nr_prime[]={0,7,97,991,8941,78721,281683,7654567,31377173,608888809};

    for(test =1; test<=5; test++)
    {

        auto start = chrono::high_resolution_clock::now();
        generator(v,exp,nr_prime[test]);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        out << "Timp generare: " << duration.count() << " ms\n";
        out <<'\n';

        for(int i=1;i<=exp;i++)
            copie_v[i]=v[i];


      start = chrono::high_resolution_clock::now();
      bubbleSort(v,exp);
      stop = chrono::high_resolution_clock::now();
      duration = duration_cast<milliseconds>(stop - start);
      out << "bubbleSort: " << duration.count() << " ms ";
      testSort(v,exp);

        exp*=10;
        out << '\n' << '\n';

        }
    exp=1;

    for(test =1; test<=7; test++)
    {

        auto start = chrono::high_resolution_clock::now();
        generator(v,exp,nr_prime[test]);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        out << "Timp generare: " << duration.count() << " ms\n";
        out <<'\n';

        for(int i=1;i<=exp;i++)
            copie_v[i]=v[i];

        for(int i=1;i<=exp;i++)
            v[i]=copie_v[i];

        start = chrono::high_resolution_clock::now();
        mergeSort(v,1,exp);
        stop = chrono::high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        out << "mergeSort:  " << duration.count() << " ms ";
        testSort(v,exp);

        for(int i=1;i<=exp;i++)
            v[i]=copie_v[i];


        start = chrono::high_resolution_clock::now();
        quickSort(v,1,exp);
        stop = chrono::high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        out << "quickSort:  " << duration.count() << " ms ";
        testSort(v,exp);

        for(int i=1;i<=exp;i++)
            v[i]=copie_v[i];
        start = chrono::high_resolution_clock::now();
        countSort(v,exp);
        stop = chrono::high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        out << "countSort:  " << duration.count() << " ms ";
        testSort(v,exp);

        for(int i=1;i<=exp;i++)
            v[i]=copie_v[i];

        start = chrono::high_resolution_clock::now();
        radixSort(v,exp,256);
        stop = chrono::high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        out << "radixSort:  " << duration.count() << " ms ";
        testSort(v,exp);

        for(int i=1;i<=exp;i++)
            v[i]=copie_v[i];

        exp*=10;
        out << '\n' << '\n';
    }





    return 0;
}


