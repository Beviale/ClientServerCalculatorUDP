/*
 ============================================================================
 Name        : Esonero 2 Client.c
 Author      : Alessandro Bevilacqua
 Version     : 1.0
 Date 	     : 10 dec 2022
 Description : Module that implements the client UDP connection.
 ============================================================================
 */


#include "../../Librerie UDP/src/udp.h"

int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("%s", "\nIncorrect parameters!");
		system("pause");
		return -1;
	}
	char serverName[100];
    const char separator[]=":";
	strcpy(serverName, strtok(argv[1], separator));
	int portNumber = atoi(strtok(NULL, separator));
	if(wsadata()==0)
	{
		system("pause");
		return -1;
	}
	int c_socket; // Socket descriptor.
	c_socket= socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); // Socket initialization.
	if(c_socket<0)
	{
		errorhandler("\nSocket creation failed.\n");
		clearwinsock();
		system("pause");
		return -1;
	}
	char serverAddress[20]; // String containing the Server IP address in dotted format.
	if(resolveDNS_ntoa(serverName, serverAddress)==0)
	{
		clearwinsock();
		system("pause");
		return -1;
	}
	createServerAddress(serverAddress, portNumber);
	float op1=0; // First operand.
	float op2=0; // Second operand.
	char operator; // Operator.
	while(1) // loop
	{
		printf("\nEnter operator and operands in the format OperatorSpaceOperand1SpaceOperand2: ");
		fflush(stdin); // Cleaning of the output buffer.
		if(scanf("%c %f %f", &operator, &op1, &op2)!=3) // The scanf() function returns the number of fields that were successfully converted and assigned.
		{
			printf("\nScanf() Error!");
			system("pause");
			continue;
		}
		if(operator=='=')
		{
			printf("\nYou chose to exit.");
			system("pause");
			return 0;
		}
		send_operation(c_socket, op1, op2, operator); // Sends operands and operator to the server.
		struct sockaddr_in fromServerAddr; // Socket structure containing server information.
		unsigned int fromSize = sizeof(fromServerAddr);
		char received_result[BUFFERSIZE]; // Operation result.
		memset(received_result, 0, BUFFERSIZE);
		if(recvfrom(c_socket, received_result, BUFFERSIZE-1, 0, (struct sockaddr*)&fromServerAddr, &fromSize)>0) // As soon as the client receives the result from the server...
		{
			printf("\nReceived result from server %s, IP address %s: %s.", serverName, serverAddress, received_result);
		}else
		{
			continue;
		}
	}
}
