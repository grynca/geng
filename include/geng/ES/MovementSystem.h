#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

namespace grynca {

    template <typename GameType>
    class MovementSystem : public GengSystem<GameType> {
    public:
        virtual FlagsMask getTrackedFlags() override {
            return {};
        }

        virtual RolesMask getNeededRoles() override {
            return {GengEntityRoles::erMovable};
        }

        virtual void updateEntity(Entity& e, float dt) override {
            CMovable& m = e.getComponent<CMovable>();
            CTransform& t = e.getComponent<CTransform>();
            t.move(m.getSpeed().getLinearSpeed()*dt, e);
            t.rotate(m.getSpeed().getAngularSpeed()*dt, e);
        }
    };
}

#endif //MOVEMENTSYSTEM_H
