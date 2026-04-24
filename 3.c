#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *token;
char input[10000];

int pairs[10000][2];
int i, j, k, l, width, height, grey_value, width_counter = 0, counter, GV = 0, GH = 0, GPD = 0, GND = 0;
int p1, p2, p3, p4, S_counter = 0, new_width, new_height;


int pixels[10000][10000];
int larger_pixels[10000][10000];
int converted_pixels[10000][10000]; 
int convert_to_array();
int convert_to_black_and_white();
int size_up_array();


int main(){

    fgets(input, 10000, stdin);

    token = strtok(input, " ");
    width = atoi(token);
    token = strtok(NULL, " ");
    height = atoi(token);
    token = strtok(NULL, " ");
    grey_value = atoi(token);

    for(i = 3; i < 10000; i++){
        token = strtok(NULL, " ");
        pairs[i][0] = atoi(token);
        token = strtok(NULL, " ");
        pairs[i][1] = atoi(token);
    }
    /*
    printing_function();
    for (i = 0; i < height; i++){
        for (j = 0; j < width; j++){
            printf("%c", pixels[i][j]);
        }
        printf("\n");
    }
    */
    convert_to_array();
    size_up_array();
    convert_to_black_and_white();
    for (i = 0; i < new_height-1; i++){
        for (j = 0; j < new_width-1; j++){
            printf("%c", larger_pixels[i][j]);
        }
        printf("\n");
    }
}

int convert_to_array(){
    if (grey_value == 2){
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
}

/*increase array size and calculate in-between values*/
int size_up_array(){
    new_width = width * 2;
    new_height = height * 2;
    grey_value = grey_value * 2;
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            larger_pixels[i*2][j*2] = ((pixels[i][j] - '0'));
            larger_pixels[i*2][j*2 + 1] = (((pixels[i][j] - '0') + (pixels[i][j+1] - '0'))/2);
            larger_pixels[i*2 + 1][j*2] = (((pixels[i][j] - '0') + (pixels[i+1][j] - '0'))/2);
            larger_pixels[i*2 + 1][j*2 + 1] = (((pixels[i][j] - '0') + (pixels[i][j+1] - '0') + (pixels[i+1][j] - '0') + (pixels[i+1][j+1] - '0'))/4);
        }
    }
}

int convert_to_black_and_white(){

    for (i = 0; i < new_height - 1; i++){
        for (j = 0; j < new_width - 1; j++){
            larger_pixels[i][j] = (larger_pixels[i][j] == 0) ? '#' : (larger_pixels[i][j] == 1) ? ':' : (larger_pixels[i][j] == 2) ? '.' : ' ';
        }
    }
}