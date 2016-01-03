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

#include "clipboard.h"
#include "config.h"


class Daemon
{
  public:
    Daemon();
    void run();
    void process();
    void stop();
  private:
    std::unique_ptr<Config> m_configs;
    std::unique_ptr<Clipboard> m_clipbd;
    void init_log();
    void init_process();
    void clean();
};
