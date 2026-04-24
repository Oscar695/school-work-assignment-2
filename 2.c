#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *token;
char input[10000];

int pairs[10000][2];
int i, j, k, l, width, height, grey_value, width_counter = 0, counter, GV = 0, GH = 0, GPD = 0, GND = 0;
int p1, p2, p3, p4, S_counter = 0;


int pixels[10000][10000];
int gradient[10000][10000];
int convert_to_array();
int grade_checker();
int convert_to_black_and_white();

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
    grade_checker();
    convert_to_black_and_white();
    for (i = 0; i < height-1; i++){
        for (j = 0; j < width-1; j++){
            printf("%c", gradient[i][j]);
        }
        printf("\n");
    }
}


int convert_to_array(){

    if (grey_value == 1){
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                pixels[i][j] = '0';
            }
        }
    }

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

            gradient[i][j] = (GH >= GV && GH >= GPD && GH >= GND) ? GH : (GV >= GH && GV >= GPD && GV >= GND) ? GV : (GPD >= GH && GPD >= GV && GPD >= GND) ? GPD : GND;
        }
    }
}

int convert_to_black_and_white(){
    for (i = 0; i < height - 1; i++){
        for (j = 0; j < width - 1; j++){
            if (grey_value == 1)
            gradient[i][j] = gradient[i][j] == '#';

            else if (grey_value == 2)
            gradient[i][j] = (gradient[i][j] == 0) ? ' ' : '#';

            else if (grey_value == 3)
            gradient[i][j] = (gradient[i][j] == 0) ? ' ' : (gradient[i][j] == 1) ? '.' : '#';

            else if (grey_value == 4)
            gradient[i][j] = (gradient[i][j] == 0) ? ' ' : (gradient[i][j] == 1) ? '.' : (gradient[i][j] == 2) ? ':' : '#';
        }
    }
}