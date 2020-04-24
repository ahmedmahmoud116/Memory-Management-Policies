#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int readfromFile();
void fifo_policy();
void optimal_policy();
void lru_policy();
void clock_policy();
char* printArr(int* buffer);


int size_buffer; //size of the buffer
char policy[10]; //name of the policy
int* buffer;    //the actual buffer
int inputs[200];  //inputs of memory pages to be replaced

int main()
{
    int check = readfromFile();
    if(check  == 0){
        printf("The file not in the folder of the program \n");
        return 0;
    }

    if(strcmp(policy,"OPTIMAL") == 0){
        optimal_policy();
    }
    else if(strcmp(policy,"FIFO") == 0){
        fifo_policy();
    }
    else if(strcmp(policy,"LRU") == 0){
        lru_policy();
    }
    else if(strcmp(policy,"CLOCK") == 0){
        clock_policy();
    }

    return 0;
}

void clock_policy(){
    int countF = 0;
    char printBuffer[8];
    char page[3];
    bool bufferch[3];
     FILE *fptr = fopen("outputCLOCK.txt","w");// open file for writing
     if (fptr == NULL){
        printf("Could not open output file\n");
        return 0;
        }

    else{
               fprintf(fptr,"Replacement Policy = %s\n", policy);
               fprintf(fptr,"-------------------------------------\n");
               fprintf(fptr,"Page   Content of Frames\n");
               fprintf(fptr,"----   -----------------\n");
      for(int i = 0, j = 0;inputs[j] != -1; j++){ //i points to the free space in the buffer or the longest element in the buffer, j points to the inputs in the inputs array

        if(inputs[j]<10){
            char pageW[2] = "0";
            sprintf(pageW, "%d", inputs[j]);
            strcpy(page, "0");
            strcat(page,pageW);
        }
        else{
            sprintf(page, "%d", inputs[j]);
        }
        //   if(j == 6)
       /*  for(int v = 0 ;v<size_buffer;v++){
            printf("Result %d: %d\n",j,buffer[v]);
        }*/

        if(i == 3){
            i = 0;
        }
        bool contains = false;
        int k;
        for(k = 0;k<size_buffer;k++){
            if(buffer[k] == inputs[j]){
            contains = true;
            break;
            }
        }
        if(contains){
            strcpy(printBuffer,printArr(buffer));
            fprintf(fptr,"%s     %s\n",page,printBuffer);
            bufferch[k] = true;
            continue;
        }
        if(buffer[i] == 0){ //if there is an empty space in the buffer and its not in the buffer
            buffer[i] = inputs[j];
            bufferch[i] = true;
            strcpy(printBuffer,printArr(buffer));
            fprintf(fptr,"%s     %s\n",page,printBuffer);
            i++;
            continue;
        }

        int min = (int)( sizeof(inputs) / sizeof(inputs[0]))  , index_be_replaced = i;
        for(int z = i;z<size_buffer;z++){
            if(bufferch[z]){
                bufferch[z] = false;
            }
            else{
                buffer[z] = inputs[j];
                bufferch[z] =true;
                strcpy(printBuffer,printArr(buffer));
                fprintf(fptr,"%s F   %s\n",page,printBuffer);
                countF++;
                i++;
                break;
            }
            if(z == 2){ //means it find all with * so it loop again to substitute
                z = -1;
            }
        }

      }
    }
        fprintf(fptr,"-------------------------------------\n");
        fprintf(fptr,"Number of page faults = %d",countF);
}

