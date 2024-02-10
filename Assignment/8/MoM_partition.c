#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(short arr[], int initial, int final)
{
    for (int i = initial; i <= final; i++)
    {
        int value = arr[i];
        int pos = i - 1;
        while (pos >= initial && arr[pos] > value)
        {
            arr[pos + 1] = arr[pos];
            pos--;
        }
        arr[pos + 1] = value;
    }
}

int give_median(short arr[], int initial, int final)
{
    insertion_sort(arr, initial, final);
    int mid = (initial + final) / 2;
    return arr[mid];
}

int median_of_median(short arr[], int arr_size, int divide_size)
{
    if (arr_size < divide_size)
    {
        int median = give_median(arr, 0, arr_size - 1);
        return median;
    }

    int no_full_group = arr_size / divide_size;
    int elements_in_last = arr_size % divide_size;

    int next_arr_size;

    if (elements_in_last == 0)
        next_arr_size = no_full_group;
    else
        next_arr_size = no_full_group + 1;

    short next_arr[next_arr_size];

    for (int i = 0; i < next_arr_size; i++)
    {
        if (i == next_arr_size - 1)
            next_arr[i] = give_median(arr, divide_size * i, arr_size - 1);
        else
            next_arr[i] = give_median(arr, divide_size * i, divide_size * (i + 1) - 1);
    }

    return median_of_median(next_arr, next_arr_size, divide_size);
}

int main()
{
    srand(time(0));

    int arr_size = 10000;
    int num_iter = 10;
    double avg_time = 0;

    FILE *fout = fopen("MoM_obs.csv", "w");
    fprintf(fout, "partitions,time\n");

    int divide_size;

    short arr[arr_size];

    for (int obs_counter = 1; obs_counter <= 500; obs_counter++)
    {
        int partitions = 2 * obs_counter + 1;
        avg_time = 0;

        for (int i = 0; i < num_iter; i++)
        {
            for (int j = 0; j < arr_size; j++)
                arr[j] = rand() % 100;

            float start_time = clock();
            int temp = median_of_median(arr, arr_size, partitions);
            float end_time = clock();

            float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
            avg_time += time_taken;
        }

        avg_time = avg_time / num_iter;

        printf("Partitions: %4d Avg time: %.4f ms\n", divide_size,avg_time);
        fprintf(fout, "%d,%f\n", partitions, avg_time);
    }

    fclose(fout);
    return 0;
}