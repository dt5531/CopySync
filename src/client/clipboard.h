#pragma once
#include <string>


class clipboard
{
  public:
    Clipboard();
    std::string get_clipboard();
    void update();
  private:
    void get_clipboard_text();
    int set_clipboard_text(std::string text);
    std::string m_value;
}
