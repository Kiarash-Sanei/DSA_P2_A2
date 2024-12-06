#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    long long *informations;
    long long size;
} stack;

int main()
{
    long long n;
    scanf("%lld", &n);
    for (int i = 0; i < n; i++)
    {
        long long peopleCount;
        scanf("%lld", &peopleCount);

        long long towers[peopleCount][3];
        for (int j = 0; j < peopleCount; j++)
        {
            scanf("%lld %lld %lld", towers[j], towers[j] + 1, towers[j] + 2);
        }

        long long *left = calloc(peopleCount, sizeof(long long));
        long long *right = calloc(peopleCount, sizeof(long long));

        stack s;
        s.informations = calloc(peopleCount, sizeof(long long));
        s.size = 0;
        long long hit = 0;

        for (int j = 0; j < peopleCount; j++)
        {
            left[j] = hit;
            while (s.size > 0 && towers[s.informations[s.size - 1]][0] < towers[j][0])
            {
                s.size--;
                hit -= towers[s.informations[s.size]][2];
            }
            s.informations[s.size] = j;
            s.size++;
            hit += towers[j][2];
        }

        free(s.informations);
        s.informations = calloc(peopleCount, sizeof(long long));
        s.size = 0;
        hit = 0;

        for (int j = peopleCount - 1; j >= 0; j--)
        {
            right[j] = hit;
            while (s.size > 0 && towers[s.informations[s.size - 1]][0] < towers[j][0])
            {
                s.size--;
                hit -= towers[s.informations[s.size]][2];
            }
            s.informations[s.size] = j;
            s.size++;
            hit += towers[j][2];
        }

        for (int j = 0; j < peopleCount; j++)
        {
            long long totalHit = left[j] + right[j];
            long long turns = (towers[j][1] + totalHit - 1) / totalHit;
            printf("%lld ", turns);
        }
        printf("\n");

        free(left);
        free(right);
        free(s.informations);
    }

    return 0;
}