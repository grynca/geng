#include "PhysicsManager.h"
#include "Components/CBody.h"
#include "../core/Components/CSpeed.h"
#include "../core/Components/CTransform.h"

namespace grynca {

    inline BodiesPairHandler::BodiesPairHandler()
     : emgr_(NULL)
    {}

    inline void BodiesPairHandler::init(EntityManager& emgr) {
        emgr_ = &emgr;
    }


    inline void BodiesPairHandler::setBodyA(EntityIndex ent_id) {
        Base::setBodyA(ent_id.accInnerIndex());
        e1_ = emgr_->getEntity<ETrigger>(ent_id);
    }

    inline void BodiesPairHandler::setBodyB(EntityIndex ent_id) {
        Base::setBodyB(ent_id.accInnerIndex());
        e2_ = emgr_->getEntity<ETrigger>(ent_id);
    }

    inline void BodiesPairHandler::swapOrder() {
        Base::swapOrder();
        std::swap(e1_, e2_);
    }

    inline Body& BodiesPairHandler::accBodyA() {
        return *e1_.getEntity().getData<CBodyData>();
    }

    inline Speed& BodiesPairHandler::accSpeedA() {
        return *e1_.getEntity().getData<CSpeedData>();
    }

    inline Transform& BodiesPairHandler::accTransformA() {
        return *e1_.getData<CTransformData>();
    }

    inline Collider& BodiesPairHandler::accColliderA() {
        return *e1_.getData<CColliderData>();
    }

    inline Body& BodiesPairHandler::accBodyB() {
        return *e2_.getEntity().getData<CBodyData>();
    }

    inline Speed& BodiesPairHandler::accSpeedB() {
        return *e2_.getEntity().getData<CSpeedData>();
    }

    inline Transform& BodiesPairHandler::accTransformB() {
        return *e2_.getData<CTransformData>();
    }

    inline Collider& BodiesPairHandler::accColliderB() {
        return *e2_.getData<CColliderData>();
    }

    inline EntityManager& BodiesPairHandler::accEntitiesManager() {
        return *emgr_;
    }

    inline ETrigger& BodiesPairHandler::accEntityA() {
        return e1_;
    }

    inline ETrigger& BodiesPairHandler::accEntityB() {
        return e2_;
    }

    template <typename EntAccT>
    inline EntAccT BodiesPairHandler::accEntityA() {
        return e1_.get<EntAccT>();
    }

    template <typename EntAccT>
    inline EntAccT BodiesPairHandler::accEntityB() {
        return e2_.get<EntAccT>();
    }

    inline void PhysicsManager::init(GameBase& game) {
        game_ = &game;
        setUPS(game.getTargetUPS());
        bph_.init(game.accEntitiesManager());
    }

    inline const GameBase& PhysicsManager::getGame()const {
        return *game_;
    }

    inline GameBase& PhysicsManager::accGame() {
        return *game_;
    }
}