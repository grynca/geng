#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "SAP.h"
#include "GameSystem.h"

namespace grynca {

    template <typename GameType>
    class CollisionSystem : public GameSystem<GameType> {
    public:
        using GameEntity = typename GameType::GameEntity;

        void update(GameEntity &e, float dt);

        void postUpdate();

        virtual RolesMask getNeededRoles() {
            return {GengEntityRoles::erCollidable, GengEntityRoles::erTransform };
        }
    private:
        SAPManager<VersionedIndex, 2> sap_;
    };
}
#include "CollisionSystem.inl"
#endif //COLLISIONSYSTEM_H
