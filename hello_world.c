#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// game size ist 16
#define N 16
u_int8_t state_1[N+2][N+2];
u_int8_t state_2[N+2][N+2];
u_int8_t* state_in_p=&state_1;
u_int8_t* state_out_p=&state_2;
u_int8_t* state_tmp_p=NULL;


void field_initializer()
{
    // fills fields with random numbers 0 = dead, 1 = alive
    srand(time(0));
    for (int i = 1; i < N+1; i++)
    {
        for (int j = 1; j < N+1; j++)
        {
            state_1[i][j] = rand() % 2;
        }
    }
    return;
}

// needs update
int calculate_next_gen_cell(int neighbours)
{
    // cell will be dead
    if (neighbours < 2 || neighbours > 3)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// needs update
void calculate_next_gen()
{
    int nextGen[N][N];

    // i = row, j = column
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // coi = Cell of Interest
            int coi = state_1[i][j];
            // create an array which contains all neighbours
            int neighbourCounter = 0;

            // coi is left, top edge
            if (!i && !j)
            {
                if (state_1[0][1])
                {
                    neighbourCounter++;
                }
                else if (state_1[1][1])
                {
                    neighbourCounter++;
                }
                else if (state_1[1][0])
                {
                    neighbourCounter++;
                }
                nextGen[i][j] = calculate_next_gen_cell(neighbourCounter);
            }
        }
    }
    return;
}

int main()
{
    field_initializer();
    // print 2D array
    for (int i = 0; i < N+2; i++)
    {
        for (int j = 0; j < N+2; j++)
        {
            printf("%d ", state_1[i][j]);
        }
        printf("\n");
    }
    printf("Array size is: %lu\n", (sizeof(state_1) / sizeof(u_int8_t)) / (N+2));
    return 0;
}