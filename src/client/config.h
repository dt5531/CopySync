#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>



class Config
{
  public:
    Config();
    void setSid(pid_t _sid);
    void setPid(pid_t _pid);
    pid_t getSid();
    pid_t getPid();

  private:
    pid_t m_sid;
    pid_t m_pid;
};
