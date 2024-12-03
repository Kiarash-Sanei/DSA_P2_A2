#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct list 
{
    int* leftTowers;
    int leftSize;
    int* rightTowers;
    int rightSize;
} list;

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
        possible[0].leftSize = 0;
        possible[0].leftTowers = NULL;
        for (int j = 1; j < peopleCount; j++)
        {
            if (possible[j - 1].leftSize != 0)
            {
                possible[j].leftSize = 0;
                possible[j].leftTowers = (int*) malloc((possible[j - 1].leftSize + 1) * sizeof(int));
                for (int k = 0; k < possible[j - 1].leftSize; k++)
                {
                    if (possible[j - 1].leftTowers[k] >= towers[j - 1][0])
                    {
                        possible[j].leftTowers[possible[j].leftSize] = possible[j - 1].leftTowers[k];
                        possible[j].leftSize++;
                    }
                }
                possible[j].leftTowers[possible[j].leftSize] = j - 1;
                possible[j].leftSize++;
            }
            else 
            {
                possible[j].leftSize = 1;
                possible[j].leftTowers = (int*) malloc(sizeof(int));
                possible[j].leftTowers[0] = j - 1;
            }
        }
        possible[peopleCount - 1].rightSize = 0;
        possible[peopleCount - 1].rightTowers = NULL;
        for (int j = peopleCount - 2; j >= 0; j--)
        {
            if (possible[j + 1].rightSize != 0)
            {
                possible[j].rightSize = 0;
                possible[j].rightTowers = (int*) malloc((possible[j + 1].rightSize + 1) * sizeof(int));
                for (int k = 0; k < possible[j + 1].rightSize; k++)
                {
                    if (possible[j + 1].rightTowers[k] >= towers[j + 1][0])
                    {
                        possible[j].rightTowers[possible[j].rightSize] = possible[j - 1].rightTowers[k];
                        possible[j].rightSize++;
                    }
                }
                possible[j].rightTowers[possible[j].rightSize] = j - 1;
                possible[j].rightSize++;
            }
            else 
            {
                possible[j].rightSize = 1;
                possible[j].rightTowers = (int*) malloc(sizeof(int));
                possible[j].rightTowers[0] = j - 1;
            }
        }
        for (int j = 0; j < peopleCount; j++)
        {
            int hit = 0;
            for (int k = 0; k < possible[j].leftSize; k++)
            {
                hit += towers[possible[j].leftTowers[k]][2];
            }
            for (int k = 0; k < possible[j].rightSize; k++)
            {
                hit += towers[possible[j].rightTowers[k]][2];
            }
            double result = ((double) towers[j][1]) / ((double) hit);
            printf("%.0lf ", ceil(result));
        }
        for (int j = 0; j < peopleCount; j++)
        {
            free(possible[j].leftTowers);
            free(possible[j].rightTowers);
        }
        printf("\n");
    }
}