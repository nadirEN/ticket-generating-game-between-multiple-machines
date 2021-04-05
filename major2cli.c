#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h> /* Added for the nonblocking socket */


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>



//#define PORT 4444
char                    buffer[1024];


int por;
char *arv;




void  ipfunction( void);

void client_srv(int port);

void transition(int ns);

char array[50];



int main(int argc, char *argv[]) 
{



 if (argc != 3) {printf("Error: Usage ./a.out 'machine'  'port'\n ");}
 else {
 
 int PORT;   
 int                     clientsocket, ret;
 struct  sockaddr_in     serveraddr; /* connector's address information */
  struct  sockaddr_in     currentaddr; /* connector's address information */


 
struct hostent *hname;          /* use to get host name. */



 PORT  = atoi(argv[2]);           /* converting string into int. */

  if ((clientsocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                perror("error  in connection");
                exit(1);
        }

  printf("client  socket created\n");

 if ((hname = gethostbyname(argv[1])) == NULL) 
       {         /* get the host info. */
                printf("host not exist: Connection timed out\n");
                exit(1);
        }


   
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;         /* host byte order */
    serveraddr.sin_port = htons(PORT);     /* short, network byte order */
    bcopy((char *)hname->h_addr, (char *)&serveraddr.sin_addr.s_addr, hname->h_length);   /* assigning host name. */



    if (ret = connect(clientsocket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {  /* Connect to the server. */
                perror("connect error");
                exit(1);
        }
  
   printf("connected to the server\n"); 


   while(1)
     {   int value;
       printf("%d: enter client Data : \t", clientsocket);
       gets(buffer);
       send(clientsocket, buffer, strlen(buffer), 0);
             




       if  ( recv(clientsocket, buffer, sizeof(buffer), 0) < 0)
             {    printf("error in receiving data\n"); }     
          else
             {   if ( strcmp(buffer, "Disconnected")==0 )
                           {
                            printf("Disconnected\n");
                              recv(clientsocket, buffer, sizeof(buffer), 0);
                             value = atoi(buffer);
                             printf("   Port: %d\n", value);                         
   

                              ipfunction();
                               send(clientsocket, array, strlen(array), 0);               
                              client_srv(value);
     

                              break;
     
                           }
                   if ( strcmp(buffer, "transition")==0 )
                             {
                                 printf("\n\n connectin second server\n");                         
                                    transition(clientsocket );
  
                              }                
 

                else {
                 value = atoi(buffer);
                 printf("   Server Total: %d\n", value); 
	         memset((void *)buffer, 0, 11);	
	     }}



     }


return 0;


}
}



void  client_srv(int p)
{

int PORT = p;
int                     sockfd, ret;
struct  sockaddr_in     serveraddr;    /* my address information */
struct  sockaddr_in     newaddr1;    /* my address information */

 int              ns;

  pthread_t tid;



  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                perror("error connection");
                exit(EXIT_FAILURE);
        }

  printf("\n----- second server--- \n connection created\n");
      printf("New Server IP: %s\n", array);
     printf("New Server Port : %d\n", p);     


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


    if (listen(sockfd, 10) == 0) {  printf("connecting to remote client....\n ..... \n"); }
     else   {
                perror("listen error");
                exit(1);
            }


   int len1 = sizeof( newaddr1);


while(1)
       {
            

               ns  = accept(sockfd, (struct sockaddr *)&newaddr1, &len1);
               if (ns  < 0)
                     { printf("Error connecting client %d \n", ns);
                      exit(1);
                      }


             else
                { 
                   printf("connection accepted from client %d\n", ns );
                
                   while(1)
                    {  
                      printf("enter what to send : ");
                              gets(buffer);
                              send(ns, buffer, strlen(buffer), 0 );
                              bzero(buffer, sizeof(buffer));
                     
                     
                        
                             recv(ns, buffer, 1024, 0);
                        if (strcmp(buffer, ":exit")== 0)
                           { printf("disconnected from  %d\n", ns);
                             break;
                           }
                        else {     printf("message received : %s\n", buffer);
                              }
         

                     }  
 
               }

   }
}





void ipfunction(void)
{
 int fd;
 struct ifreq ifr;


 fd = socket(AF_INET, SOCK_DGRAM, 0);

 /* I want to get an IPv4 IP address */
 ifr.ifr_addr.sa_family = AF_INET;

 /* I want IP address attached to "eth0" */
 strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

 ioctl(fd, SIOCGIFADDR, &ifr);

 close(fd);

 /* display result */
 printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
strcpy(array, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));



}

void transition(int ns)
{


char buffer[1024];           
                      

                             recv(ns, buffer, 1024, 0);
                        if (strcmp(buffer, ":exit")== 0)
                           { printf("error from  %d\n", ns);
                             
                           }
                        else {     printf("IP received : %s\n", buffer);
                              }
                     
                          



                           

                    


}






