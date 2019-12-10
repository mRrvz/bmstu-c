#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define OK 0

int main()
{
    setbuf(stdout, NULL);
        
    float base1, base2, height;
    float edge;
    float side_triangle;
    float perimeter;

    puts("Enter the bases and height of an isosceles trapezoid: ");
    scanf("%f %f %f", &base1, &base2, &height);
    
    side_triangle = fabs(base2 - base1) * 0.5;
    edge = sqrt(side_triangle * side_triangle + height * height);
    perimeter = edge + edge + base1 + base2;
    
    printf("The perimeter of an isosceles trapezoid is %.5f", perimeter);

    return OK;
}
