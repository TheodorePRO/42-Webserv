#include "incs/network/ListeningSocket.hpp"
#include "incs/network/Server.hpp"
#include <stdio.h>

// Test Socket

extern char **environ;

int main(int argc, char **argv)
{
  int i;

  if( environ != NULL )
    for( i=0; environ[i]; i++ )
      printf("%s\n",environ[i]);

  return 0;
}


