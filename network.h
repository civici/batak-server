#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <errno.h>

#include <pthread.h>


#include "client.h"

#define clientsize sizeof(struct client)

struct client* clients[2];

int network_openserver();