#pragma once
#include <string>


class Window
{
private:

    void* m_win_handle;

    const std::string m_title = "default";
    int m_width, m_height = 0;

    bool m_is_open = false;


public:
    Window(int width, int height, const std::string& title);

    ~Window();

    bool is_open() { return m_is_open; }

    bool should_close();

    void swap_buffers();
};