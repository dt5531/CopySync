#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "config.h"


Config::Config()
{
  m_sid = 0;
  m_pid = 0;
}

void Config::setSid(pid_t _sid)
{
  m_sid = _sid;
}

void Config::setPid(pid_t _pid)
{
  m_pid = _pid;
}

pid_t Config::getSid()
{
  return m_sid;
}

pid_t Config::getPid()
{
  return m_pid;
}
