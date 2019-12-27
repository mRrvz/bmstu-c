#ifndef __ARR_OPER_H__
#define __ARR_OPER_H__

void *memory_changer(double *const *const arr, const short int new_n, short int *const code_err, double **const arr_end);

void *del_from_arr(double *const arr, double *arr_end, const double num1, short int *const n);

void add_to_arr(double *arr, double *arr_end, double *const pos, const double num2);

#endif

