// This code is intedted to create a child prossec and pass data between Parent & Child proccess
// Created by Mohamad Chaman-Motlagh on 28/11/2019


#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int sum_of_even_digits();
  
void main() 
{ 
    // We use two pipes 
    // First pipe to send input string from parent 
    // Second pipe to send concatenated string from child 
  //char fixed_str[] = "forgeeks.org";
    int dataArr1[2];  // For sending from parent to child 
    int dataArr2[2];  // For sending from child to parent

     
  
    char input_str[100]; 
    pid_t p; 
  
    if (pipe(dataArr1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        exit(-1); 
    } 
    if (pipe(dataArr2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        exit(-1); 
    } 
  
    scanf("%s", input_str); 

    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        exit(-1); 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
        char concat_str[100]; 
  
        close(dataArr1[0]);  // Close reading end of first pipe 
  
        // Write input string and close writing end of first pipe
        write(dataArr1[1], input_str, strlen(input_str)+1); 
        close(dataArr1[1]); 
  
        // Wait for child to send a string 
        wait(NULL); 
  
        close(dataArr2[1]); // Close writing end of second pipe 
  
        // Read string from child, print it and close reading end.
        read(dataArr2[0], concat_str, 100);
        printf("%s %s\n", input_str,concat_str); 
        close(dataArr2[0]); 
    } 
  
    // child process 
    else
    { 
        close(dataArr1[1]);  // Close writing end of first pipe 
  
        // Read a string using first pipe 
        char concat_str[100]; 
        read(dataArr1[0], concat_str, 100); 
        int event_digits = sum_of_even_digits(concat_str);
        char * str;
        sprintf(str, "%d", event_digits);
        // Clear concat_str and place fixed string inside it
        concat_str[0] = '\0';
        sprintf(concat_str, "%s", "The sum of even digits in the input number: ");

        // Concatenate a fixed string with it 
        int k = strlen(concat_str); 
        int i; 
        for (i = 0; i < strlen(str); i++) 
            concat_str[k++] = str[i]; 
  
        concat_str[k] = '\0';
  
        // Close both reading ends 
        close(dataArr1[0]); 
        close(dataArr2[0]); 
  
        // Write concatenated string and close writing end 
        write(dataArr2[1], concat_str, strlen(concat_str)+1); 
        close(dataArr2[1]); 
  
        exit(0); 
    } 
} 

int sum_of_even_digits(char* input){ // Count number of even digits
    int i = 0, sum = 0;
    for(i = 0; i < strlen(input); i++){
        if(input[i] < 48 || input[i] > 57){
            printf("Bad input, exiting! \n");
            exit(1);
        }
        int tmp = (int) input[i] - 48;
        if(tmp % 2 == 0)
            sum += tmp;
    }
    return sum;
}