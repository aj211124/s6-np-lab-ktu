#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

void child_process(int arr[], int n)
{
  int temp;
  printf("Child process : \n");
  for(int i=0;i<n-1;i++)
  {
    for(int j=0;j<n-1-i;j++)
    {
      if(arr[j]<=arr[j+1])
      {
        temp=arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
      }
    }
  }
  printf("Sorted numbers in descending order\n");
  for(int i=0;i<n;i++)
  {
    printf("%d\t",arr[i]);
  }
  printf("\n");
}

void parent_process(int arr[], int n)
{
  int temp;
  printf("Parent Process : \n");
  for(int i=0;i<n-1;i++)
  {
    for(int j=0;j<n-1-i;j++)
    {
      if(arr[j]>=arr[j+1])
      {
        temp=arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
      }
    }
  }
  printf("Sorted number in ascending order\n");
  for(int i=0;i<n;i++)
  {
    printf("%d\t",arr[i]);
  }
  printf("\n");
}

void main()
{
  int n;
  printf("Enter the total number of numbers to be sorted\n");
  scanf("%d",&n);
  int arr[n];
  printf("Enter the numbers to be sorted\n");
  for(int i=0;i<n;i++)
  {
    scanf("%d",&arr[i]);
  }
  pid_t pid=fork();
  if(pid<0)
  {
    printf("Child creation failed\n");
  }
  else if(pid==0)
  {
    child_process(arr,n);
  }
  else
  {
    parent_process(arr,n);
  }
}
