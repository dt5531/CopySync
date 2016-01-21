#pragma once
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



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
