#include "CSpeed.h"

namespace grynca {

    inline CSpeedData::CSpeedData()
     : flags_(0)
    {}

    inline bool CSpeedData::isZero()const {
        return flags_ == 0;
    }

    inline bool CSpeedData::isRotating()const {
        return GET_BIT(flags_, fRotating);
    }

    inline bool CSpeedData::isMoving()const {
        return GET_BIT(flags_, fMoving);
    }

    inline u8& CSpeedData::accFlags() {
        return flags_;
    }

    inline u8 CSpeedData::getFlags()const {
        return flags_;
    }

    inline CSpeedSetter::CSpeedSetter()
      : dirty_(false)
    {}

    inline CSpeedSetter::~CSpeedSetter() {
        if (dirty_) {
            updateFlags_();
        }
    }

    inline Speed& CSpeedSetter::accSpeed() {
        dirty_ = true;
        return *getData<CSpeedData>();
    }

    inline void CSpeedSetter::setSpeed(const Speed& spd) {
        dirty_ = true;
        *(Speed*)(getData<CSpeedData>()) = spd;
    }

    inline void CSpeedSetter::forceUpdateFlags() {
        updateFlags_();
        dirty_ = false;
    }

    inline void CSpeedSetter::updateFlags_() {
        CSpeedData* data = getData<CSpeedData>();
        bool rotating =!data->getAngularSpeed().isZero();
        bool moving = !data->getLinearSpeed().isZero();

        data->accFlags() = SET_BITV(data->getFlags(), CSpeedData::fRotating, rotating);
        data->accFlags() = SET_BITV(data->getFlags(), CSpeedData::fMoving, moving);
    }
}