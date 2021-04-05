#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h> /* Added for the nonblocking socket */
#include <sys/select.h> 
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>







void * function1(int a, int* b  );
void  function2( int a);

 char         buffer[1024];
 char         array[1024];

 int fd1, fd2, cond;



int main(int argc, char *argv[])
{
 int PORT;
 int                     sockfd, ret;
 struct  sockaddr_in     serveraddr;    /* my address information */

typedef struct t
{
 int t[100];
}myarray;



 int                     ns[10], ns2;
struct  sockaddr_in     newaddr1; /* connector's address information */
 struct  sockaddr_in     newaddr2; /* connector's address information */
 

if (argc != 2 ) {printf("arror:  usage ./a.out port\n");}
 else 
   {


 pid_t                   pid;
  
  int len1, len2;

    pthread_t tid;
  
   
  PORT  = atoi(argv[1]);           /* converting string into int. */
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                perror("error connection");
                exit(EXIT_FAILURE);
        }

  printf("connection created\n");


   memset(&serveraddr, '\0', sizeof(serveraddr));
   serveraddr.sin_family = AF_INET;         /* host byte order */
   serveraddr.sin_port = htons(PORT);     /* short, network byte order */
   serveraddr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */

   if (ret = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
        {
                perror("bind error");
                exit(1);
        }
    printf("binding created\n");


    if (listen(sockfd, 10) == 0) {  printf("listening....\n"); }
     else   {
                perror("listen error");
                exit(1);
            }


   len1 = sizeof( newaddr1);
   len2 = sizeof( newaddr2 );

 

fd_set which_client;
int sel;
int max;
struct timeval timeout;
 
   int i=0, clientnum=0; 
    while(1)
       {  
            if (clientnum < 2)
             
             {  ns[i]  = accept(sockfd, (struct sockaddr *)&newaddr1, &len1); 
               if (ns[i] < 0) 
                     { printf("Error connecting client %d \n", ns[i]);
                      exit(1);
                      }
            
             
             else { 
                     
             printf("connection accepted from client %d\n", ns[i] );
     
           if (clientnum ==0 ) {fd1= ns[i];}
            
           clientnum++;

                 if (  (clientnum >  1)  && (ns[i] > 0)  )    {fd2= ns[i];}
              
         
             pid =fork();
             if (pid==0)
               {
                         
                   
                  close(sockfd);
                  
                 
             
               
              
                   pthread_create(&tid, NULL, function1(ns[i], &fd2), NULL); 
                                 
         
         

                    


               }


                   }

                   }
            else {   if ( accept(sockfd, (struct sockaddr *)&newaddr1, &len1) > 0  ) 
                        {printf("too many client\n");}
                  }    
                  
            }

  close(sockfd );
}
}



void * function1( int ns1, int* fd2 )
{ 

       
       pthread_t tid; 
     int value, total=0;
     cond =0;
     int x = fd1+1; 
     while(1)
                    {   
                      recv(ns1, buffer, 1024, 0);
                      value = atoi(buffer); 
                      total = total+ value;       
                      printf("client %d : total = %d\n",ns1, total);
                      if (  ( total >=  1024) &&  (total <= 49151) )
                           { printf("disconnected from  client %d\n", ns1);   
                             send(ns1, "Disconnected", 100, 0 );
      
                              sprintf(buffer, "%d", total);
                                send(ns1, buffer, sizeof(buffer), 0 );
                              bzero(buffer, sizeof(buffer));








                                 
                                      
                              recv(ns1, array, 1024, 0);
                                      

                              printf("the IP of client who become server : %s\n", array); 
                              
 
                               break;
                           }
                     
                      else { 
                             
                             
                            
                              bzero(buffer, sizeof(buffer));
                              sprintf(buffer, "%d", total);
                              send(ns1, buffer, sizeof(buffer), 0 );
                              bzero(buffer, sizeof(buffer));

                           }             
    
           
                     } 

}

void  function2( int fd)
{
     
  
                   
            send(fd, "transition", 64 , 0 );
            bzero(buffer, sizeof(buffer));
            send(fd, array, sizeof(array), 0 );


                     

}







