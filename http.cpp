// HTTP Library functions
// Original author:  Gordon Griesel

#include "http.h"

int create_tcp_socket()
{
  int sock;
  if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror("Can't create TCP socket");
    exit(1);
  }
  return sock;
}

char *get_ip(char *host)
{
  struct hostent *hent;
  //ip address format  123.123.123.123
  // --------------------------------------------------------------------------
  // Fixed runtime error: Can't resolve host with inet_ntop: No space left on
  //                      device
  // Previous code was:  int iplen = 15
  // Original code overflows the buffer on inet_ntop().  Need to give it a
  // length of 16 to include the trailing \0 on the IP address string.
  // -------------------------------------------------------------------------- 
  int iplen = 16;
  char *ip = (char *)malloc(iplen+1);
  memset(ip, 0, iplen+1);
  if ((hent = gethostbyname(host)) == NULL) {
    herror("Can't get IP host by name");
    exit(1);
  }
  //printf("hent->h_addr_list[0] = %si\n", hent->h_addr_list[0]);
  if (inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL) {
    perror("Can't resolve host with inet_ntop");
    exit(1);
  }
  return ip;
}

char *build_get_query(char *host, char *page)
{
  char *query;
  char *getpage = page;
  // --------------------------------------------------------------------------
  // Fixed warning: ISO C++ forbids converting a string constant to 'char*'
  // Previous code was: char *tpl = ...
  // --------------------------------------------------------------------------
  const char *tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";
  if (getpage[0] == '/') {
    getpage = getpage + 1;
    fprintf(stderr,"Removing leading \"/\",");
    fprintf(stderr, " converting %s to %s\n", page, getpage);
  }
  // -5 is to consider the %s %s %s in tpl and the ending \0
  query = (char *)malloc(strlen(host)+strlen(getpage)+strlen(USERAGENT)\
          +strlen(tpl)-5);
  sprintf(query, tpl, getpage, host, USERAGENT);
  return query;
}

