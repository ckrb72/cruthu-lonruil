#pragma once
#include "../cltypes.h"

namespace cl
{
    class physicsEngine
    {
        private:


        public:
            physicsEngine();
            physicsEngine(const physicsEngine& p);
            ~physicsEngine();

            bool init();

            uint32_t addRigidBody();
    };
}