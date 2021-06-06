#include <stdio.h>
#include <stdlib.h>
/* You will to add includes here */

#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include<bits/stdc++.h>
#include<time.h>
// Included to get the support library
// #include <calcLib.h>



using namespace std;

#define MAX 80 
#define SA struct sockaddr
#define LIMIT 1000


string convertToOpString(string op, float v1, float v2)
{
	string s1 = to_string(v1);
	string s2 = to_string(v2);
	string s3 = op;
	string ret = s3 + " " + s1 + " " + s2;
	return ret;

}

string convertToOpString(string op, int v1, int v2)
{
	string s1 = to_string(v1);
	string s2 = to_string(v2);
	string s3 = op;
	string ret = s3 + " " + s1 + " " + s2;
	return ret;

}

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

  /* Do more magic */

  // cout << argc << '\n';
  // cout << argv[1] << "\n";
  vector<string> args = getIPandPort(argv[1]);
  cout << "Requested IP: " << args[0] << " :: " << "Requested PORT: " << args[1] << "\n";
  char IP[10];
  int i;
  for(i=0;i<args[0].length();i++)
    IP[i] = args[0][i];
  IP[i] = '\0';
  int PORT = stoi( args[1] );

	srand(time(0));
	char buffer1[1256], buffer2[1256]; 
    int server = socket(AF_INET, SOCK_STREAM, 0); 
    if (server < 0) 
    {
        printf("Error in server creating\n"); 
    }
    else
    {
        cout << "";
    }
          
    struct sockaddr_in my_addr, peer_addr; 
    my_addr.sin_family = AF_INET; 
    my_addr.sin_addr.s_addr = INADDR_ANY; 
      
    // This ip address will change according to the machine 
    my_addr.sin_addr.s_addr = inet_addr(IP); 
      
    my_addr.sin_port = htons(PORT); 
  
    if (bind(server, (struct sockaddr*) &my_addr, sizeof(my_addr)) == 0) 
    {
        cout << "";
    }
    else
    {
        printf("Unable to bind\n"); 
    }
          
    if (listen(server, 3) == 0) 
    {
        printf("Listening ...\n"); 
    }
    else
    {
        printf("Unable to listen\n"); 
    }
      
    socklen_t addr_size; 
    addr_size = sizeof(struct sockaddr_in); 
      
    // Ip character array will store the ip address of client 
    char *ip; 
      
    // while loop is iterated infinitely to  
    // accept infinite connection one by one 

    while (1) 
    { 
    	printf("Waiting for client .....\n");
        int acc = accept(server, (struct sockaddr*) &peer_addr, &addr_size); 
        printf("Connection Established\n"); 
        char ip[INET_ADDRSTRLEN]; 
        inet_ntop(AF_INET, &(peer_addr.sin_addr), ip, INET_ADDRSTRLEN); 
      
        // "ntohs(peer_addr.sin_port)" function is  
        // for finding port number of client 
        printf("Connection established with IP : %s and PORT : %d\n",  ip, ntohs(peer_addr.sin_port)); 
  
  		char versions[3][50] = {"TEXT TCP 1.0\n", "TEXT TCP 1.1\n", "\n"}; 
  		for( int i=0;i<3;i++ )
  		{
  			strcpy(buffer1, versions[i]); 
        	send(acc, buffer1, 1256, 0); 
  		}
  		recv(acc, buffer2, 1256, 0); 
        printf("Client : %s", buffer2); 
        cout << "\n";
        vector<string> operations = {"add","fadd","sub","fsub","div","fdiv","mul","fmul"};
       	int interaction=1;
  		while(interaction)
  		{
  			int rand_op = rand()%8;
  			string chosen_operation = operations[rand_op];
  			// cout << chosen_operation << '\n';
  			if( chosen_operation[0] == 'f' )
  			{
  				// floating point operation
  				float A = rand()%LIMIT;
  				float B = rand()%100;
  				float v1 = A/B;

  				A = rand()%LIMIT;
  				B = rand()%100;
  				float v2 = A/B;
  				// cout << v1 << " " << v2 << "\n";
  				float actualAns;
  				if( chosen_operation == "fadd" )
  					actualAns = v1+v2;
  				if( chosen_operation == "fsub" )
  					actualAns = v1-v2;
  				if( chosen_operation=="fmul" )
  					actualAns = v1*v2;
  				if( chosen_operation=="fdiv" )
  				{
  					// no divison of 0 is allowed
  					if((int)v2 == 0)
  						v2+=1;
  					actualAns = v1/v2;
  				}
  				// cout << v1 << " " << v2 << " " << actualAns<< "\n";
  				string sendOpString = convertToOpString(chosen_operation, v1, v2);
  				char send_str[100];
  				int j = 0;
  				for(int i=0;i<sendOpString.length();i++)
  					send_str[j++] = sendOpString[i];
  				send_str[j] = '\0';
  				printf("Question : %s\n",send_str );
  				strcpy(buffer1, send_str); 
        		send(acc, buffer1, 1256, 0); 

        		recv(acc, buffer2, 1256, 0); 
        		printf("Client's Answer : %s\n", buffer2); 
        		cout << "\n";

        		string b = buffer2;
        		float clientAnswer = stof(b);
        		if( abs(clientAnswer-actualAns) < 0.0001 )
        		{
        			strcpy(buffer1, "OK"); 
        			send(acc, buffer1, 1256, 0); 
        		}
  				else
        		{
        			strcpy(buffer1, "ERROR"); 
        			send(acc, buffer1, 1256, 0); 
        		}
  				

  			}
  			else{
  				// normal integer operation
  				int v1 = rand()%LIMIT;
  				int v2 = rand()%LIMIT;
  				int actualAns;
  				if( chosen_operation == "add" )
  					actualAns = v1+v2;
  				if( chosen_operation == "sub" )
  					actualAns = v1-v2;
  				if( chosen_operation=="mul" )
  					actualAns = v1*v2;
  				if( chosen_operation=="div" )
  				{
  					// no divison of 0 is allowed
  					if(v2 == 0)
  						v2+=1;
  					actualAns = v1/v2;
  				}
  				// cout << v1 << " " << v2 << " " << actualAns<< "\n";
  				string sendOpString = convertToOpString(chosen_operation, v1, v2);
  				char send_str[100];
  				int j = 0;
  				for(int i=0;i<sendOpString.length();i++)
  					send_str[j++] = sendOpString[i];
  				send_str[j] = '\0';
  				printf("Question: %s\n",send_str );
  				strcpy(buffer1, send_str); 
        		send(acc, buffer1, 1256, 0); 

        		recv(acc, buffer2, 1256, 0); 
        		printf("Client's Answer : %s\n", buffer2); 
        		cout << "\n";

        		string b = buffer2;
        		int clientAnswer = stoi(b);
        		if( abs(clientAnswer-actualAns) == 0 )
        		{
        			strcpy(buffer1, "OK"); 
        			send(acc, buffer1, 1256, 0); 
        		}
  				else
        		{
        			strcpy(buffer1, "ERROR"); 
        			send(acc, buffer1, 1256, 0); 
        		}
  			}

  			interaction-=1;
        	

  		}
        
        
    }  
    return 0; 


}
