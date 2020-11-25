#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//game size ist 32
#define N 32
u_int16_t const repetitions = 3;
//write output files
u_int8_t const write_output = 1;

u_int8_t state_1[N + 2][N + 2];
u_int8_t state_2[N + 2][N + 2];

u_int8_t (*state_in)[N + 2][N + 2] = &state_1;
u_int8_t (*state_out)[N + 2][N + 2] = &state_2;
u_int8_t (*state_tmp)[N + 2][N + 2] = NULL;

void field_initializer()
{
    //fills fields with random numbers 0 = dead, 1 = alive
    srand(time(0));
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < N + 1; j++)
        {
            state_1[i][j] = rand() % 2;
        }
    }
    return;
}

void calculate_next_gen(u_int8_t (*state)[N + 2][N + 2], u_int8_t (*state_old)[N + 2][N + 2])
{
    //i = row, j = column
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < N + 1; j++)
        {
            //count up a number (8)
            u_int8_t sum_of_8 = (*state_old)[i - 1][j - 1] + (*state_old)[i - 1][j] + (*state_old)[i - 1][j + 1] + (*state_old)[i][j - 1] + (*state_old)[i][j + 1] + (*state_old)[i + 1][j - 1] + (*state_old)[i + 1][j] + (*state_old)[i + 1][j + 1];
            (*state)[i][j] = (sum_of_8 == 3) || ((sum_of_8 == 2) && (*state_old)[i][j]);
        }
    }
    return;
}

void write_pbm_file(u_int8_t (*state)[N + 2][N + 2], int i)
{
    FILE *fptr;
    char filename[20];
    sprintf(filename, "output%d.pbm", i);
    fptr = fopen(filename, "w");
    fprintf(fptr, "P1\n");
    fprintf(fptr, "# This is the result. Have fun :)\n");
    fprintf(fptr, "%d %d\n", N, N);
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < N + 1; j++)
        {
            fprintf(fptr, "%d ", (*state)[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    return;
}

int main()
{
    field_initializer();
    //print 2D array
    for (int i = 0; i < N + 2; i++)
    {
        for (int j = 0; j < N + 2; j++)
        {
            printf("%d ", state_1[i][j]);
        }
        printf("\n");
    }
    printf("Array size is: %lu\n", (sizeof(state_1) / sizeof(u_int8_t)) / (N + 2));
    printf("%d repetitions:\n", repetitions);
    //calculation
    for (int i = 0; i < repetitions; i++)
    {   
        calculate_next_gen(state_out, state_in);
        state_tmp = state_in;
        state_in = state_out;
        state_out = state_tmp;
        if (write_output)
        {
            write_pbm_file(state_in, i);
        }
    }
    printf("Done.\n");
    exit(0);
}