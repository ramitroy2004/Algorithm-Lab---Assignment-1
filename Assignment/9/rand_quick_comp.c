#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


// An utility function to swap two int values
void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int partition(int arr[], int start, int final, long *comparisons)
{
    int pivot_index = start + rand() % (final - start + 1);
    int pivot_value = arr[pivot_index];

    int i = start;
    int j = final;

    while(true)
    {
        while (arr[i] < pivot_value)
            i++;

        while (pivot_value < arr[j])
            j--;

        if (arr[i] == arr[j])
        {
            if (i == j)
                return i;
            else
                j--;
        }
        else if (i < j)
        {
            swap(&arr[i], &arr[j]);
            (*comparisons)++;
        }
        else
            return i;
    }
}

void quickSort(int *arr, int start, int final, long *comparisons)
{
    if (start < final)
    {
        int pivot_index = partition(arr, start, final, comparisons);
        quickSort(arr, start, pivot_index, comparisons);
        quickSort(arr, pivot_index + 1, final, comparisons);
    }
}

//assuming 1 is true, 0 is false
int is_array_sorted(int *arr, int length)
{
    for (int i = 0; i < length - 1; i++)
        if (arr[i] > arr[i + 1])
            return 0;

    return 1;
}

void text_to_arr(int *arr, int n)
{

    FILE *fin = fopen("normal_data.csv", "r");

    int temp = 0;

    char temp2[10];
    fscanf(fin, "%s\n", temp2);
    
    for (int i = 0; i < n; i++)
    {
        int skip_line = rand() % 10;

        for (int j = 0; j < skip_line; j++)
            fscanf(fin, "%d\n", &temp);

        fscanf(fin, "%d\n", &temp);
        arr[i] = (int)temp;
    }

    fclose(fin);
}

int main()
{
    srand(time(0));


    FILE* fp2 = fopen("observation_normal.csv", "w");

    int max_power = 13;
    int num_of_it = 50;

    if (fp2) {
        fprintf(fp2, "Input size,Best,Worst\n");
        // Start with 2^0 = 1 input and double size each time
        int inputSize = 8;
        for(int p = 0; p < max_power; p++){
            float best_comparison = __INT_MAX__;
            float worst_comparison = 0;

            int input[inputSize];

            text_to_arr(input, inputSize);

            for(int k = 0; k < num_of_it; k++){

                float time = 0;
                
                float start = clock();
                long comparisons = 0;
                // Sort input data using Quick Sort
                quickSort(input, 0, inputSize - 1, &comparisons);
                float end = clock();

                time = (end - start) * 1000 / CLOCKS_PER_SEC;

                if (comparisons > worst_comparison)
                    worst_comparison = comparisons;
                
                if(comparisons < best_comparison)
                    best_comparison = comparisons;
                
                if (is_array_sorted(input, sizeof(input) / sizeof(int)) == 1)
                    printf("Num = %d Run %d: %.4f time, %ld comparisons\n", inputSize, k + 1, time, comparisons);
                else
                {
                    printf("Array Not Sorted\n");
                    break;
                }

                for (int i = inputSize-1; i >= 0; --i){
                    //generate a random number [0, n-1]
                    int j = rand() % (i+1);

                    //swap the last element with element at random index
                    int temp = input[i];
                    input[i] = input[j];
                    input[j] = temp;
                }
            }

            fprintf(fp2, "%d,%.5f,%.5f\n",inputSize, best_comparison, worst_comparison);

            // Double input size for next iteration
            inputSize *= 2;
        }
        fclose(fp2);
    } else {
        printf("Failed to open output file: %s\n", "failed.csv");
        return 1;
    }


    return 0;
}