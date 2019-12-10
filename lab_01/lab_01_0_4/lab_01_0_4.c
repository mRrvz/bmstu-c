#include <stdio.h>
#define SALE 20
#define DIFF_COST_SALE 25
#define OK 0

int main()
{
    setbuf(stdout, NULL);

    int penny, count;

    puts("Enter the number of penny: ");
    scanf("%d", &penny);

    count = (penny - SALE) / DIFF_COST_SALE;
    printf("You can buy maximum %d bottles.", count);

    return OK;
}
