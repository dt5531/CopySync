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

using namespace std;

void process(Clipboard * clipbd)
{

    syslog (LOG_NOTICE, "Writing to my Syslog");
    // TODO get server clipboard
    clipbd -> update();
}   

void init_log()
{
    //Set our Logging Mask and open the Log

    setlogmask(LOG_UPTO(LOG_NOTICE));

    openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);

    syslog(LOG_INFO, "Daemon starting");
}

void init_process()
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
        exit(EXIT_SUCCESS); 
    }

    //Change File Mask

    umask(027);

    // change directory for logging

    if (chdir("/home/david/work/daemon/CopySync/log") < 0)
    {
        exit(EXIT_FAILURE);
    }

    // Create a new Signature Id for our child

    sid = setsid();
    if (sid < 0) 
    { 
        exit(EXIT_FAILURE); 
    }


    //Close Standard File Descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void clean()
{
    closelog ();
    exit(EXIT_SUCCESS);
}
