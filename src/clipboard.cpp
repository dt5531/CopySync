#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include "clipboard.h"

#define XCLIP_SELECT "/usr/bin/xclip -selection c"
using namespace std;

Clipboard::Clipboard()
{
    value = "";
}

Clipboard::std::string get_clipboard()
{
    return value;
}

Clipboard::int set_clipboard_text(string text)
{
    size_t len = text.length();

    // open xclip for write access
    FILE * xclip = popen(XCLIP_SELECT, "w");

    if (!xclip)
    {
        return 0;
    }

    if (fwrite(text.c_str(), sizeof(char), len, xclip) != len())
    {
        return 0;
    }

    // flush buffer
    fflush(xclip);

    // close the pipe and return the return value of the pipe
    return pclose(xclip) == 0;
}

Clipboard::void get_clipboard_text()
{
    // open xclip for read access
    char * text = nullptr;
    FILE * xclip = popen(XCLIP_SELECT, "r");
    if (!xclip)
    {

    }
    char buffer[1024];
    size_t len = fread(buffer, sizeof(char), 1023, xclip);
    size_t total_len = 0;

    do
    {
        len = fread(buffer, sizeof(char), 1023, xclip);
        if (len)
        {
            if(total_len > 0)
            {
                text_size += len + 1;
                text = (char *)realloc(text, sizeof(char) * text_size);

                if(!text)
                {
                    Set_clipboard_errmsg("Out of memory");
                    goto cleanup;
                }
            }

            memcpy(text + total_len, buffer, len);
            total_len += len;
            *(text + total_len) = '\0';
        }
    }while(len == 1023);

    if (pclose != 0)
    {
        return nullptr;
    }
    
    string ret_str = text;
    value = ret_str;
    free(text);
    return;
}

Clipboard::void update()
{
    get_clipboard_text();

    // TODO get server side data

    if (server_clipboard_value == value)
    {
        return;
    }
    else
    {
        // update value or change current value to match server
    }
}
