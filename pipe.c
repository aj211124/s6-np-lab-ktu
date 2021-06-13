#include<stdio.h>
#include<unistd.h>
#include<string.h>

void main()
 {
   int pipefds1[2], pipefds2[2];
   int p1, p2;
   int pid;
   char filename[100];
   char content[100];
   char output[100];
   p1 = pipe(pipefds1);
   
   if (p1 == -1)
   {
      printf("Unable to create pipe 1 \n");  
   }
   p2 = pipe(pipefds2);
   
   if (p2 == -1) 
   {
      printf("Unable to create pipe 2 \n");
   }
   pid = fork();
   
   if (pid != 0)
   {
      printf("Enter the filename\n");
      gets(filename);
      close(pipefds1[0]);
      close(pipefds2[1]);
      printf("In Parent: Writing to pipe 1 – %s\n", filename);
      write(pipefds1[1], filename, sizeof(filename));
      read(pipefds2[0], output, sizeof(output));
      printf("In Parent: Reading from pipe 2 – %s\n", output);
   } 
   else
    {
      printf("Enter the content to be written\n");
      gets(content);
      close(pipefds1[1]);
      close(pipefds2[0]);
      read(pipefds1[0], output, sizeof(output));
      printf("In Child: Reading from pipe 1 – %s\n", output);
      printf("In Child: Writing to pipe 2 – %s\n", content);
      write(pipefds2[1], content, sizeof(content));
   }
  }
