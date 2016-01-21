#include <errno.h>
#include <fcntl.h>
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

Daemon::Daemon()
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
    throw "unable to fork";
  }

  // Change File Mask, allow owner to modify everything, group to have read
  // and others have no permission to do anything
  umask(027);

  // change directory for logging
  if (chdir("/home/david/work/daemon/CopySync/log") < 0)
  {
    throw "Can't get into log location.";
  }

  // Create a new Signature Id for our child
  sid = setsid();
  if (sid < 0) 
  { 
    throw "Failed to get a session ID.";
  }
  catch (string e)
  {
    cout << "An error has occured. " << e << endl;
    exit(1);
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
    process();                  //Run our Process
    sleep(1);                   //Update once every second
  }

}

void Daemon::stop()
{
  clean();
}
