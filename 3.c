#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *token;
char input[10000];

int pairs[10000][2];
int i, j, k, l, width, height, grey_value, width_counter = 0, counter, GV = 0, GH = 0, GPD = 0, GND = 0;
int p1, p2, p3, p4, S_counter = 0, new_width, new_height;

float temp_float;

int pixels[10000][10000];
int larger_pixels[10000][10000];
int smoothed[10000][10000];

int convert_to_array();
int convert_to_black_and_white();
int size_up_array();
int smooth_array_1();
int smooth_array_2();

/*takes the input and processes it then runs the functions and prints the result*/
int main(){

    /*gets the input values*/
    fgets(input, 10000, stdin);

    /*read the width, height, and grey value and store them in variables*/
    token = strtok(input, " ");
    width = atoi(token);
    token = strtok(NULL, " ");
    height = atoi(token);
    token = strtok(NULL, " ");
    grey_value = atoi(token);

    /*read the pairs of values (grey values and number of occurrences) and store them in the pairs array*/
    for(i = 3; i < 10000; i++){
        token = strtok(NULL, " ");
        pairs[i][0] = atoi(token);
        token = strtok(NULL, " ");
        pairs[i][1] = atoi(token);
    }

   /*runs the functions and prints the result*/
    convert_to_array();
    size_up_array();
    smooth_array_1();
    smooth_array_2();
    smooth_array_2();
    convert_to_black_and_white();
    for (i = 0; i < new_height-1; i++){
        for (j = 0; j < new_width-1; j++){
            printf("%c", smoothed[i][j]);
        }
        printf("\n");
    }
}

/*converts the pairs array to the pixels array*/
int convert_to_array(){
    k = 3;
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){ 
            counter++;
            pixels[i][j] = ((pairs[k][0]) == 0 ? '0' : '3');
            if (counter == pairs[k][1]){
                counter = 0;
                k++;
            }       
        }
    }
}

/*increase array size and calculate in-between values*/
int size_up_array(){

    /*calculate the new width and height of the array*/
    new_width = width * 2;
    new_height = height * 2;

    /*scale up the array and calculate in-between values*/
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            /*scale up the array removes '0' to convert form char to int*/
            larger_pixels[i*2][j*2] = ((pixels[i][j] - '0'));
            /*calculate the value for the pixel to the right*/
            larger_pixels[i*2][j*2 + 1] = (((pixels[i][j] - '0') + (pixels[i][j+1] - '0')) / 2 );
            /*calculate the value for the pixel below*/
            larger_pixels[i*2 + 1][j*2]  = ((float)((pixels[i][j] - '0') + (pixels[i+1][j] - '0')) / 2 );
            /*calculate the value for the pixel diagonal to the bottom right has to be asigned to a float and then converted to an integer
            the +0.25 is so that when its converted to an integer its truncated to the correct value*/
            temp_float = ((float)((pixels[i][j] - '0') + (pixels[i][j+1] - '0') + (pixels[i+1][j] - '0') + (pixels[i+1][j+1] - '0')) / 4 + 0.25);
            larger_pixels[i*2 + 1][j*2 + 1] = temp_float;
        }
        temp_float = 0;
    }
}

/*run smoothing operation for the first time*/
int smooth_array_1(){
    for(i = 0; i <= new_height - 1; i++){
        for(j = 0; j <= new_width - 1; j++){
            /*if its the border pixel dosent run the smoothing operation*/
            if (i == 0 || j == 0 || i == new_height-2 || j == new_width-2){
                smoothed[i][j] = larger_pixels[i][j];
            }

            else{
            /*runs the smoothing equation and assigns the result*/
            smoothed[i][j] = (larger_pixels[i-1][j-1] + 2*larger_pixels[i-1][j] + larger_pixels[i-1][j+1]
                + 2*larger_pixels[i][j-1] + 4*larger_pixels[i][j]
                + 2*larger_pixels[i][j+1] + larger_pixels[i+1][j-1]
                + 2*larger_pixels[i+1][j] + larger_pixels[i+1][j+1] + 7)/16;
            }
        }
    }
}

/*run smoothing operation for the second and third time*/
int smooth_array_2(){
    for(i = 0; i <= new_height - 1; i++){
        for(j = 0; j <= new_width - 1; j++){
            /*if its the border pixel dosent run the smoothing operation*/
            if (i == 0 || j == 0 || i == new_height-2 || j == new_width-2){
                smoothed[i][j] = smoothed[i][j];
            }

            /*runs the smoothing equation and assigns the result*/
            else{
            smoothed[i][j] = (smoothed[i-1][j-1] + 2*smoothed[i-1][j] + smoothed[i-1][j+1]
                + 2*smoothed[i][j-1] + 4*smoothed[i][j]
                + 2*smoothed[i][j+1] + smoothed[i+1][j-1]
                + 2*smoothed[i+1][j] + smoothed[i+1][j+1] + 7)/16;
            }
        }   
    }
}

/*convert the smoothed array to the required symbols*/
int convert_to_black_and_white(){
    for (i = 0; i < new_height; i++){
        for (j = 0; j < new_width; j++){
            /*checks each value and converts it to the corresponding symbol*/
            smoothed[i][j] = (smoothed[i][j] == 0) ? '#' : (smoothed[i][j] == 1) ? ':' : (smoothed[i][j] == 2) ? '.' : ' ';
        }
    }
}

