#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct list
{
    int *leftTowers;
    int leftSize;
    int *rightTowers;
    int rightSize;
} list;

void leftCalculator(list *possible, int towers[][3], int peopleCount)
{
    possible[0].leftSize = 0;
    possible[0].leftTowers = NULL;
    for (int i = 1; i < peopleCount; i++)
    {
        if (possible[i - 1].leftSize != 0)
        {
            possible[i].leftSize = 0;
            possible[i].leftTowers = (int *)malloc((possible[i - 1].leftSize + 1) * sizeof(int));
            for (int j = 0; j < possible[i - 1].leftSize; j++)
            {
                if (towers[possible[i - 1].leftTowers[j]][0] >= towers[i - 1][0])
                {
                    possible[i].leftTowers[possible[i].leftSize] = possible[i - 1].leftTowers[j];
                    possible[i].leftSize++;
                }
            }
            possible[i].leftTowers[possible[i].leftSize] = i - 1;
            possible[i].leftSize++;
        }
        else
        {
            possible[i].leftSize = 1;
            possible[i].leftTowers = (int *)malloc(sizeof(int));
            possible[i].leftTowers[0] = i - 1;
        }
    }
}

void rightCalculator(list *possible, int towers[][3], int peopleCount)
{
    possible[peopleCount - 1].rightSize = 0;
    possible[peopleCount - 1].rightTowers = NULL;
    for (int i = peopleCount - 2; i >= 0; i--)
    {
        if (possible[i + 1].rightSize != 0)
        {
            possible[i].rightSize = 0;
            possible[i].rightTowers = (int *)malloc((possible[i + 1].rightSize + 1) * sizeof(int));
            for (int j = 0; j < possible[i + 1].rightSize; j++)
            {
                if (towers[possible[i + 1].rightTowers[j]][0] >= towers[i + 1][0])
                {
                    possible[i].rightTowers[possible[i].rightSize] = possible[i + 1].rightTowers[j];
                    possible[i].rightSize++;
                }
            }
            possible[i].rightTowers[possible[i].rightSize] = i + 1;
            possible[i].rightSize++;
        }
        else
        {
            possible[i].rightSize = 1;
            possible[i].rightTowers = (int *)malloc(sizeof(int));
            possible[i].rightTowers[0] = i + 1;
        }
    }
}

void printer(list *possible, int towers[][3], int peopleCount)
{
    for (int i = 0; i < peopleCount; i++)
    {
        int hit = 0;
        for (int j = 0; j < possible[i].leftSize; j++)
        {
            hit += towers[possible[i].leftTowers[j]][2];
        }
        for (int j = 0; j < possible[i].rightSize; j++)
        {
            hit += towers[possible[i].rightTowers[j]][2];
        }
        double result = ((double)towers[i][1]) / ((double)hit);
        printf("%.0lf ", ceil(result));
    }
    printf("\n");
}

void freeMemory(list *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(array[i].leftTowers);
        free(array[i].rightTowers);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int peopleCount;
        scanf("%d", &peopleCount);

        int towers[peopleCount][3];
        for (int j = 0; j < peopleCount; j++)
        {
            scanf("%d %d %d", towers[j], towers[j] + 1, towers[j] + 2);
        }

        list possible[peopleCount];

        leftCalculator(possible, towers, peopleCount);

        rightCalculator(possible, towers, peopleCount);

        printer(possible, towers, peopleCount);

        freeMemory(possible, peopleCount);
    }
}