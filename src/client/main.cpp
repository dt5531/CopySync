#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <memory>

#include "daemon.h"
#include "config.h"

using namespace std;

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
    return 1;
  }
  return 0;
}
