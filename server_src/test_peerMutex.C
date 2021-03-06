#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // for exit(), atoi()

#include <vrpn_Mutex.h>


int rg (void *) {
  printf("callback - Mutex granted.\n");
  return 0;
}

int rd (void *) {
  printf("callback - Mutex denied.\n");
  return 0;
}

int rel (void *) {
  printf("callback - Mutex released.\n");
  return 0;
}

int main (int, char ** argv) {

  vrpn_PeerMutex * me;
  char inputLine [100];

  me = new vrpn_PeerMutex (argv[1], atoi(argv[2]));

  me->addRequestGrantedCallback(NULL, rg);
  me->addRequestDeniedCallback(NULL, rd);
  me->addReleaseCallback(NULL, rel);

  printf("req - request the mutex.\n");
  printf("rel - release the mutex.\n");
  printf("? - get current mutex state.\n");
  printf("add - add a peer site to the mutex.\n");
  printf("quit - exit.\n");

  while (1) {

    me->mainloop();
    memset(inputLine, 0, 100);
    if (fgets(inputLine, 100, stdin) == NULL) {
	perror("could not read line");
	return -1;
    }

    if (!strncmp(inputLine, "req", 3)) {
      printf("test_mutex:  sending request.\n");
      me->request();
    } else if (!strncmp(inputLine, "rel", 3)) {
      printf("test_mutex:  sending release.\n");
      me->release();
    } else if (!strncmp(inputLine, "?", 1)) {
      printf("isAvailable:  %d.\n", me->isAvailable());
      printf("isHeldLocally:  %d.\n", me->isHeldLocally());
      printf("isHeldRemotely:  %d.\n", me->isHeldRemotely());
      printf("numPeers:  %d.\n", me->numPeers());
    } else if (!strncmp(inputLine, "add", 3)) {
      printf("Name of peer:  ");
      fflush(stdout);
      if (fgets(inputLine, 100, stdin) == NULL) {
	perror("could not read line");
	return -1;
      }
      me->addPeer(inputLine);
    } else if (!strncmp(inputLine, "quit", 4)) {
      delete me;
      exit(0);
    } else {
      printf(".\n");
    }
  }


}


