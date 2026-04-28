#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *token;
char input[10000];

int i, j, k, l, width, height, grey_value, width_counter = 0, counter, GV = 0, GH = 0, GPD = 0, GND = 0;
int p1, p2, p3, p4, S_counter = 0;

int pairs[10000][2];
int pixels[10000][10000];
int gradient[10000][10000];

int convert_to_array();
int grade_checker();
int convert_to_black_and_white();

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
    grade_checker();
    convert_to_black_and_white();
    for (i = 0; i < height - 1; i++){
        for (j = 0; j < width - 1; j++){
            printf("%c", gradient[i][j]);
        }
        printf("\n");
    }
}

/*converts the pairs array to the pixels array based on the grey value
because when asigning to the pairs array the values of i (k in seen in this function) start from 3 
k has been initialized to 3 to compensate
a counter is used to keep track of how many of each pixel of each pair has been assigned and when they are equal
the code moves on to the next pair*/
int convert_to_array(){
    /*if the grey value is 1 this fills the pixels array with '0' characters*/
    if (grey_value == 1){
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                pixels[i][j] = '0';
            }
        }
    }

    /*if the grey value is 2 this fills the pixels array with '0' and '1' characters based on the pairs array*/
    if (grey_value == 2){
        k = 3;
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){ 
                counter++;
                pixels[i][j] = ((pairs[k][0]) == 0 ? '0' : '1');
                if (counter == pairs[k][1]){
                    counter = 0;
                    k++;
                }       
            }
        }
    }

    /*if the grey value is 3 this fills the pixels array with '0' and '1' and '2' characters based on the pairs array*/
    if (grey_value == 3){
        k = 3;
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                counter++;
                pixels[i][j] = ((pairs[k][0]) == 0 ? '0' : (pairs[k][0]) == 1 ? '1' : '2');
                if (counter == pairs[k][1]){
                    counter = 0;
                    k++;
                }
            }
        }
    }

    /*if the grey value is 4 this fills the pixels array with '0' and '1' and '2' and '3' characters based on the pairs array*/
    if (grey_value == 4){
        k = 3;
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                counter++;
                pixels[i][j] = ((pairs[k][0]) == 0 ? '0' : (pairs[k][0]) == 1 ? '1' : (pairs[k][0]) == 2 ? '2' : '3');
                if (counter == pairs[k][1]){
                    counter = 0;
                    k++;
                }
            }
        }
    }
}


/*this function calculates the gradient values for each pixel and assigns them to the gradient array*/
int grade_checker(){
    for(i = 0; i < height-1; i++){
        for(j = 0; j < width-1; j++){
            p1 = pixels[i][j];
            p2 = pixels[i][j+1];
            p3 = pixels[i+1][j];
            p4 = pixels[i+1][j+1];

            /*gradient horizontal*/
            GH =abs((p1 - p2 + p3 - p4)/2);

            /*gradient vertical*/
            GV = abs((p1 + p2 - p3 - p4)/2);

            /*gradient positive diagonal*/
            GPD = abs(p1 - p4);

            /*gradient negative diagonal*/
            GND = abs(p2 - p3);

            /*assign the maximum gradient value to the gradient array for each pixel*/
            gradient[i][j] = (GH >= GV && GH >= GPD && GH >= GND) ? GH : (GV >= GH && GV >= GPD && GV >= GND) ? GV : (GPD >= GH && GPD >= GV && GPD >= GND) ? GPD : GND;
        }
    }
}

/*converts the gradient array to the correct symbol representation*/
int convert_to_black_and_white(){
    for (i = 0; i < height - 1; i++){
        for (j = 0; j < width - 1; j++){

            /*if the grey value is 1 this converts the gradient array to a grid of '#' characters*/
            if (grey_value == 1)
            gradient[i][j] = gradient[i][j] == '#';

            /*if the grey value is 2 this converts the gradient array to a grid of '#' and ' ' characters based on the gradient values*/
            else if (grey_value == 2)
            gradient[i][j] = (gradient[i][j] == 0) ? ' ' : '#';

            /*if the grey value is 3 this converts the gradient array to a grid of '#' and '.' and ' ' characters based on the gradient values*/
            else if (grey_value == 3)
            gradient[i][j] = (gradient[i][j] == 0) ? ' ' : (gradient[i][j] == 1) ? '.' : '#';

            /*if the grey value is 4 this converts the gradient array to a grid of '#' and ':' and '.' and ' ' characters based on the gradient values*/
            else if (grey_value == 4)
            gradient[i][j] = (gradient[i][j] == 0) ? ' ' : (gradient[i][j] == 1) ? '.' : (gradient[i][j] == 2) ? ':' : '#';
        }
    }
}