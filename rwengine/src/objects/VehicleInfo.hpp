#ifndef _RWENGINE_VEHICLEINFO_HPP_
#define _RWENGINE_VEHICLEINFO_HPP_

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

/**
 * @brief Stores data loaded from handling.cfg
 */
struct VehicleHandlingInfo {
    enum EngineType { Diesel = 'D', Petrol = 'P', Electric = 'E' };

    enum DriveType { Forward = 'F', Rear = 'R', All = '4' };

    float mass;
    glm::vec3 dimensions{};
    glm::vec3 centerOfMass{};
    float percentSubmerged;
    float tractionMulti;
    float tractionLoss;
    float tractionBias;
    size_t numGears;
    float maxVelocity;
    float acceleration;
    DriveType driveType;
    EngineType engineType;
    float brakeDeceleration;
    float brakeBias;
    bool ABS;
    float steeringLock;
    float suspensionForce;
    float suspensionDamping;
    float seatOffset;
    float damageMulti;
    size_t value;
    float suspensionUpperLimit;
    float suspensionLowerLimit;
    float suspensionBias;
    uint32_t flags;

    enum /*VehicleFlags*/ {
        VF_1G_BOOST = 1 << 0,
        VF_2G_BOOST = 2 << 0,
        VF_REV_BONNET = 4 << 0,
        VF_HANGING_BOOT = 8 << 0,
        VF_NO_DOORS = 1 << 8,
        VF_IS_VAN = 2 << 8,
        VF_IS_BUS = 4 << 8,
        VF_IS_LOW = 8 << 8,
        VF_DBL_EXHAUST = 1 << 16,
        VF_TAILGATE_BOOT = 2 << 16,
        VF_NOSWING_BOOT = 4 << 16,
        VF_NONPLAYER_STABILIZER = 8 << 16,
        VF_NEUTRALHANDLING = 1 << 16,
        VF_HAS_NO_ROOF = 2 << 16,
        VF_IS_BIG = 4 << 16,
        VF_HALOGEN_LIGHTS = 8 << 16
    };
};

struct WheelInfo {
    glm::vec3 position{};
};

struct SeatInfo {
    glm::vec3 offset{};
};

/**
 * @brief Vehicle Handling and runtime-derrived information about wheel and seat
 * positions.
 */
struct VehicleInfo {
    /** Handling data */
    VehicleHandlingInfo handling;

    /** Value for caching wheel information */
    std::vector<WheelInfo> wheels;
    /** Struct for caching seat information */
    struct Seats{
        std::vector<SeatInfo> front;
        std::vector<SeatInfo> back;

        SeatInfo operator[](size_t index) const {
            // Try front seats first
            if (index < front.size()) {
                return front[index];
            }
            index -= front.size();

            // Get back seat
            return back[index];
        }
        size_t size() const {
            return front.size() + back.size();
        }
        bool empty() const {
            return front.empty() && back.empty();
        }
    };
    Seats seats;

    template <typename T1, typename T2>
    VehicleInfo(VehicleHandlingInfo p_handling, T1&& p_wheels, T2&& p_seats)
        : handling(p_handling)
        , wheels(std::forward<T1>(p_wheels))
        , seats(std::forward<T2>(p_seats)) {
    }
};

#endif
