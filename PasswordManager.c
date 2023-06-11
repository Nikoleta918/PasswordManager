#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//variables
char * buffer = 0;
long length;
#define MAX_LINE 1024
char wrd[256];
int thepassword=0;
char masterPassword[20];

void enterLoginCredentials(){

    FILE *fpointer;
    fpointer=fopen("C:\\Users\\super\\Desktop\\C_Projects\\masterCredentials.txt","w");

    printf("Enter Master Username: \n");
    //we dont need to use &masterUsername because in c string=char array that already points to the first element of the array
    scanf("%s", masterPassword);  
    fputs(masterPassword,fpointer);

    printf("Your master Username is %s.\n", masterPassword);

    fclose(fpointer);

}

int login(){
    char inputMasterUsername[20];
    FILE *fpointer;

    printf("Enter Username: \n");
    //we dont need to use &masterUsername because in c string=char array that already points to the first element of the array
    scanf("%s",inputMasterUsername);  

    fpointer=fopen("C:\\Users\\super\\Desktop\\C_Projects\\masterCredentials.txt","r"); 

    if (fpointer == NULL) return 1;

    // move the file pointer to the end of the file
    fseek(fpointer, 0, SEEK_END); 

    // ftell(file) will return the current value of the position indicator, 
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
        printf("access denied.Try again\n");
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

    f1=fopen("C:\\Users\\super\\Desktop\\C_Projects\\savedServices.txt","a");

    scanf("%s",newService);
    //we write the newService the user wants to login to the file savedServices
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


    f2 = fopen("C:\\Users\\super\\Desktop\\C_Projects\\savedServices.txt", "r");

    //while not end of file
    while(!feof(f2)){  
        //read last line of file
        fgets(serviceUsername, 1024, f2);  
    }

    printf("The service %s is saved with username: %s\n", newService,serviceUsername);
    printf("You have saved a new Password\n");

    fclose(f2);
}

void deletePasswords(){
    //by opening and closing the file with the intention to write,all passwords gone
    fclose(fopen("savedServices.txt", "w"));
}

int retrievePassword(){
    FILE *fp;
    //variables
    char word[15],str[200];
    char ch;
    int i=0,j=0,pos=0,cmp,flag=0,thepassword=0;
    //enter the service for which you need the password
    printf("Enter a word to search\n");
    scanf("%s",word);

    fp=fopen("C:\\Users\\super\\Desktop\\C_Projects\\savedServices.txt","r");
    //while it is not the end of file
    while((ch=fgetc(fp))!=EOF)
    {
        //if ch=null character or change of line character,then we possibly are near a word so we will need to compare
        if((ch==' ')||(ch=='\n'))
        {
           pos++;
           cmp=strcmp(str,word);
           if(cmp==0)
           {
               thepassword=pos+1;
               flag=1;
           }
           //go to the next word and delete the existing word stored in the buffer named str
           for(i=j;i>=0;i--)
           {
               str[i]='\0';
           }
           j=0;
           continue;
        }
        //store character ch inside str buffer
        str[j]=ch;
        j++;
    }
    //we use this block to compare our word with the last word of the file(because EOF does not count the last word)
    pos++;
    cmp=strcmp(str,word);
    if(cmp==1)
    {
        printf("%s is not found in this file\n",word);
    }
        // reset file pointer to start of file
        rewind(fp);

    // used to store the filename and each line from the file
    char buffer[200];

    // stores the line number of the line the user wants to read from the file
    int read_line = thepassword;


    // open the the file in read mode

    // if the file failed to open, exit with an error message and status
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // we'll keep reading the file so long as keep_reading is true, and we'll 
    // keep track of the current line of the file using current_line
    bool keep_reading = true;
    int current_line = 1;
    do 
    {
        // read the next line from the file, store it into buffer
        fgets(buffer, 200, fp);

        // if we've reached the end of the file, we didn't find the line
        if (feof(fp))
        {
        // stop reading from the file, and tell the user the number of lines in 
        // the file as well as the line number they were trying to read as the 
        // file is not large enough
        keep_reading = false;
        printf("Couldn't find line %d.\n", read_line);
        }

        // if we've found the line the user is looking for, print it out
        else if (current_line == read_line)
        {
        keep_reading = false;
        printf("The password is:\n%s", buffer);
        }

        // continue to keep track of the current line we are reading
        current_line++;

    } while (keep_reading);

  // close our access to the file
  fclose(fp);

  return 0;
}



int main(){
    int num=0;
    int flag=0;
    printf("Choose one of the following options to use PasswordManager\n");
    printf("1:enter your login credentials to secure your passwords.Always do it at the begging of your use of password manager\n");
    printf("2:login to your existing account\n");
    printf("3:input a new password to save it\n");
    printf("4:delete all your saved passwords\n");
    printf("5:retrieve any password you have saved\n");
    printf("press any other key to terminate the session\n");
    do{
    scanf("%d",&num);
    switch(num)
    {
    case 1:
        enterLoginCredentials();
        break;
    case 2:
        login();
        break;
    case 3:
        inputNewPassword();
        break;
    case 4:
        deletePasswords();
        break;
    case 5:
        retrievePassword();
        break;
    default:
        flag=1;
        break;
    }
    }while(flag=0);

    return 0;

}