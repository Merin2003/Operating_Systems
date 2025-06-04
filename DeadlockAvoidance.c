BANKERS

#include<stdio.h>
#include<stdlib.h>
int main()
{
   int m,n;
   printf("Enter the number of processes:");
   scanf("%d",&n);
   printf("Enter the different types of resources:");
   scanf("%d",&m);
   int available[m],max[n][m],allocated[n][m],need[n][m],work[m],finish[n],safe[n],req[m],count,flag,proc,i,j,k;
   char ch;
   for(i=0;i<m;i++)
   {
      printf("Enter the number of resources of type%d:",i+1);
      scanf("%d",&available[i]);
      work[i]=available[i];
   }
   for(i=0;i<n;i++)
   {
      for(j=0;j<m;j++)
      {
         printf("Enter the maximum resources R%d required by P%d:",j,i);
         scanf("%d",&max[i][j]);
      }
   }
   for(i=0;i<n;i++)
   {
      for(j=0;j<m;j++)
      {
         printf("Enter the allocated resource R%d to process P%d:",j,i);
         scanf("%d",&allocated[i][j]);
      }
   }
   for(i=0;i<n;i++)
   {
      for(j=0;j<m;j++)
      {
         need[i][j]=max[i][j]-allocated[i][j];
      }
   }
   printf("Is there is a request from any process?(y/n)");
   scanf(" %c",&ch);
   if(ch=='y')
   {
      printf("Enter the process number requesting for resource:");
      scanf("%d",&proc);
      printf("Enter the request of p%d:\n",proc);
      for(i=0;i<m;i++)
      {
         printf("Enter request for resource R%d:",i);
         scanf("%d",&req[i]);
      }
      for(i=0;i<m;i++)
      {
         if(req[i]>need[proc][i])
         {
            printf("Cannot alloacte resource!");
            return 0;
         }
         else
         {
            if(req[i]<=available[i])
            {
               available[i]-=req[i];
               allocated[proc][i]+=req[i];
               need[proc][i]-=req[i];
               work[i]=available[i];
            }
            else
            {
               printf("Resource not currently available!\n");
            }
         }
      }
   }
   printf("\n\tAVAILABLE\n\t");
   for(i=0;i<m;i++)
   {
      printf("R%d\t",i);
   }
   printf("\n\t");
   for(i=0;i<m;i++)
   {
      printf("%d\t",available[i]);
   }
   printf("\n\n\tMAXIMUM\n\t");
   for(i=0;i<m;i++)
   {
      printf("R%d\t",i);
   }
   printf("\n");
   for(i=0;i<n;i++)
   {
      printf("P%d\t",i);
      for(j=0;j<m;j++)
      {
         printf("%d\t",max[i][j]);
      }
      printf("\n");
   }
   printf("\n\tALLOCATED\n\t");
   for(i=0;i<m;i++)
   {
      printf("R%d\t",i);
   }
   printf("\n");
   for(i=0;i<n;i++)
   {
      printf("P%d\t",i);
      for(j=0;j<m;j++)
      {
         printf("%d\t",allocated[i][j]);
      }
      printf("\n");
   }
   printf("\n\tNEED\n\t");
   for(i=0;i<m;i++)
   {
      printf("R%d\t",i);
   }
   printf("\n");
   for(i=0;i<n;i++)
   {
      printf("P%d\t",i);
      for(j=0;j<m;j++)
      {
         printf("%d\t",need[i][j]);
      }
      printf("\n");
   }
   printf("\n");
   for(i=0;i<n;i++)
   {
      finish[i]=0;
   }
   count=0;
   do
   {
      flag=0;
      for(i=0;i<n;i++)
      {
         if(finish[i]==0)
         {
            for(j=0;j<m;j++)
            {
               if(need[i][j]>work[j])
               {
                  break;
               }
            }
            if(j==m)
            {
               for(k=0;k<m;k++)
               {
                  work[k]=work[k]+allocated[i][k];
               }
               safe[count++]=i;
               finish[i]=1;
               flag=1;
            }
         }
      }
      if(flag==0)
      {
         printf("The system is not in a safe state!\n");
         return 0;
      }
   }while(count<n);
   printf("The system is in a safe state!\nThe safe sequence is:");
   for(i=0;i<n;i++)
   {
      printf("P%d",safe[i]);
      if(i!=n-1)
      {
         printf("->");
      }
   }
   printf("\n");
   return 0;
}
