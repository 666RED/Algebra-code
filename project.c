#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool validValue(char*);
void matrix(float*, float*, float*, float*);
float findDeterminant(float*, float*, float*);
float findDxyz(float*, float*, float*);
float findValue(float*, float*);

int main(){

    int result;
    float det;
    char input[5];
    float dx, dy, dz;
    float x[5], y[5], z[5], w[5];
    float ansX, ansY, ansZ;
    printf("\nx = Manufacturing price / quantity\ny = Delivery fee / km\nz = Keeping fee / day\n\n");
    for(int i = 0; i < 3; i++){
        printf("Equation %d\n", i + 1);
        do{
            printf("Enter the quantity of item: ", i + 1);
            scanf("\n%[^\n]", input);
            result = validValue(input);
            if(result == 0){
                printf("Invlid value.\n");
            }else{
                x[i] = atof(input);
            }
        }while(result != 1);

        do{
            printf("Enter the delivery distance (km): ", i + 1);
            scanf("\n%[^\n]", input);
            result = validValue(input);
            if(result == 0){
                printf("Invlid value.\n");
            }else{
                y[i] = atof(input);
            }
        }while(result != 1);

        do{
            printf("Enter the keeping days: ", i + 1);
            scanf("\n%[^\n]", input);
            result = validValue(input);
            if(result == 0){
                printf("Invalid value.\n");
            }else{
                z[i] = atof(input);
            }
        }while(result != 1);

        do{
            printf("Enter the value of total %d: ", i + 1);
            scanf("\n%[^\n]", input);
            result = validValue(input);
            if(result == 0){
                printf("Invalid value");
            }else{
                w[i] = atof(input);
            }
        }while(result != 1);
    }
    printf("\nIn matrix form: \n");
    matrix(x, y, z, w);
    det = findDeterminant(x, y, z);
    dx = findDxyz(w, y ,z);
    dy = findDxyz(x, w, z);
    dz = findDxyz(x ,y, w);
    if((int)det == 0){
        if((int)dx == 0 && (int)dy == 0 && (int)dz == 0){
            printf("\nThe system is dependent.\n");
        }else{
            printf("\nThe system is inconsistent.\n"); 
        }
    }else{
        printf("\nDeterminant  = %f\n", det);
        ansX = findValue(&dx, &det);
        ansY = findValue(&dy, &det);
        ansZ = findValue(&dz, &det);
        printf("x = %.3f\ny = %.3f\nz = %.3f\n", ansX, ansY, ansZ);
    }
}

bool validValue(char* value){
    
    int numberOfPeriod = 0;
    if(value[0] == 48 && strlen(value) != 1){
        return 0;
    }else if(value[0] == 46){
        return 0;
    }
    for(int i = 0;i < strlen(value); i++){
        if(numberOfPeriod > 1){
            return 0;
        }
        if((value[i] < 48 || value[i] > 57) && value[i] != 46){
            return 0;
        }else if(value[i] == 46){
            numberOfPeriod++;
        }else if(i == strlen(value) - 1){
            return 1;
        }
    }
}

void matrix(float* x, float* y, float* z, float* w){

    printf("( %.2f\t%.2f\t%.2f )\t( x ) = ( %.2f )\n", x[0], y[0], z[0], w[0]);
    printf("( %.2f\t%.2f\t%.2f )\t( y ) = ( %.2f )\n", x[1], y[1], z[1], w[1]);
    printf("( %.2f\t%.2f\t%.2f )\t( z ) = ( %.2f )\n", x[2], y[2], z[2], w[2]);
}

float findDeterminant(float* x, float* y, float* z){

    float result;
    result = (x[0] * ((y[1] * z[2]) - (y[2] * z[1]))) - (x[1] * ((y[0] * z[2]) - (y[2] * z[0]))) + (x[2] * ((y[0] * z[1]) - (y[1] * z[0])));
    return result;
}

float findDxyz(float* a1, float* a2, float* a3){

    float result;
    result = (a1[0] * ((a2[1] * a3[2]) - (a3[1] * a2[2]))) - (a2[0] * ((a1[1] * a3[2]) - (a3[1] * a1[2]))) + (a3[0] * ((a1[1] * a2[2]) - (a2[1] * a1[2])));
    return result;
}

float findValue(float* value, float* det){

    float result;
    result = *value / *det;
    return result;
}