// Functions to support leaderboard scores lookup over HTTP

#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define USERAGENT "HTMLGET 1.0"

int create_tcp_socket();
char *get_ip(char *host);
char *build_get_query(char *host, char *page);

#endif
