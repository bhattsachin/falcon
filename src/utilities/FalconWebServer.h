/*
 * FalconWebServer.h
 *
 *  Created on: Nov 24, 2011
 *      Author: bhatt
 */

#ifndef FALCONWEBSERVER_H_
#define FALCONWEBSERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "CommandLine.h"

int run();
void sigchld_handler(int s);
void *get_in_addr(struct sockaddr *sa);


#endif /* FALCONWEBSERVER_H_ */
