#include <stdio.h>

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
            for (int k = 0; k < peopleCount; k++)
            {
                if (k < j)
                {
                    int flag = 1;
                    for (int m = k + 1; m < j; m++)
                    {
                        if (towers[m][0] > towers[k][0])
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag)
                    {
                        hit += towers[k][2];
                    }
                }
                else if (k > j)
                {
                    int flag = 1;
                    for (int m = j + 1; m < k; m++)
                    {
                        if (towers[m][0] > towers[k][0])
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag)
                    {
                        hit += towers[k][2];
                    }
                }
            }
            int result = 0;
            while (towers[j][1] > 0)
            {
                towers[j][1] -= hit;
                result++;
            }
            printf("%d ", result);
        }
        printf("\n");
    }
}