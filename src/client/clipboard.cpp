#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "clipboard.h"

#define XCLIP_SELECT "/usr/bin/xclip -selection c"
using namespace std;

Clipboard::Clipboard()
{
  m_value = "";
}

string Clipboard::get_clipboard()
{
  return m_value;
}

int Clipboard::set_clipboard_text(string text)
{
  size_t len = text.length();

  // open xclip for write access
  FILE* xclip = popen(XCLIP_SELECT, "w");

  if (!xclip)
  {
    return 0;
  }

  if (fwrite(text.c_str(), sizeof(char), len, xclip) != len)
  {
    return 0;
  }

  // flush buffer
  fflush(xclip);

  // close the pipe and return the return m_value of the pipe
  return pclose(xclip) == 0;
}

void Clipboard::get_clipboard_text()
{
  // open xclip for read access
  string txt = "";
  FILE* xclip = popen(XCLIP_SELECT, "r");
  if (!xclip)
  {
    return;
  }
  char buffer[1024];
  size_t len = fread(buffer, sizeof(char), 1023, xclip);

  do
  {
    len = fread(buffer, sizeof(char), 1023, xclip);
    if (len)
    {
      txt += buffer;
    }
  } while (len == 1023);

  if (pclose(xclip) != 0)
  {
    return;
  }
  m_value = txt;

  return;
}

void Clipboard::update()
{
  get_clipboard_text();

  // TODO get server side data
  
  return;
}
