#pragma once
#include <string>

namespace cl
{
    class window
    {
    private:

        void* m_win_handle;

        const std::string m_title = "default";
        int m_width, m_height = 0;

        bool m_is_open = false;


    public:
        window(int width, int height, const std::string& title);

        ~window();

        inline bool is_open() { return m_is_open; }
        bool should_close();
        void swap_buffers();
        inline void* get_handle() { return m_win_handle; }
    };
}