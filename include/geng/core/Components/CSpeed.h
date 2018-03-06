#ifndef CSPEED_H
#define CSPEED_H

#include "../GengEntity.h"
#include "gphyx/Speed.h"

namespace grynca {

    class CSpeedData : public Speed {
    public:
        static RolesMask componentRoles() {
            return GERoles::erSpeedMask();
        }

        enum SpeedFlagIds {
            fRotating,
            fMoving
        };

        CSpeedData();

        bool isZero()const;
        bool isRotating()const;
        bool isMoving()const;

        u8& accFlags();
        u8 getFlags()const;
    private:
        u8 flags_;
    };

    class CSpeedSetter : public EntityAccessor<CSpeedData> {
        typedef EntityAccessor<CSpeedData> Base;
    public:
        MOVE_ONLY(CSpeedSetter);

        CSpeedSetter();
        ~CSpeedSetter();

        Speed& accSpeed();
        void setSpeed(const Speed& spd);

        // is done automatically in destructor
        void forceUpdateFlags();
    private:
        void updateFlags_();

        bool dirty_;
    };
}

#include "CSpeed.inl"
#endif //CSPEED_H
