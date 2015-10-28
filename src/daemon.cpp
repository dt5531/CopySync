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

int main(int argc, char *argv[]) 
{
    unique_ptr<Config> configs = unique_ptr<Config>(new Config());

    unique_ptr<Clipboard> clipbd = unique_ptr<Clipboard>(new Clipboard());

    init_log();

    init_process(configs.get());


    //TODO Start network

    //----------------
    //Main Process
    //----------------
    while(true)
    {
        process(clipbd.get());           //Run our Process
        sleep(1);                   //Update once every second
    }

    clean();

}
