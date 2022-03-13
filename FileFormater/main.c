/**
 * Converts a ﬁle format to another. from "csv" to "tl5" and "tl5" to "csv"
 *  
 */
/* 
 * File:   main.c
 * Author: Luis Oliveros
 *
 * Created on July 26, 2020, 8:58 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
   //File pointers used for file conversions
   FILE *in;
   FILE *out;
   char infile[40];//input filename
   char outfile[40];//output filename
   char file[1];//2 types of files
   int i;//counter 
   int om;//file output mode 
   int im;//file input mode
   printf("Enter input file name: ");
   scanf("%s", infile);//reading input file
   printf("Enter output file name: ");
   scanf("%s", outfile);//reading output file

   i = 0;//set counter 0;
   //while infile, until it reaches a "." or ends
   while(infile[i] != '.' && infile[i] != '\0')
   {
       i++;//length of file name before the "." and file mode
   }
   if(infile[i + 1] == 'c' && infile[i + 2] == 's' && infile[i + 3] == 'v')
   {
       im = 0;//file input mode "csv"
   }
   else if(infile[i + 1] == 't' && infile[i + 2] == 'l' && infile[i + 3] == '5')
   {
       im = 1;//file input mode "tl5"
   }
   else
   {
       printf("Inconsistent File Format\n");
       return 0;
   }
 
   i = 0;//set counter to 0;
   //while outfile, until it reaches "." or ends
   while(outfile[i] != '.' && outfile[i] != '\0')
   {
       i++;//length of file name before the "." and file mode
   }
   if(outfile[i + 1] == 'c' && outfile[i + 2] == 's' && outfile[i + 3] == 'v')
   {
       om = 0;//file output mode "csv"
   }
   else if(outfile[i + 1] == 't' && outfile[i + 2] == 'l' && outfile[i + 3] 
           == '5')
   {
       om = 1;//file output mode "tl5"
   }
   else
   {
       printf("Inconsistent File Format \n");
       return 0;
   }
   in = fopen(infile, "r");//opens and reads file
   out = fopen(outfile, "w");//opens and writes to file
   if(in == NULL || out == NULL)
   {
       printf("Error");//Files cannot open
   }
   
   char str[50];
   char ch;
 
   if (im == 0)//input file "csv" to set delimiter as "," or "\n"
   {
       //reads input file into str 
       while(fscanf(in, "%[^\n,]", str) != EOF)
       {
           fscanf(in, "%c", &ch);//scanning delimiter
           if (om == 0)//same format file, output stays the same
           { 
               fprintf(out, "%s", str);//writes to output file
               if (ch == ',')//if "," in infile
               {
                   fprintf(out, ",");//then write "," in outfile
               }
               else
               {
                   fprintf(out, "\n");//write new line
               }
           }
           else if (om == 1)//file output mode "tl5"
           {
               i = 0;//counter set 0
               while(str[i] != '\0' && i < 5)
               {
                   fprintf(out, "%c", str[i]);
                   //writes to output file the first 5 characters
                   i++;
               }
               while (i != 5)//less than 5 characters 
               {  
                   i++;
                   fprintf(out, " ");//write the rest with spaces
               }
               if (ch == ',')//if "," in infile
               {
                   fprintf(out, "|");//then write "|" in outfile
               }
               else
               {
                   fprintf(out, "\n");//write new line
               }
           }        
       }
   }
   else//input file "tl5"
   {
      //reads input file into str 
       while (fscanf(in, "%[^\n|]", str) != EOF)
       {           
           fscanf(in, "%c", &ch);
           if (om == 0)//file output mode "csv"
           {
               fprintf(out, "%s", str);//writes to output file
               if (ch == '|')//if "|" infile
               {
                   fprintf(out, ",");//then write "," in outfile
               }
               else
               {
                   fprintf(out, "\n");//write new line
               }
           }
           else if (om == 1)//file output mode "tl5"
           {
               i = 0;
               while(str[i] != '\0' && i < 5)
               {
                   fprintf(out, "%c", str[i]);
                   //writes to output file the first 5 characters
                   i++;
               }
               while (i != 5)//less than 5 characters
               {
                   i++;
                   fprintf(out, " ");//write the rest with spaces
               }
               if (ch == '|')//if "|" in infile
               {
                   fprintf(out, "|");//then write "|" in outfile
               }
               else
               {
                   fprintf(out, "\n");//write new line.
               }
           }
       }
   }
   return 0;
}
