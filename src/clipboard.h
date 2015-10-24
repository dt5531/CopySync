#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory>

#define xclip_select "/usr/bin/xclip -selection c"

int set_clipboard_text(string text)
{
    size_t len = text.length();

    // open xclip for write access
    FILE * xclip = popen(xclip_select, "w");

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

string get_clipboard_text()
{
    // open xclip for read access
    char * text = nullptr;
    FILE * xclip = popen(xclip_select, "r");
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
    free(text);
    return ret_str;
}