void lru_policy(){
    int countF = 0;
    char printBuffer[8];
    char page[3];
     FILE *fptr = fopen("outputLRU.txt","w");// open file for writing
     if (fptr == NULL){
        printf("Could not open output file\n");
        return 0;
        }

        else{
               fprintf(fptr,"Replacement Policy = %s\n", policy);
               fprintf(fptr,"-------------------------------------\n");
               fprintf(fptr,"Page   Content of Frames\n");
               fprintf(fptr,"----   -----------------\n");

    for(int i = 0, j = 0;inputs[j] != -1; j++){ //i points to the free space in the buffer or the longest element in the buffer, j points to the inputs in the inputs array

        if(inputs[j]<10){
            char pageW[2] = "0";
            sprintf(pageW, "%d", inputs[j]);
            strcpy(page, "0");
            strcat(page,pageW);
        }
        else{
            sprintf(page, "%d", inputs[j]);
        }
        //   if(j == 6)
       /*  for(int v = 0 ;v<size_buffer;v++){
            printf("Result %d: %d\n",j,buffer[v]);
        }*/

        if(i == 3){
            i = 0;
        }
        bool contains = false;

        for(int k = 0;k<size_buffer;k++){
            if(buffer[k] == inputs[j]){
            contains = true;
            break;
            }
        }
        if(contains){
            strcpy(printBuffer,printArr(buffer));
            fprintf(fptr,"%s     %s\n",page,printBuffer);
            continue;
        }
        if(buffer[i] == 0){ //if there is an empty space in the buffer and its not in the buffer
            buffer[i] = inputs[j];
            strcpy(printBuffer,printArr(buffer));
            fprintf(fptr,"%s     %s\n",page,printBuffer);
            i++;
            continue;
        }
        int min = (int)( sizeof(inputs) / sizeof(inputs[0]))  , index_be_replaced = i;
        for(int z = 0;z<size_buffer;z++){
            int x;
            for(x = j-1;x > 0;x--){
                if(buffer[z]  == inputs[x])
                {
                    if(x < min)
                    {min = x;
                     index_be_replaced = z;
                    }
                    break;
                }
            }
             if(x < min){
                    min = x;
                    index_be_replaced = z;
                }
        }
        if(index_be_replaced == i){
            i++;
        }
        //printf("Buffer: %d %d\n",buffer[index_be_replaced], index_be_replaced);
        buffer[index_be_replaced] = inputs[j];
        strcpy(printBuffer,printArr(buffer));
        fprintf(fptr,"%s F   %s\n",page,printBuffer);
        countF++;
        //printf("Buffer: %d %d\n",buffer[index_be_replaced], index_be_replaced);

    }
    }
        fprintf(fptr,"-------------------------------------\n");
        fprintf(fptr,"Number of page faults = %d",countF);
}

void optimal_policy(){
    int countF = 0;
    char printBuffer[8];
    char page[3];
     FILE *fptr = fopen("outputOPTIMAL.txt","w");// open file for writing
     if (fptr == NULL){
        printf("Could not open output file\n");
        return 0;
        }

        else{
               fprintf(fptr,"Replacement Policy = %s\n", policy);
               fprintf(fptr,"-------------------------------------\n");
               fprintf(fptr,"Page   Content of Frames\n");
               fprintf(fptr,"----   -----------------\n");

    for(int i = 0, j = 0;inputs[j] != -1; j++){ //i points to the free space in the buffer or the longest element in the buffer, j points to the inputs in the inputs array

        if(inputs[j]<10){
            char pageW[2] = "0";
            sprintf(pageW, "%d", inputs[j]);
            strcpy(page, "0");
            strcat(page,pageW);
         //   printf("%s \n",page);
        }
        else{
            sprintf(page, "%d", inputs[j]);
        }
        //   if(j == 6)
       /*  for(int v = 0 ;v<size_buffer;v++){
            printf("Result %d: %d\n",j,buffer[v]);
        }*/

        if(i == 3){
            i = 0;
        }
        bool contains = false;

        for(int k = 0;k<size_buffer;k++){
            if(buffer[k] == inputs[j]){
            contains = true;
            break;
            }
        }
        if(contains){
            strcpy(printBuffer,printArr(buffer));
            fprintf(fptr,"%s     %s\n",page,printBuffer);
            continue;
        }
        if(buffer[i] == 0){ //if there is an empty space in the buffer and its not in the buffer
            buffer[i] = inputs[j];
            strcpy(printBuffer,printArr(buffer));
            fprintf(fptr,"%s     %s\n",page,printBuffer);
            i++;
            continue;
        }
        int max = 0 , index_be_replaced = i;
        for(int z = 0;z<size_buffer;z++){
            int x;
            for(x = j + 1;inputs[x] != -1;x++){
                if(buffer[z]  == inputs[x])
                {
         //       printf("%d \t %d \t %d \t %d\n",inputs[x], x ,z,max);
                    if(x > max)
                    {max = x;
                     index_be_replaced = z;
                  //  printf("AAAA: %d \t%d\n",max,index_be_replaced);
                    }
                    break;


                }
            }
             if(x > max){
                    max = x;
                    index_be_replaced = z;
                }
        }
        if(index_be_replaced == i){
            i++;
        }
        //printf("Buffer: %d %d\n",buffer[index_be_replaced], index_be_replaced);
        buffer[index_be_replaced] = inputs[j];
        strcpy(printBuffer,printArr(buffer));
        fprintf(fptr,"%s F   %s\n",page,printBuffer);
        countF++;
        //printf("Buffer: %d %d\n",buffer[index_be_replaced], index_be_replaced);

    }
    }
        fprintf(fptr,"-------------------------------------\n");
        fprintf(fptr,"Number of page faults = %d",countF);

}


