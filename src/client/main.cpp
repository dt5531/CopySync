#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "daemon.h"
#include "config.h"

using namespace std;

void sig_handler(int SIG)
{
  closelog();
  exit(0);
}

int main(int argc, char** argv)
{
  try
  {
    unique_ptr<Daemon> daemon = unique_ptr<Daemon>(new Daemon());
    daemon->run();
    daemon->stop();
  }
  catch (exception& e)
  {
    cout << "exception " << e.what() << "has occured" << endl;
    return 1;
  }
  return 0;
}
