#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int dial(char *rotations[], int rotations_len){
    int counter = 0;
    int temp = 50;
    int temp_direction;
    for(int i = 0; i < rotations_len; i++){
        if (rotations[i][0] == 'L') {
            temp_direction = -1;
        }else {
            temp_direction = 1;
        }
        int temp_rotation = atoi(rotations[i] + 1);
        int prev_temp = temp;
        while(temp_rotation >= 100) {
            counter++;
            temp_rotation = temp_rotation - 100;
        }
        if (temp_rotation == 0) {
            continue;
        }
        temp = (temp + (temp_rotation * temp_direction));

        if (prev_temp == 0 && temp <= 0) {
            counter--;
        }

        if (temp <= 0 || temp >= 100) {
            counter++;
        }
        if (temp < 0){
            temp = temp + 100;
        }
        if (temp > 99) {
            temp = temp - 100;
        }
    }
    return counter;
}

int main(int argc, char *argv[]){
    if(argc > 2){
        printf("result: %d", dial(argv+1, argc-1));
    }
}
