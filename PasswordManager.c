#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * buffer = 0;
long length;
#define MAX_LINE 1024

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

int login(){
    char inputMasterUsername[20];
    FILE *fpointer;

    printf("Enter Username: \n");
    scanf("%s",inputMasterUsername);  //we dont need to use &masterUsername because in c string=char array that already points to the first element of the array
    printf(inputMasterUsername);

    fpointer=fopen("C:\\Users\\super\\Desktop\\C_Projects\\masterCredentials.txt","r"); 

    if (fpointer == NULL) return 1;

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
        printf("access granted\n");
    }
    else{
        printf("no\n");
        exit(0);
    }


}


int inputNewPassword(){

    char newService[20];
    char serviceUsername[MAX_LINE];
    FILE *f1;
    FILE *f2;
    char mybuffer[MAX_LINE];

    printf("welcome\n");
    printf("What service do you wish to sign in? \n");
    f1=fopen("C:\\Users\\super\\Desktop\\C_Projects\\savedServices.txt","w");
    scanf("%s",newService);
    fputs(newService,f1);
    fclose(f1);

    printf("The service is %s.\n", newService);
    f1 = fopen("C:\\Users\\super\\Desktop\\C_Projects\\savedServices.txt", "a");

    if (f1 == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

  // continually accept lines of user input until the user enters quit
    printf("Input new Username:\n");
  printf("Enter 'done' to exit.\n");
    do 
    {
        // read a line of input from the terminal (stdin) and store it into buffer
        fgets(mybuffer, MAX_LINE, stdin);
        

        // when the user enters quit, stop
        if (strcmp(mybuffer, "done\n") == 0){
        break;
        }

        // write the buffer to the file
        fputs(mybuffer, f1);
        // accept input indefinitely
    } while (1);
    fclose(f1);
    //printf("Your master Password is %s.\n", log.masterPassword);


    f2 = fopen("C:\\Users\\super\\Desktop\\C_Projects\\savedServices.txt", "r");

    while(!feof(f2))  //while not end of file
        fgets(serviceUsername, 1024, f2);  //read last line of file
    printf("The service %s is saved with username: %s\n", newService,serviceUsername);
    printf("You have saved a new Password\n");
    fclose(f2);
}

int main(){
    struct loginCredentials log;
    //enterLoginCredentials(log);
    //login(log);
    inputNewPassword();
    return 0;

}