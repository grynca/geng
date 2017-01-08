#ifndef GEOMSTATE_H
#define GEOMSTATE_H

namespace grynca {

    class GeomState {
    public:
        enum StateType {
            stNone,
            stAnimation,
            stText,
            stParticles
        };

        enum UsageHint {
            uhStatic,       // set once use a lot
            uhDynamic,      // set a lot use a lot
            uhStream,        // set once use once


            uhCount
        };

        GeomState(StateType st, UsageHint bh) : id_(Index::Invalid()) {
            setType(st);
            setUsageHint(bh);
        }

        StateType getType()const {
            return StateType(GET_BITS(id_.getUnused(), 0, 8));
        }
        UsageHint getUsageHint()const {
            return UsageHint(GET_BITS(id_.getUnused(), 8, 8));
        }
        Index getIndex()const {
            return id_;
        }


        void setType(StateType st) {
            u16 pack = SET_BITS(id_.getUnused(), 0, 8, u16(st));
            id_.setUnused(pack);
        }
        void setUsageHint(UsageHint bh) {
            u16 pack = SET_BITS(id_.getUnused(), 8, 8, u8(bh));
            id_.setUnused(pack);
        }
        void setIndex(Index id) {
            u16 pack = id_.getUnused();
            id_ = id;
            id_.setUnused(pack);
        }

    private:
        Index id_;
    };



}

#endif //GEOMSTATE_H
