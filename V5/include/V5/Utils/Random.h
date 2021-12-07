#pragma once

#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace V5Utils
{
    class Random
    {
    public:
        // Returns a random real in [0,1).

        static float RandomFloat() {
            return rand() / (RAND_MAX + 1.0f);
        }

        // Returns a random real in [min,max).

        static float RandomFloat(float min, float max) {
            return min + (max - min) * RandomFloat();
        }

        static glm::vec3 RandomVector01()
        {
            return glm::vec3(RandomFloat(), RandomFloat(), RandomFloat());
        }

        static glm::vec3 RandomVector(float min, float max)
        {
            return glm::vec3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
        }

        static glm::vec3 RandomInUnitySphere() {

            while (true) {
                auto p = RandomVector(-1, 1);
                auto length = glm::length(p);
                if (length * length >= 1)
                {
                    continue;
                }
                return p;
            }
        }

        static glm::vec3 RandomInHemisphere(const glm::vec3& normal) {
            glm::vec3 in_unit_sphere = RandomInUnitySphere();
            if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
                return in_unit_sphere;
            else
                return -in_unit_sphere;
        }

        static glm::vec3 RandomUnitVec()
        {
            return glm::normalize(RandomInUnitySphere());
        }

        static glm::vec3 RandomInUnitDisc() {
            while (true) {
                auto p = glm::vec3(RandomFloat(-1, 1), RandomFloat(-1, 1), 0);
                if (glm::length2(p) >= 1) continue;
                return p;
            }
        }
    };

}

