/*
 * udp.h
 * Created on: 10 dec 2022
 * Author: Alessandro Bevilacqua
 */

#ifndef UDP_H_
#define UDP_H_

#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 255 // Define the size of the buffer.

// For Client and Server
void errorhandler(const char *error_message);
void clearwinsock();
bool wsadata();
bool resolveDNS_aton(char *, char *); // Address to name.
bool resolveDNS_ntoa(char *, char *); // Name to address.


// For Server
bool serverBind(int, const char*, int);
void send_response(int, char*, struct sockaddr_in);


// For Client
void createServerAddress(const char *, int);
void send_operation(int, float, float, char);
void send_data_tos(int, char*);


// Available operations
float add(float, float);
float divi(float, float);
float sub(float, float);
float mul(float, float);



#endif /* UDP_H_ */
