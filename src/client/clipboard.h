#pragma once
#include <string>


class Clipboard
{
  public:
    Clipboard();
    // This function takes no argument and return the current clipboard string
    std::string get_clipboard();
    // This function takes no arugment and return nothing
    // This function updates the clipboard and replace it with newest data
    void update();
  private:
    void get_clipboard_text();
    int set_clipboard_text(std::string text);
    std::string m_value;
};
