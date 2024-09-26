#pragma once
#include "../types.h"

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

            uint32 addRigidBody();
    };
}