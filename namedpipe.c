#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


void main()
 {
   int pid, pid1;
   int pipe, pipe2;
   char str[100];
   int op[3],m=1;
   char * myfifo = "/tmp/myfifo";
   mkfifo(myfifo, 0666);
   char * myfifo2 = "/tmp/myfifo2";
   mkfifo(myfifo2, 0666);
   printf("Enter the string\n");
   fgets(str, 100, stdin);
   int no_char=-1, no_sent=0, no_words=1;
   pid = fork();
   if (pid != 0)
   {
      pipe = open(myfifo, O_WRONLY);
      write(pipe, str, strlen(str)+1);
      close(pipe);
      printf("Process 1 completed\n");
   } 
   else
    {
      pid1 = fork();
      if(pid1 != 0)
      {
        while(m==1)
        {
        pipe = open(myfifo, O_RDONLY);
        read(pipe,str, sizeof(str));
        for(int i=0; str[i]!='\0'; i++)
        {
          if(str[i]!='.')
          {
            if(str[i]!=' ')
            {
              no_char++;
            }
            else
            {
              no_words++;
            }
          }
          else
          {
            no_sent++;
          }
        }
        //printf("%d\t%d\t%d\n",no_char,no_words,no_sent);
        close(pipe);
        printf("%d\t%d\t%d\n",no_char,no_words,no_sent);
        pipe2 = open(myfifo2, O_WRONLY);
        write(pipe2, &no_char,sizeof(no_char));
        write(pipe2, &no_words,sizeof(no_words));
        write(pipe2, &no_sent,sizeof(no_sent));
        //printf("Written\n");
        close(pipe2);
        printf("Process 2 completed\n");
        m=0;
      }
      }
      else
      {
        pipe2 = open(myfifo2, O_RDONLY);
        read(pipe2, &no_char, sizeof(no_char));
        //printf("Opened\n");
        printf("Process 3:\n");
        printf("Total number of character in the string is %d\n",no_char);
        read(pipe2, &no_words, sizeof(no_words));
        printf("Total number of words in the string is %d\n",no_words);
        read(pipe2, &no_sent, sizeof(no_sent));
        printf("Total number of sentence in the string is %d\n",no_sent);
        //printf("Process 3\n");
        close(pipe2);
      }
   }
  }
