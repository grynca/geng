#ifndef BODIESPAIRHANDLER_H
#define BODIESPAIRHANDLER_H

#include "Entities/ETrigger.h"

namespace grynca {

    // fw
    class EntityManager;

    class BodiesPairHandler : public BodiesPairHandlerBase {
        typedef BodiesPairHandlerBase Base;
    public:
        BodiesPairHandler();
        void init(EntityManager& emgr);

        // overriden from Base
        void setBodyA(EntityIndex ent_id);
        void setBodyB(EntityIndex ent_id);
        void swapOrder();

        Body& accBodyA();
        Speed& accSpeedA();
        Transform& accTransformA();
        Collider& accColliderA();

        Body& accBodyB();
        Speed& accSpeedB();
        Transform& accTransformB();
        Collider& accColliderB();

        EntityManager& accEntitiesManager();
        ETrigger& accEntityA();
        ETrigger& accEntityB();
        template <typename EntAccT>
        EntAccT accEntityA();
        template <typename EntAccT>
        EntAccT accEntityB();
    private:
        EntityManager* emgr_;
        ETrigger e1_, e2_;
    };

    class PhysicsManager : public PhysicsManagerT<PhysicsManager, BodiesPairHandler> {
    public:
        void init(GameBase& game);

        const GameBase& getGame()const;
        GameBase& accGame();
    private:
        GameBase* game_;
    };
}

#include "PhysicsManager.inl"
#endif //PHYSICSMANAGER_H
