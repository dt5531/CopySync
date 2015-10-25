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

using namespace std;

int main(int argc, char *argv[]) 
{
    init_log();

    init_process();

    unique_ptr<Clipboard> clipbd = unique_ptr<Clipboard>(new Clipboard());

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
