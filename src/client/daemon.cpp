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

Deamon::Deamon()
{
  m_configs = unique_ptr<Config>(new Config());
  m_clipbd = unique_ptr<Clipboard>(new Clipboard());
  init_log();
  init_process();
}


void Daemon::process()
{

  syslog(LOG_NOTICE, "Writing to my Syslog");
  m_clipbd->update();
}   

void Daemon::init_log()
{
  //Set our Logging Mask and open the Log

  setlogmask(LOG_UPTO(LOG_NOTICE));

  openlog("CopySync", LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);

  syslog(LOG_INFO, "Daemon starting");
}

void Daemon::init_process()
{
  pid_t pid, sid;

  // Fork the Parent Process
  pid = fork();

  if (pid < 0) 
  { 
    exit(EXIT_FAILURE); 
  }

  // Close the Parent Process

  if (pid > 0)
  {
    exit(0); 
  }

  //Change File Mask

  umask(027);

  // change directory for logging

  if (chdir("/home/david/work/daemon/CopySync/log") < 0)
  {
    throw std::exception("Can't get into log location.");
  }

  // Create a new Signature Id for our child

  sid = setsid();
  if (sid < 0) 
  { 
    throw std::exception("Failed to get a session ID.");
  }

  m_configs->setSid(sid);
  m_configs->setPid(pid);
}

void Daemon::clean()
{
  closelog();
}

void Daemon::run()
{
  while(true)
  {
    process(clipbd.get());           //Run our Process
    sleep(1);                   //Update once every second
  }

}
