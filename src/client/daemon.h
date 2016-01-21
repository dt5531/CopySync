#pragma once

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "clipboard.h"
#include "config.h"


class Daemon
{
  public:
    Daemon();
    // This function takes no argument and return nothing.
    // This function runs the daemon.
    void run();
    // This function takes no argument and return nothing.
    // This function updates the current clipboard data
    void process();
    // This function takes no argument and return nothing.
    // This function does graceful exit for the daemon.
    void stop();
  private:
    std::unique_ptr<Config> m_configs;
    std::unique_ptr<Clipboard> m_clipbd;
    void init_log();
    void init_process();
    void clean();
};
