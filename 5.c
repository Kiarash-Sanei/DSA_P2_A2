#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    long long *indices;
    long long count;
} Stack;

int main() {
    long long testCases;
    scanf("%lld", &testCases);

    while (testCases--) {
        long long numTowers;
        scanf("%lld", &numTowers);

        long long towerInfo[numTowers][3];
        for (long long i = 0; i < numTowers; i++) {
            scanf("%lld %lld %lld", &towerInfo[i][0], &towerInfo[i][1], &towerInfo[i][2]);
        }

        long long *leftHits = calloc(numTowers, sizeof(long long));
        long long *rightHits = calloc(numTowers, sizeof(long long));

        Stack stack;
        stack.indices = calloc(numTowers, sizeof(long long));
        stack.count = 0;
        long long cumulativeHits = 0;

        for (long long i = 0; i < numTowers; i++) {
            leftHits[i] = cumulativeHits;
            while (stack.count > 0 && towerInfo[stack.indices[stack.count - 1]][0] < towerInfo[i][0]) {
                cumulativeHits -= towerInfo[stack.indices[--stack.count]][2];
            }
            stack.indices[stack.count++] = i;
            cumulativeHits += towerInfo[i][2];
        }

        stack.count = 0;
        cumulativeHits = 0;

        for (long long i = numTowers - 1; i >= 0; i--) {
            rightHits[i] = cumulativeHits;
            while (stack.count > 0 && towerInfo[stack.indices[stack.count - 1]][0] < towerInfo[i][0]) {
                cumulativeHits -= towerInfo[stack.indices[--stack.count]][2];
            }
            stack.indices[stack.count++] = i;
            cumulativeHits += towerInfo[i][2];
        }

        for (long long i = 0; i < numTowers; i++) {
            long long totalHits = leftHits[i] + rightHits[i];
            long long turnsNeeded = (towerInfo[i][1] + totalHits - 1) / totalHits;
            printf("%lld ", turnsNeeded);
        }
        printf("\n");

        free(leftHits);
        free(rightHits);
        free(stack.indices);
    }

    return 0;
}