void fifo_policy(){
    int countF = 0;
    char printBuffer[8];
    char page[3];
     FILE *fptr = fopen("outputFIFO.txt","w");// open file for writing
     if (fptr == NULL){
        printf("Could not open output file\n");
        return 0;
        }
    else{
               fprintf(fptr,"Replacement Policy = %s\n", policy);
               fprintf(fptr,"-------------------------------------\n");
               fprintf(fptr,"Page   Content of Frames\n");
               fprintf(fptr,"----   -----------------\n");
        for(int i = 0, j = 0;inputs[j] != -1; j++){
            if(inputs[j]<10){
            char pageW[2] = "0";
            sprintf(pageW, "%d", inputs[j]);
            strcpy(page, "0");
            strcat(page,pageW);
         //   printf("%s \n",page);
        }
        else{
            sprintf(page, "%d", inputs[j]);
        }

        if(i == 3){
            i = 0;
        }

        bool contains = false;

        for(int k = 0;k<size_buffer;k++){
            if(buffer[k] == inputs[j]){
            contains = true;
            break;
            }
        }
        if(contains){
            strcpy(printBuffer,printArr(buffer));
            fprintf(fptr,"%s     %s\n",page,printBuffer);
            continue;
        }
        if(buffer[i] == 0){ //if there is an empty space in the buffer and its not in the buffer
            buffer[i] = inputs[j];
            strcpy(printBuffer,printArr(buffer));
            fprintf(fptr,"%s     %s\n",page,printBuffer);
            i++;
            continue;
        }
        buffer[i] = inputs[j];
        strcpy(printBuffer,printArr(buffer));
        fprintf(fptr,"%s F   %s\n",page,printBuffer);
        countF++;
        i++;

        }
    }
        fprintf(fptr,"-------------------------------------\n");
        fprintf(fptr,"Number of page faults = %d",countF);
}


char* printArr(int buffer[]){
    char page[2];
    char *result = (char *) malloc(sizeof(char) * 8);
    strcpy(result, "");
    for(int i = 0;i<size_buffer;i++){
        if(buffer[i] == 0)
        break;
        char space[10] = {' '};
            if(buffer[i]<10){
            char pageW[2] = "0";
            sprintf(pageW, "%d", buffer[i]);
            strcpy(page, "0");
            strcat(page,pageW);
            if(i == 0){
                strcpy(result,page);
            }
        }
        else{
            sprintf(page, "%d", buffer[i]);
            if(i == 0){
                 strcpy(result,page);
            }
        }
        if(i != 0){
        strcat(space, page);
        strcat(result,space);
        }
    }
    return result;
}

int readfromFile(){
    FILE *fptr = fopen("inputCLOCK.txt","r");// open file for reading
     if (fptr == NULL){
        printf("Could not open input file\n");
        return 0;
    }
    else{
    fscanf(fptr,"%d",&size_buffer);
    fscanf(fptr,"%s",&policy);
    buffer = (int *)malloc(size_buffer * sizeof(int));
    int num;
    fscanf(fptr,"%d",&num);//take the char in the file
    int index = 0;  //index to put in the array of inputs
    while(num != -1){ //loop to put all inputs in the file in the array
        inputs[index]  = num;
        index++;
        fscanf(fptr,"%d",&num);
    }
    inputs[index] = -1;
    }
    fclose(fptr);
    return 1;
}
