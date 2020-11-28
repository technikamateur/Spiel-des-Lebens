#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//game size ist 32
#define N 2048
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
#pragma omp parallel for collapse(2)
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
#pragma omp parallel for collapse(2)
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
#pragma omp parallel for
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

void read_pbm_file()
{
    FILE *fptr;
    fptr = fopen("input.pbm", "r");
    if (fptr == NULL)
    {
        perror("Using random data. Unable to open input.pbm");
        return;
    }
    printf("Found valid input file.\n");
    char line[66];
    u_int8_t line_count = 1;
    while (fgets(line, 66, fptr))
    {
        if (line[0] == 48 || line[0] == 49)
        {
            //printf("line[%02d]: %s", line_count, line);
            u_int8_t z = 0;
#pragma omp parallel for
            for (int j = 1; j < N + 1; j++)
            {
                if (line[z] == 48)
                {
                    state_1[line_count][j] = 0;
                }
                else
                {
                    state_1[line_count][j] = 1;
                }
                z += 2;
            }
            line_count++;
        }
    }
    fclose(fptr);
    return;
}

int main()
{
    printf("Defined array size is: %lu\n", ((sizeof(state_1) / sizeof(u_int8_t)) / (N + 2) - 2));
    printf("%d repetitions\n", repetitions);
    field_initializer();
    read_pbm_file();
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