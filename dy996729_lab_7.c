#include <stdio.h>

void bubbleSort(int arr[], int n) 
{

   int i, j, temp, swaps[n];

   for (i = 0; i < n; i++)

      swaps[i] = 0;

   for (i = 0; i < n-1; i++)
   {

       for (j = 0; j < n-i-1; j++)
       {
           if (arr[j] > arr[j+1])
           {

              temp = arr[j];
              arr[j] = arr[j+1];
              arr[j+1] = temp;
              swaps[j]++;

           }//end if

       }//end for j

   }//end for i

   for (i = 0; i < n; i++)

      printf("Swaps needed for index %d: %d\n", i, swaps[i]);

}//end bubbleSort

int main()
{

   int arr[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
   int n = sizeof(arr)/sizeof(arr[0]);
   bubbleSort(arr, n);

   return 0;

}//end main