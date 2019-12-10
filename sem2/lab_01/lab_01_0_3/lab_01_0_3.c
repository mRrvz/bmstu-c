#include <stdio.h>
#define CONSTANT_FROM_FORMULA 240
#define COEFF_FROM_CM_TO_M 100
#define OK 0

int main()
{
    setbuf(stdout, NULL);

    float height, radius, weight;
    float normal_weight, mass_index;
    
    puts("Enter height (cm), chest circumference (cm) and weight (cm):");
    scanf("%f %f %f", &height, &radius, &weight);

    normal_weight = height * radius / CONSTANT_FROM_FORMULA;
    height /= COEFF_FROM_CM_TO_M;
    mass_index = weight / (height * height);

    printf("Normal weight is a man with given parameters equal to: %.5f kg.\n\
The body mass index with such a weight is equal to: %.5f", normal_weight, mass_index);
    
    return OK;
}
