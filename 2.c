#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *token;
char input[10000];

int pairs[10000][2];
int i, j, k, l, width, height, grey_value, width_counter = 0;

int pixels[10000][10000];
int printing_function();

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
    printing_function();
    for (i = 0; i < height; i++){
        for (j = 0; j < width; j++){
            printf("%c", pixels[i][j]);
        }
        printf("\n");
    }
    
}


int printing_function(){

    if (grey_value == 1){
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                pixels[i][j] = '#';
            }
        }
    }

    if (grey_value == 2){
        for(j = 3; j < 10000; j++){
            for (i = 0; i < pairs[j][1]; i++){
                if (pairs[j][0] == 0){
                    pixels[j][i] = '#';
                }
                else{
                    pixels[j][i] = ' ';
                }
            }   
        }
    }

    if (grey_value == 3){
        for(j = 3; j < 10000; j++){
            for (i = 0; i < pairs[j][1]; i++){
                if (pairs[j][0] == 0){
                    pixels[j][i] = '#';
                }
                else if (pairs[j][0] == 1){
                    pixels[j][i] = '.';
                }
                else{
                    pixels[j][i] = ' ';
                }
            }
        }
    }
    

    if (grey_value == 4){
        for(j = 3; j < 10000; j++){
            for (i = 0; i < pairs[j][1]; i++){
                if (pairs[j][0] == 0){
                    pixels[j][i] = '#';
                }
                else if (pairs[j][0] == 1){
                    pixels[j][i] = ':';
                }
                else if (pairs[j][0] == 2){
                    pixels[j][i] = '.';
                }
                else{
                    pixels[j][i] = ' ';
                }
            }
        }
    }
}
