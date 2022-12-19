/*
 * Created on: 10 dec 2022
 * udp.c
 * Author: Alessandro Bevilacqua
 */

#include "udp.h"
struct sockaddr_in echoServAddr; // 1) Used by the client to create the socket structure for the server. 2) Used by the server to execute the operation bind.


// Prints error message.
void errorhandler(const char *error_message)
{
    printf("%s", error_message);
}


void clearwinsock()
{
    #if defined WIN32
    WSACleanup();
    #endif
}


// Initialize WSAStartup().
bool wsadata()
{
    #if defined WIN32
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2,2), &wsa_data);
    if(result!=0)
    {
        printf("\nError at WSAStartup\n");
        return 0;
    }
    #endif
    return 1;
}



// Used by the client to initialize the data structure for the server. Accepts the Server IP address (as a string value) and the Server port number (as an int value).
void createServerAddress(const char* ServerAddress, int port)
{
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family=AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(ServerAddress); // Server IP address.
    echoServAddr.sin_port = htons(port); // Server port number.
}



// Sends operands and operator from the client to the server.
void send_operation(int socket, float op1, float op2, char operator)
{
	char number1[BUFFERSIZE]; // String containing the first operand.
	char number2[BUFFERSIZE]; // String containing the second operand
	char convert_operator[2]; // String containing the operator and '\0'.
	snprintf(number1, BUFFERSIZE-1, "%.2f", op1); // Converts from float to string.
	printf("\nThe first number you entered is: %s", number1);
	send_data_tos(socket, number1);
	snprintf(number2, BUFFERSIZE-1, "%.2f", op2); // Converts from float to string.
	printf("\nThe second number you entered is: %s", number2);
	send_data_tos(socket, number2);
	convert_operator[0]=operator; // Defines a character as a string.
	convert_operator[1]='\0';
	send_data_tos(socket, convert_operator);
}


// Send a string from the client to the server. Accepts the client socket and the string.
void send_data_tos(int socket, char *data)
{
	if(sendto(socket, data, (strlen(data)+1)*sizeof(char), 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr))!=(strlen(data)+1)*sizeof(char))
	{
		errorhandler("\nSend() sent a different number of bytes than expected");
		return;
	}
	return;
}


// Send a string from the server to the client. Accepts the server socket, the string and the socket structure containing client information.
void send_response(int socket, char *data, struct sockaddr_in echoClntAddr)
{
	if(sendto(socket, data, (strlen(data)+1)*sizeof(char), 0, (struct sockaddr*)&echoClntAddr, sizeof(echoClntAddr))!=(strlen(data)+1)*sizeof(char))
	{
		errorhandler("\nSend() sent a different number of bytes than expected");
		return;
	}
	return;
}




// From a name returns the corresponding IP address in the second parameter. Accepts the host name and a second string value to put the result.
bool resolveDNS_ntoa(char* name, char* result)
{
	struct hostent *host;
	host = gethostbyname(name);
	if (host == NULL)
	{
		errorhandler("gethostbyname() failed.\n");
		return 0;
	}
	struct in_addr* ina = (struct in_addr*) host->h_addr_list[0];
	strcpy(result, inet_ntoa(*ina));
	return 1;
}


// From an IP address returns the corresponding canonical name in the second parameter. Accepts the host IP address and a second string value to put the result.
bool resolveDNS_aton(char* address , char* result)
{
	struct hostent *host;
	struct in_addr addr;
	addr.s_addr = inet_addr(address);
	host = gethostbyaddr((char *) &addr, 4, AF_INET);
	if(host==NULL)
	{
		errorhandler("gethostbyname() failed.\n");
		return 0;
	}
	strcpy(result, host->h_name);
	return 1;
}






// For the division.
float divi(float first, float second)
{
	return first/second;
}

// For the addition.
float add(float first, float second)
{
	return first+second;
}

// For the subtraction.
float sub(float first, float second)
{
	return first-second;
}


// For the multiplication.
float mul(float first, float second)
{
	return first*second;
}

// Initialize echoServAddr and execute the bind operation. Accepts the server socket, the server IP address as a string value and the port number as an int value.
bool serverBind(int sock, const char* address, int port)
{
	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_port = htons(port);
	echoServAddr.sin_addr.s_addr = inet_addr(address);
	if ((bind(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr))) < 0)
	{
		errorhandler("bind() failed");
			return 0;

	}
	return 1;
}















