#pragma once

namespace cl
{
    class sphere
    {
        private:
            unsigned int m_glID;

        public:
            sphere();
            sphere(const sphere& s);
            ~sphere();
    };
}