#include <stdio.h>

unsigned int binary_didigt_sum(unsigned int value)
{
        unsigned int sum = 0;
        while (value > 0) {
                printf("sum before = %d\n", sum);
                printf("value before = %d\n", value);
                sum += value & 1;
                value >>=1;
                printf("sum after = %d\n", sum);
                printf("value after = %d\n", value);
                printf("========================\n");
        }
        return sum;
}

int main(void)
{
        int res = binary_didigt_sum(9);
        printf("%d\n", res);
        return 0;
}
