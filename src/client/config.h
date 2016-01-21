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
    // This function takes a sid as arguement and returns nothing.
    // This functions stores the program's sid.
    void setSid(pid_t _sid);
    // This function takes a pid as arguement and returns nothing.
    // This functions stores the program's pid.
    void setPid(pid_t _pid);
    // This function takes nothing as argument and return the program's sid.
    // This function returns the program's sid.
    pid_t getSid();
    // This function takes nothing as argument and return the program's pid.
    // This function returns the program's pid.
    pid_t getPid();

  private:
    pid_t m_sid;
    pid_t m_pid;
};
