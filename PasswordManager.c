#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char * buffer = 0;
long length;
#define MAX_LINE 1024
char wrd[256];
int thepassword=0;

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
    f1=fopen("C:\\Users\\super\\Desktop\\C_Projects\\savedServices.txt","a");
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

void deletePasswords(){
    fclose(fopen("savedServices.txt", "w"));
}



int retrievePassword(){
    FILE *fp;
    char word[15],str[200];
    char ch;
    int i=0,j=0,pos=0,cmp,flag=0,thepassword=0;
    printf("Enter a word to search\n");
    scanf("%s",word);
    fp=fopen("C:\\Users\\super\\Desktop\\C_Projects\\savedServices.txt","r");
    while((ch=fgetc(fp))!=EOF)
    {

        if((ch==' ')||(ch=='\n'))
        {
           pos++;
           cmp=strcmp(str,word);
           if(cmp==0)
           {
               printf("%s is found at the position %d from the beginning\n",word,pos);
               thepassword=pos+1;
               printf("the password initialy is:%d\n",thepassword);
               flag=1;
           }
           for(i=j;i>=0;i--)
           {
               str[i]='\0';
           }
           j=0;
           continue;
        }
        str[j]=ch;
        j++;
    }
    pos++;
    cmp=strcmp(str,word);
    if(cmp==0)
    {
        printf("%s is found at %d position from the beginning\n",word,pos);
    }
    else if(flag==0)
    {
        printf("%s is not found in this file\n",word);
    }

   //------------------------------------------------------------------------- 

    //pos einai h grammi pou thelw ara auto to xreiazomai
    
    printf("the password before the return is:%d\n",thepassword);


        // file pointer will be used to open/read the file
        rewind(fp);

  // used to store the filename and each line from the file
  char buffer[200];

  // stores the line number of the line the user wants to read from the file
  int read_line = thepassword;
  printf("the password is:%d\n",thepassword);
  printf("read line is:%d\n",read_line);


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
      printf("File %d lines.\n", current_line-1);
      printf("Couldn't find line %d.\n", read_line);
    }
    // if we've found the line the user is looking for, print it out
    else if (current_line == read_line)
    {
      keep_reading = false;
      printf("Line:\n%s", buffer);
    }

    // continue to keep track of the current line we are reading
    current_line++;

  } while (keep_reading);

  // close our access to the file
  fclose(fp);

  return 0;
    //return thepassword;
}



int main(){
    struct loginCredentials log;
    //enterLoginCredentials(log);
    //login(log);
    //inputNewPassword();
    //inputNewPassword();
    //deletePasswords();
    retrievePassword();
    return 0;

}