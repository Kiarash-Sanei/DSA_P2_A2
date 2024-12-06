#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    int *informations;
    int size;
} stack;

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

        int *left = calloc(peopleCount, sizeof(int));
        int *right = calloc(peopleCount, sizeof(int));

        stack s;
        s.informations = calloc(peopleCount, sizeof(int));
        s.size = 0;
        int hit = 0;

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
        s.informations = calloc(peopleCount, sizeof(int));
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
            int total_attack = left[j] + right[j];
            int turns = (towers[j][1] + total_attack - 1) / total_attack;
            printf("%d ", turns);
        }
        printf("\n");

        free(left);
        free(right);
        free(s.informations);
    }

    return 0;
}