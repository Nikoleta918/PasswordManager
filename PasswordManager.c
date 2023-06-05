#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * buffer = 0;
long length;

struct loginCredentials{
    char masterUsername[20];
    char masterPassword[20];    
};

void enterLoginCredentials(struct loginCredentials log){

    FILE *fpointer;
    fpointer=fopen("C:\\Users\\super\\Desktop\\C_Projects\\masterCredentials.txt","w");

    printf("Enter Master Username: \n");
    scanf("%s", log.masterUsername);  //we dont need to use &masterUsername because in c string=char array that already points to the first element of the array
    fputs(log.masterUsername,fpointer);

   // printf("Enter Master Password:\n ");
   // scanf("%s", log.masterPassword); 
    //fputs(log.masterPassword,fpointer);

    printf("Your master Username is %s.\n", log.masterUsername);
    //printf("Your master Password is %s.\n", log.masterPassword);

    fclose(fpointer);

}

void login(struct loginCredentials log){
    char inputMasterUsername[20];
    FILE *fpointer;

    printf("Enter Username: \n");
    scanf("%s",inputMasterUsername);  //we dont need to use &masterUsername because in c string=char array that already points to the first element of the array
    printf(inputMasterUsername);

    fpointer=fopen("C:\\Users\\super\\Desktop\\C_Projects\\masterCredentials.txt","r"); 

    if (fpointer == NULL) return NULL;

    // move the file pointer to the end of the file
    fseek(fpointer, 0, SEEK_END); 

    // fseek(file) will return the current value of the position indicator, 
    // which will give us the number of characters in the file
    int length = ftell(fpointer);

    // move file pointer back to start of file so we can read each character
    fseek(fpointer, 0, SEEK_SET);

    // dynamically allocate a char array to store the file contents, we add 1 to 
    // length for the null terminator we will need to add to terminate the string
    char *string = malloc(sizeof(char) * (length+1));

    // c will store each char we read from the string
    char c;

    // i will be an index into the char array string as we read each char
    int i = 0;

    // keep reading each char from the file until we reach the end of the file
    while ( (c = fgetc(fpointer)) != EOF)
    {
        // store char into the char array string
        string[i] = c;

        // increment i so we store the next char in the next index in the char array
        i++;
    }

    // put a null terminator as the final char in the char array to properly 
    // terminate the string
    string[i] = '\0';
    
    // close the file as we are now done with it
    fclose(fpointer);

    if(strcmp(string,inputMasterUsername)==0){
        printf("access granted");
    }
    else{
        printf("no");
    }


}

int main(){
    struct loginCredentials log;
    enterLoginCredentials(log);
    login(log);
    return 0;

}