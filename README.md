# ClientServerCalculatorUDP
<b>Development and implementation of a UDP client/server application written in c language, where the server is a basic remote calculator that responds to client requests.</b>

<i>This is a university project of the computer networks course.</i>
  
  
To run the server follow the path below:"Esonero 2 Server/Debug/Esonero2server.exe".
To run the client follow the path below:"Esonero 2 Client/Debug/Esonero2Client.exe".

1) The client is started passing as input parameters the name and port number of the UDP server to contact, respecting the following format: srv.di.uniba.it:56700.
2) The client reads the choice of operation to perform (using the characters +, x, -, /, respectively for Addition, Multiplication, Subtraction and Division) and two integers from the standard input, respecting the following format: + 23 45.
3) The client sends what is read from the keyboard to the server.
4) Once the data has been received from the client, the server displays a message on the std output containing both the name and the address of the client's host and the operation to be performed (Example: Operation request '+ 23 45' from the client foo.di.uniba .it, IP 193.204.187.154).
5) The server follows the requested operation and sends the result to the client in the exact format shown in the examples below:
23 + 45 = 68 for addition;
23 / 45 = 0.51 for division;
23 * 45 = 1035 for the product;
23 - 45 = -22 for subtraction.
6) The client reads the response sent by the server and displays the response on the std output (Example: Received result from server srv.di.uniba.it, ip 193.204.187.166: 23 + 45 = 68).
7) The client reads the next operation to be performed from the standard input.
8) If the character = is entered instead of an operation, the client terminates its process here; otherwise, go back to step 2.
9) The server never terminates its process.
