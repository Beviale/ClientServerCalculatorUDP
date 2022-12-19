/*
 ============================================================================
 Name        : Esonero.c
 Author      : Alessandro Bevilacqua
 Version     : 1.0
 Date 	     : 10 dec 2022
 Description : Module that implements the server UDP connection.
 ============================================================================
 */

#include "../../Librerie UDP/src/udp.h"


int main()
{
	if(wsadata()==0)
	{
		system("pause");
		return -1;
	}
	int s_socket; // Server socket descriptor.
	if ((s_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		errorhandler("socket() failed");
		clearwinsock();
		system("pause");
		return -1;
	}
	if(serverBind(s_socket, "127.0.0.1", 56700)==0)
	{
		clearwinsock();
		system("pause");
		return -1;
	}

	char received_string[BUFFERSIZE]; // String received from the client.
	memset(received_string, 0, BUFFERSIZE);
	float op1=0; // First operand.
	float op2=0; // Second operand.
	char operator; // Operator.
	char *error="\nMissing or incorrect data!"; // Error message for incorrect operator or division by zero.
	char result[BUFFERSIZE]; // Operation result.
	char stringToSend[BUFFERSIZE]; // String to send to the client.
	struct sockaddr_in fromAddr; // Socket structure for the client.
	unsigned int fromSize = sizeof(fromAddr);
	while(1)
	{
		if(recvfrom(s_socket, received_string, BUFFERSIZE-1, 0, (struct sockaddr*)&fromAddr, &fromSize)>0)
		{
			op1=atof(received_string); // Converts the string of the first operand to a float value.
			if(recvfrom(s_socket, received_string, BUFFERSIZE-1, 0, (struct sockaddr*)&fromAddr, &fromSize)>0)
			{
				op2=atof(received_string); // Converts the string of the second operand to a float value.
				if(recvfrom(s_socket, received_string, BUFFERSIZE-1, 0, (struct sockaddr*)&fromAddr, &fromSize)>0)
				{
					operator=received_string[0]; // received_string[0] is the operator while received_string[1] is '\0'.
					char* clientAddress=inet_ntoa(fromAddr.sin_addr);
					char clientName[50];
					if(resolveDNS_aton(clientAddress, clientName)==0)
					{
						system("pause");
						return -1;
					}
					switch (operator)
					{
						case '+':
						   snprintf(result, BUFFERSIZE-1, "%.2f", add(op1, op2)); // Converts float to string for addition.
						   printf("\nRequest operation '+ %.2f %.2f' from the client %s, ip %s.", op1, op2, clientName, clientAddress); // Prints the request received from the client.
						   snprintf(stringToSend, BUFFERSIZE-1, "%.2f + %.2f = %s", op1, op2, result);
						   send_response(s_socket, stringToSend, fromAddr); // Sends the operation result for addition.
						   break;
						case 'x' : case 'X':
							snprintf(result, BUFFERSIZE-1, "%.2f", mul(op1, op2)); // Converts float to string for multiplication.
							printf("\nRequest operation 'x %.2f %.2f' from the client %s, ip %s.", op1, op2, clientName, clientAddress); // Prints the request received from the client.
							snprintf(stringToSend, BUFFERSIZE-1, "%.2f x %.2f = %s", op1, op2, result);
							send_response(s_socket, stringToSend, fromAddr); // Sends the operation result for multiplication.
						   break;
						case '-':
							snprintf(result, BUFFERSIZE-1, "%.2f", sub(op1, op2)); // Converts float to string for subtraction.
							printf("\nRequest operation '- %.2f %.2f' from the client %s, ip %s.", op1, op2, clientName, clientAddress); // Prints the request received from the client.
							snprintf(stringToSend, BUFFERSIZE-1, "%.2f - %.2f = %s", op1, op2, result);
							send_response(s_socket, stringToSend, fromAddr); // Sends the operation result for subtraction.
						   break;
						case '/':
						   if(op2==0)
						   {
							   send_response(s_socket, error, fromAddr); // Sends error if the second operand of the division is zero.
							   break;
						   }
						   snprintf(result, BUFFERSIZE-1, "%.2f", divi(op1, op2)); // Converts float to string for division.
						   printf("\nRequest operation '/ %.2f %.2f' from the client %s, ip %s.", op1, op2, clientName, clientAddress); // Prints the request received from the client.
						   snprintf(stringToSend, BUFFERSIZE-1, "%.2f / %.2f = %s", op1, op2, result);
						   send_response(s_socket, stringToSend, fromAddr); // Sends the operation result for division.
						   break;
						default:
							send_response(s_socket, error, fromAddr); // Sends error if the operator is incorrect.
						break;
					}// end switch.
				} // end if operator.

			} // end if number2.

		}//end if number1.

	} // end while: receive data from the client.

} // end main
