#include <stdio.h>
#include <stdlib.h>
/* You will to add includes here */

#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include<bits/stdc++.h>


// Included to get the support library
// #include <calcLib.h>
using namespace std;

#define MAX 80 
#define SA struct sockaddr 


vector<string> getIPandPort(string s){
      char buffer[100];
      int i;
      for(i=0;i<s.length();i++)
        buffer[i] = s[i];
      buffer[i] = '\0';

      char *p = strtok (buffer, ":");
      char *array[10];
      int counter=0;
      while (p != NULL)
      {
          array[counter++] = p;
          p = strtok (NULL, ":");
      }
      vector<string> args;
      args.push_back(array[0]);
      args.push_back(array[1]);
      return args;
}

int main(int argc, char *argv[]){
  
  /* Do magic */

	 vector<string> args = getIPandPort(argv[1]);
	  cout << "Requested IP: " << args[0] << " :: " << "Requested PORT: " << args[1] << "\n";
	  char IP[10];
	  int i;
	  for(i=0;i<args[0].length();i++)
	    IP[i] = args[0][i];
	  IP[i] = '\0';
	  int PORT = stoi( args[1] );


	// cout << argv[0] << "\n";
	char buffer1[1256], buffer2[1256]; 
    struct sockaddr_in my_addr, my_addr1; 
    int client = socket(AF_INET, SOCK_STREAM, 0); 
    if (client < 0) 
    printf("Error in client creating\n"); 
    else
        printf("Client Created\n"); 
          
    my_addr.sin_family = AF_INET; 
    my_addr.sin_addr.s_addr = INADDR_ANY; 
    my_addr.sin_port = htons(PORT); 
      
    // This ip address will change according to the machine 
    my_addr.sin_addr.s_addr = inet_addr(IP); 
  
    // Explicitly assigning port number 12010 by  
    // binding client with that port  
    my_addr1.sin_family = AF_INET; 
    my_addr1.sin_addr.s_addr = INADDR_ANY; 
    my_addr1.sin_port = htons(PORT); 
      
    // This ip address will change according to the machine 
    my_addr1.sin_addr.s_addr = inet_addr(IP); 
     
    if (bind(client, (struct sockaddr*) &my_addr1, sizeof(struct sockaddr_in)) == 0) 
    {cout << "";}
    else
    {cout << "";}
      
    socklen_t addr_size = sizeof my_addr; 
    int con = connect(client, (struct sockaddr*) &my_addr, sizeof my_addr); 
    if (con == 0) 
    {
        printf("Connection Successful\n"); 
    }
    else
        printf("Error in Connection\n"); 
  
    // strcpy(buffer2, "Hello"); 
    // send(client, buffer2, 256, 0);  
    while(1)
    {
    	recv(client, buffer1, 1256, 0); 
    	printf("Server : %s", buffer1); 
    	if(buffer1[0] == '\n')
    		break;
    }
    strcpy(buffer2, "OK\n"); 
    send(client, buffer2, 1256, 0); 
    cout << "\n";
   	int interaction = 1;
   	while(interaction)
   	{
   		recv(client, buffer1, 1256, 0); 
		printf("Server Question : %s\n", buffer1); 

		char str[1000];
		strcpy(str,buffer1);
		vector<string> ops;
		char* token = strtok(str, " "); 
	    while (token != NULL) { 
	        // printf("%s\n", token);
	        ops.push_back(token);
	        token = strtok(NULL, " "); 
	    } 
	    if( ops[0][0] == 'f' )
	    {
	    	float myAns;
	    	float v1 = stof(ops[1]);
	    	float v2 = stof(ops[2]);
	    	if( ops[0] == "fadd" )
	    		myAns = v1+v2;
	    	else if( ops[0]=="fsub" )
	    		myAns = v1-v2;
	    	else if( ops[0]=="fdiv" )
	    		myAns = v1/v2;
	    	else myAns = v1*v2;

	    	char answer[100];
		    int j=0;
		    string ans = to_string(myAns);
		    for(int i=0;i<ans.length();i++)
		    	answer[j++] = ans[i];
		    answer[j] = '\0';
		    
		    strcpy(buffer2, answer); 
	    	send(client, buffer2, 1256, 0); 
	    }
	    else{
	    	int myAns;
	    	int v1 = stoi(ops[1]);
	    	int v2 = stoi(ops[2]);
	    	if( ops[0] == "add" )
	    		myAns = v1+v2;
	    	else if( ops[0]=="sub" )
	    		myAns = v1-v2;
	    	else if( ops[0]=="div" )
	    		myAns = v1/v2;
	    	else myAns = v1*v2;

	    	char answer[100];
		    int j=0;
		    string ans = to_string(myAns);
		    for(int i=0;i<ans.length();i++)
		    	answer[j++] = ans[i];
		    answer[j] = '\0';
		    
		    strcpy(buffer2, answer); 
	    	send(client, buffer2, 1256, 0); 
	    }

	    recv(client, buffer1, 1256, 0); 
		printf("Server : %s\n", buffer1); 
	    interaction-=1;

   	}
	
    
    
    return 0; 
  

}
