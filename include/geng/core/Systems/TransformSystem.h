#ifndef TRANSFORMSYSTEM_H
#define TRANSFORMSYSTEM_H

namespace grynca {
    template <typename GameType>
    class TransformSystem : public GengSystem<GameType> {
    public:
        void init() {
            transformMask_ = SystemBase::calcFlagsMask({GengEntityFlags::fMoved, GengEntityFlags::fRotated, GengEntityFlags::fScaled});
        }

        virtual FlagsMask getTrackedFlags() override {
            return {GengEntityFlags::fMoved, GengEntityFlags::fRotated, GengEntityFlags::fScaled};
        }

        virtual RolesMask getNeededRoles() override {
            return {GengEntityRoles::erTransform};
        }

        virtual void updateEntity(Entity& e, float dt) override {
            if ((e.getFlagsMask()&transformMask_).any()) {
                CTransform& ct = e.getComponent<CTransform>();
                ct.accMatrix() = ct.get().calcMatrix();
            }
        }

    private:
        FlagsMaskLong transformMask_;
    };
}

#endif //TRANSFORMSYSTEM_H
