#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool validValue(char*);
bool validQuantity(char*);
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
            result = validQuantity(input);
            if(result == 0){
                printf("Invlid value.\n\n");
            }else{
                x[i] = atoi(input);
                if(x[i] > 100){
                    printf("Maximum number of quantity is 100.\n\n");
                }
            }
        }while(result != 1 || x[i] > 100);

        do{
            printf("Enter the delivery distance (km): ", i + 1);
            scanf("\n%[^\n]", input);
            result = validValue(input);
            if(result == 0){
                printf("Invlid value.\n\n");
            }else{
                y[i] = atof(input);
                if(y[i] > 6000 || y[i] == 0){
                    printf("Invalid value.\n\n");
                }
            }
        }while(result != 1 || y[i] > 6000 || y[i] <= 0.0);

        do{
            printf("Enter the keeping days: ", i + 1);
            scanf("\n%[^\n]", input);
            result = validValue(input);
            if(result == 0){
                printf("Invalid value.\n\n");
            }else{
                z[i] = atof(input);
                if(z[i] > 31){
                    printf("Maximum keeping days is 31.\n\n");
                }
            }
        }while(result != 1 || z[i] > 31);

        do{
            printf("Enter the total cost: ", i + 1);
            scanf("\n%[^\n]", input);
            result = validValue(input);
            if(result == 0){
                printf("Invalid value.\n\n");
            }else{
                w[i] = atof(input);
                if(w[i] > 1000000 || w[i] < 5){
                    printf("Invalid value\n\n");
                }
            }
        }while(result != 1 || w[i] > 1000000 || w[i] < 5);
    }
    printf("\nIn matrix form: \n");
    matrix(x, y, z, w);
    det = findDeterminant(x, y, z);
    dx = findDxyz(w, y ,z);
    dy = findDxyz(x, w, z);
    dz = findDxyz(x ,y, w);

    printf("\nDeterminant = %f\n", det);
    printf("Dx = %f\n", dx);
    printf("Dy = %f\n", dy);
    printf("Dz = %f\n", dz);
    if(det == 0){
        if(dx == 0 && dy == 0 && dz == 0){
            printf("\nThe system is dependent.\n");
        }else{
            printf("\nThe system is inconsistent.\n"); 
        }
    }else{
        ansX = findValue(&dx, &det);
        ansY = findValue(&dy, &det);
        ansZ = findValue(&dz, &det);
        printf("\nManufacturing price / quantity, x = %f / %f = RM %.2f\n", dx, det, ansX);
        printf("\nDelivery fee / km, y = %f / %f = RM %.2f\n", dy, det, ansY);
        printf("\nKeeping fee / day, z = %f / %f = RM %.2f\n", dz, det, ansZ);
        if(ansX < 0 || ansY < 0 || ansZ < 0){
            printf("\nx, y and z shouldn't less than 0, kindly check your inputs.\n");
        }
    }
}

bool validValue(char* value){
    
    int numberOfPeriod = 0;
    if(value[0] == 48){
        if(strlen(value) != 1){
            if(value[1] != 46){
                return 0;
            }
        }else{
            return 1;
        }
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

bool validQuantity(char* quantity){

    if(quantity[0] == 48){
        return 0;
    }
    for(int i = 0; i < strlen(quantity); i++){
        if(quantity[i] < 48 || quantity[i] > 57){
            return 0;
        }else if(i == strlen(quantity) - 1){
            return 1;
        }
    }
}

void matrix(float* x, float* y, float* z, float* w){

    printf("( %6.2f %10.2f %8.2f ) ( x ) = ( %-10.2f )\n", x[0], y[0], z[0], w[0]);
    printf("( %6.2f %10.2f %8.2f ) ( y ) = ( %-10.2f )\n", x[1], y[1], z[1], w[1]);
    printf("( %6.2f %10.2f %8.2f ) ( z ) = ( %-10.2f )\n", x[2], y[2], z[2], w[2]);
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