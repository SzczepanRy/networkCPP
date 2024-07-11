#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <minwindef.h>
#include <system_error>
#include <winsock.h>
using namespace std;
#define PORT 6000

/*
struct sockaddr_in   {
  short sin_family;
  u_short sin_port;
  struct in_addr sin_addr;
  char sin_zero[8];
};
*/
struct sockaddr_in srv;

int main() {
  int nRet = 0;

  // init the WSA varables its supports socket programing on windows
  // IMPORTANT

  WSADATA ws;
  if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
    cout << "WSA not loaded\n";
    exit(EXIT_FAILURE);
  } else {
    cout << "loaded WSA\n";
  }

  // init socket
  // connection stream socket
  // AF_INET -- when using tcp or udp
  //
  int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (nSocket < 0) {
    cout << "socket not opened\n";
    exit(EXIT_FAILURE);
  } else {
    cout << nSocket << " :id  opened sucessfully\n";
  }
  // init the env for socketAddr structure
  srv.sin_family = AF_INET;
  // htons converts big Endian ofthe host to the little Endian of the network
  srv.sin_port = htons(PORT);
  srv.sin_addr.s_addr = INADDR_ANY; // assigning the addr to your one
  // arternative: srv.sin_addr.s_addr = inet_addr("127.0.0.1");//inet_addr
  // converts strings to byte order
  memset(srv.sin_zero, 0, 8);

  // bind the socket to the lockal port
  nRet = bind(nSocket,(sockaddr*) &srv , sizeof(sockaddr) );

  if(nRet <0 ){
    cout << "faled to bind to lockal port\n";
    exit(EXIT_FAILURE);
  }else{
    cout << "sucessfully bound to lockal port\n";
  }

  // listen to the request form client

  nRet = listen(nSocket , 5 ); // the second arg is a backlog : how meany request at a time the server can pull (active queue)
  if(nRet <0 ){
    cout << "faled to start listentnig to local port \n";
    exit(EXIT_FAILURE);
  }else{
    cout << "sucessfully listening to locka port\n";
  }


  // Kwep waiting for new request and process as per the request

  return 0;
}
