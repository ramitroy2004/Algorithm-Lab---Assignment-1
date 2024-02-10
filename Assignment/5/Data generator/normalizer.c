#include <stdio.h>
#include <math.h>

int main()
{
    int maxNo = 100;

    FILE *fin = fopen("uniform_data.csv", "r");
    FILE *fout = fopen("normalized_uniform_data.csv", "w");

    char temp[10];
    fprintf(fout, "values\n");
    fscanf(fin,"%s\n", temp);

    while(!feof(fin)){
        int tempNo = 0;
        fscanf(fin, "%d\n", &tempNo);
        fprintf(fout, "%0.2f\n", ((float)tempNo) / maxNo);
    }

    fclose(fin);
    fclose(fout);
}