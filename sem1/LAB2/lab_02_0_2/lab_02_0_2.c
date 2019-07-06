#include <stdio.h>
#define OK 0
#define ERROR_INPUT 1
#define TRIANGLE_NOT_EXIST 2
#define CORRECT_COUNT_OF_VARIABLES 6
#define OBTUSE 2
#define ACUTE 0
#define STRAIGHT 1

int triangle_type(float product_of_vectors)
{
    if (0 == product_of_vectors)
    {
        return STRAIGHT;
    }
    else if (product_of_vectors < 0)
    {
        return ACUTE;
    }
    else
    {
        return OBTUSE;
    }
}

float vec_calc(float vec_coord_first, float vec_coord_second)
{   
    float vector = vec_coord_second - vec_coord_first;

    return vector;
}

float vec_scalar_product(float x_vec_first, float x_vec_second, float y_vec_first, float y_vec_second)
{
    float scalar_product = x_vec_first * x_vec_second + y_vec_first * y_vec_second;

    return scalar_product;
}

float calc_vec_product(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float scalar_product_ab_bc = vec_scalar_product(vec_calc(x2, x1), 
        vec_calc(x3, x2), vec_calc(y2, y1), vec_calc(y3, y2));
    float scalar_product_ab_ca = vec_scalar_product(vec_calc(x2, x1), 
        vec_calc(x1, x3), vec_calc(y2, y1), vec_calc(y1, y3));
    float scalar_product_bc_ca = vec_scalar_product(vec_calc(x3, x2), 
        vec_calc(x1, x3), vec_calc(x3, x2), vec_calc(y1, y3));
    float product_of_vectors = scalar_product_ab_bc * scalar_product_ab_ca * scalar_product_bc_ca;
    
    return product_of_vectors;
}

int existence_check(float x1, float x2, float x3, float y1, float y2, float y3)
{
    if ((x3 - x1) * (y3 - y2) == (x3 - x2) * (y3 - y1))
    {
        return TRIANGLE_NOT_EXIST;
    }
    else
    {
        return OK;
    }
}


int main()
{
    setbuf(stdout, NULL);

    float x1 = 0, y1 = 0;
    float x2 = 0, y2 = 0;
    float x3 = 0, y3 = 0;

    puts("Enter vertex coordinates: ");
    int check_count = scanf("%f %f %f %f %f %f", &x1, &y1, &x2, &y2, &x3, &y3);        

    if (check_count < CORRECT_COUNT_OF_VARIABLES)
    {
        return ERROR_INPUT;
    }

    int triangle_check = existence_check(x1, x2, x3, y1, y2, y3);

    if (triangle_check != OK)
    {
        return triangle_check;
    }
    
    float product_of_vectors = calc_vec_product(x1, y1, x2, y2, x3, y3);

    printf("Triangle type: %d", triangle_type(product_of_vectors));
 
    return OK;
}

