#include <stdio.h>

void quickSort(int number[],int first,int last){

    int i, j, pivot, temp;

    if(first<last){
        pivot=first;
        i=first;
        j=last;

        while(i<j){

            while(number[i]<=number[pivot]&&i<last)
                i++;
            while(number[j]>number[pivot])
                j--;

            if(i<j){
                temp=number[i];
                number[i]=number[j];
                number[j]=temp;
                //(*count)++;
            }
        }

        temp=number[pivot];
        number[pivot]=number[j];
        number[j]=temp;
        //(*count)++;

        quickSort(number,first,j-1);
        quickSort(number,j+1,last);
    }

}


void printArr(int arr[], int n){
	for(int i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}

	printf("\n");
}

int main()
{
	int arr[] = {2, 9, 22, 11, 12, 67, 1};
	printArr(arr, 7);

	quickSort(arr, 0, 6);

	printArr(arr, 7);
}
