#pragma once
#include <string>

enum cursor_mode
{
    CL_CURSOR_ENABLED,
    CL_CURSOR_DISABLED
};

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
        void disable_cursor(bool val);
        inline void* get_handle() { return m_win_handle; }
        inline int get_width() { return m_width; }
        inline int get_height() { return m_height; }
        
    };
}