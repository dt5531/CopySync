#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include "daemon.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    init_log();

    init_process();

    //----------------
    //Main Process
    //----------------
    while(true){
        process();    //Run our Process
        sleep(60);    //Sleep for 60 seconds
    }

    clean();

}
