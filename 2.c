#include <stdio.h>
#include <math.h>

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
        for (int j = 0; j < peopleCount; j++)
        {
            int hit = 0;
            int neededHeight = 0;
            for (int k = j - 1; k >= 0; k--)
            {
                if (towers[k][0] >= neededHeight)
                {
                    hit += towers[k][2];
                    neededHeight = towers[k][0];
                }
            }
            neededHeight = 0;
            for (int k = j + 1; k < peopleCount; k++)
            {
                if (towers[k][0] >= neededHeight)
                {
                    hit += towers[k][2];
                    neededHeight = towers[k][0];
                }
            }
            double result = ((double) towers[j][1]) / ((double) hit);
            printf("%.0lf ",ceil(result));
        }
        printf("\n");
    }
}