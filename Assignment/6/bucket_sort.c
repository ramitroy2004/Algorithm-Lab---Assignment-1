#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    float data;
    struct Node *next;
};

struct Node *newNode(float data) {
    struct Node *temp = (struct Node*) malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void insertSorted(struct Node **head, float data, long *count) {
    struct Node *current;
    struct Node *temp = newNode(data);
    if (*head == NULL || (*head)->data >= temp->data) {
        temp->next = *head;
        *head = temp;
        (*count)++;
    } else {
        current = *head;
        while (current->next != NULL && current->next->data < temp->data) {
            current = current->next;
            (*count)++;
        }
        temp->next = current->next;
        current->next = temp;
        (*count)++;
    }
}

void bucketSort(float arr[], int n, long *count) {
    struct Node **buckets = (struct Node**) malloc(n * sizeof(struct Node*));
    for (int i = 0; i < n; i++) {
        buckets[i] = NULL;
    }

    // Put elements into buckets
    for (int i = 0; i < n; i++) {
        int index = n * arr[i];
        insertSorted(&buckets[index], arr[i], count);
    }

    // Concatenate all the buckets
    int index = 0;
    for (int i = 0; i < n; i++) {
        struct Node *current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->data;
            current = current->next;
        }
    }

    // Deallocate memory
    for (int i = 0; i < n; i++) {
        struct Node *current = buckets[i];
        while (current != NULL) {
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(buckets);
}


int is_array_sorted(float *arr, int length)
{
    for (int i = 0; i < length - 1; i++)
        if (arr[i] > arr[i + 1])
            return 0;

    return 1;
}

void text_to_arr(float *arr, int n)
{

    FILE *fin = fopen("normalized_normal_data.csv", "r");
    char skip[10];
    fscanf(fin, "%s\n", skip);
    float temp = 0;
    for (int i = 0; i < n; i++)
    {
        int skip_line = rand() % 10;

        for (int j = 0; j < skip_line; j++)
            fscanf(fin, "%f\n", &temp);

        fscanf(fin, "%f\n", &temp);
        arr[i] = temp;
    }

    fclose(fin);
}

int main()
{
    srand(time(0));


    FILE* fp2 = fopen("observation_normal.csv", "w");

    int max_power = 17;
    int num_of_it = 100;

    if (fp2) {
        fprintf(fp2, "Input size,Comparisons,Time (ms)\n");
        // Start with 2^0 = 1 input and double size each time
        int inputSize = 2;
        for(int p = 0; p < max_power; p++){
            long total_comparisons = 0;
            float total_time = 0;
            for(int k = 0; k < num_of_it; k++){

                float input[inputSize];

                text_to_arr(input, inputSize);

                long comparisons = 0;
                
                // Record start time
                float start = clock();
                // Sort input data using Quick Sort
                bucketSort(input, inputSize, &comparisons);
                // Record end time
                float end = clock();
                // Calculate time taken in milliseconds
                float timeTaken = (end - start) * 1000 / CLOCKS_PER_SEC ;

                total_comparisons += comparisons;
                total_time += timeTaken;
                if (is_array_sorted(input, sizeof(input) / sizeof(int)) == 1)
                    printf("Num = %d Run %d: %d comparison, %0.4f ms\n", inputSize, k + 1, comparisons, timeTaken);
                else
                {
                    printf("Array Not Sorted\n");
                    break;
                }
            }

            long avg_comparisons = total_comparisons / num_of_it;
            float avg_time = (float)total_time / num_of_it;
            
            // Write results to output file
            fprintf(fp2, "%d,%ld,%0.4f\n", inputSize, avg_comparisons, avg_time);

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
