#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*prototypes*/
int readFile(char** words, char *fileName);
void encode(char** words, char *fileName, int nwords);
void decode(char * filename);
void Exit();


int main(void)
{
     char **keyWords;
     char *fileName;  /*name of file to be read. fileName will be entered by user*/

     int numWords = 0;
     int i=0;
     int c=0; /*choice for menu*/
     
     int seed = 0111; /*last 4 digits of my GNumber as seed*/
     srand(seed);
     
     /*Dynamically create the 2D array(array of strings)*/
     /*no more than 15 characters in a word*/
     keyWords = malloc(5000 * sizeof(char*));
     
     for (i = 0; i<5000; i++)
     {
          keyWords[i] = (char *)malloc(15);
     }

     fileName = (char*)malloc(15); 

    

     while (1) 
     { 
          /*Menu of choices*/
          printf("Hello. choose a task.\n");
          printf("1) Enter name of cipher text file\n");
          printf("2) Create a cipher key using a text file\n");
          printf("3) Decode an existing cipher\n");
          printf("4) Exit the program.\n");
          printf("Enter your choice: ");

          scanf("%d", &c); /*scan choice from user*/
          
          switch(c) /*switch for choice menu*/
          {
               case 1:
                    {
                         numWords = readFile(keyWords, fileName);
                         break;
                    }
               case 2: 
                    {
                         encode(keyWords, fileName, numWords);
                         break;
                    }
               case 3:
                    {
                         decode(fileName);
                         break;
                    }
               case 4:
               default:
                    {
                         exit(1);
                         break;
                    }
          }/*end switch*/

          printf("\n\n");

     }/*end while loop*/
     return 0;
}


/*read text(words) into 2D array(array of char strings)*/
int readFile(char** words, char *fileName)
{
     char cipher[1000];
     int word = 0;
     FILE *frp; /*declare FILE pointer*/

     printf("Enter the name of a cipher text file:");
     /*read name of cipher file from user*/
     scanf("%s", fileName);  

     frp = fopen(fileName, "r"); /*after getting name of file, read it*/
     if (frp == NULL) /*check if file opened successfully*/
     {
          puts("Error: Couldn't open file");
          exit(1);
     }

     
     while (fgets(cipher, sizeof(cipher), frp) != NULL) /*read content of text file using fgets*/
     { 
          int i=0;
          int j=0;

          while (cipher[i] != '\0') /*exits while loop only when null character encountered (i.e., EOF)*/
          {
              if (cipher[i] != ' ')
              {
                   if (cipher[i] >= 65 && cipher[i] <= 90) /*If uppercase, convert to lowercase*/
                   {
                        words[word][j] = cipher[i] +32;
                   }

                   else
                   {
                        words[word][j] = cipher[i];
                   }

                   j++;
              }

              else
              {
                   words[word][j] = '\n';
                   j = 0;
                   word++;
              }
	              i++;
          }
     
          words[word][j] = '\n';
          word++;
     }
     fclose(frp);

     return word;
}

/*Convert plain text from user to cipher*/
void encode(char** words, char *fileName, int nwords)
{
     FILE *fwp;
     
     char cipher[1500];
     char result[100];
     char decodedFilename[30];
     
     /*declaration and instantiation of variables to be used in the following while loop*/
     int i=0;
     int j=0;
     int k=0;
     int l=0; 

     int found =0; /*0 or 1 whether if there is a letter found in the cipher text*/ 

     strcpy(result, " ");

     if (strcmp(fileName, "") == 0)
     {
          nwords = readFile(words, fileName);
     }

     printf("Enter a cipher text: ");
     scanf("%s", cipher);

     printf("What would you like to name your test file containing decoded file?:");
     scanf("%s", decodedFilename);

     while (cipher[i] != '\0')
     {        
          if (cipher[i] >= 65 && cipher[i] <= 90) /*Convert to lowercase if there are any uppercase*/
               {
                    cipher[i] = cipher[i] + 32;
               }

          l = 0;
          found = 0;
          while (l<nwords)
          {
              j=0; 

              while (words[l][j] != '\0' && !feof(stdin))
              {
                   if (cipher[i] == words[l][j])
                   {
                        printf("%c -> %d,%d \n", cipher[i], l, j);
                        found = 1;
                        fwp = fopen(decodedFilename,"w+");
                        fprintf(fwp,"%c -> %d,%d \n", cipher[i], l, j);
                        fclose(fwp);
                        break;
                   }
               j++;
              }
              if (found == 1)
              {
                   break;
              }
              l++;
          }
          i++;
     }
     result[k] = '\n';
}

void decode(char * filename) /*decode encoded text*/
{
     char buff[255]; /*buffer for printing*/
     FILE *fdp;

     char decodedFile[30]; 

     printf("Enter name of decoded file name(the one you put in choice 2)" );
     scanf("%s", decodedFile);

     printf("Enter name of file of cipher text:" );
     scanf("%s", filename);

     

     fdp = fopen(decodedFile, "r+");
     
     if(fdp !=NULL)
          {
               fgets(buff, 255, fdp);
               printf("%s\n", buff);
          }
     fclose(fdp);
}

void Exit() /*EXIT PROGRAM*/
{
     exit(1);
}

