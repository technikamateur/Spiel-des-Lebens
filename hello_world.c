#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// game size ist 16
#define N 16
u_int8_t state_1[N + 2][N + 2];
u_int8_t state_2[N + 2][N + 2];
u_int8_t *state_in_p = &state_1;
u_int8_t *state_out_p = &state_2;
u_int8_t *state_tmp_p = NULL;

void field_initializer()
{
    // fills fields with random numbers 0 = dead, 1 = alive
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

// needs update
void calculate_next_gen()
{
    // i = row, j = column
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < N + 1; j++)
        {
            // count up a number (8)
            u_int8_t sum_of_8 = state_1[i - 1][j - 1] + state_1[i - 1][j] + state_1[i - 1][j + 1] + state_1[i][j - 1] + state_1[i][j + 1] + state_1[i + 1][j - 1] + state_1[i + 1][j] + state_1[i + 1][j + 1];
            state_2[i][j] = (sum_of_8 == 3) || ((sum_of_8 == 2) && state_1[i][j]);
        }
    }
    return;
}

int main()
{
    field_initializer();
    // print 2D array
    for (int i = 0; i < N + 2; i++)
    {
        for (int j = 0; j < N + 2; j++)
        {
            printf("%d ", state_1[i][j]);
        }
        printf("\n");
    }
    printf("Array size is: %lu\n", (sizeof(state_1) / sizeof(u_int8_t)) / (N + 2));
    printf("After one repetition:\n");
    calculate_next_gen();
    for (int i = 0; i < N + 2; i++)
    {
        for (int j = 0; j < N + 2; j++)
        {
            printf("%d ", state_2[i][j]);
        }
        printf("\n");
    }
    printf("done");
    exit(0);
}