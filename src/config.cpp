#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include "config.h"


Config::Config()
{
    sid = 0;
    pid = 0;
}

void Config::setSid(pid_t _sid)
{
    sid = _sid;
}

void Config::setPid(pid_t _pid)
{
    pid = _pid;
}

pid_t Config::getSid()
{
    return _sid;
}

pid_t Config::getPid()
{
    return _pid;
}
