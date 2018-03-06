#include "EBody.h"
#define EB_TPL template <typename... ACs>
#define EB_TYPE EBodyT<ACs...>

namespace grynca {

    EB_TPL
    inline void EB_TYPE::initDynamicRectBody1(const RectBodyPars1& pars) {
        CRenderable rend = this->template get<CRenderable>();
        RectRenderable* r = rend.initR<RectRenderable>();
        r->setColor(pars.color);
        r->setStaticSharedQuadGeom(pars.noffset_type);
        initRectBodyInner_(r, pars);
    }

    EB_TPL
    inline void EB_TYPE::initDynamicRectBody2(const RectBodyPars2& pars) {
        CRenderable rend = this->template get<CRenderable>();
        RectRenderable* r = rend.initR<RectRenderable>();
        r->setColor(pars.color);
        r->setGeom(*pars.geom_ptr);
        initRectBodyInner_(r, pars);
    }

    EB_TPL
    inline void EB_TYPE::initDynamicCircleBody(const CircleBodyPars& pars) {
        initCircleBodyInner_(pars);
        // set physical body
        CBodyCalcFromShape body = this->template get<CBodyCalcFromShape>();
        body.init(pars.material);
    }

    EB_TPL
    inline void EB_TYPE::initStaticCircleBody(const CircleBodyPars& pars) {
        initCircleBodyInner_(pars);
        // set physical body
        CBodyData* cbd = this->template getData<CBodyData>();
        cbd->initStatic(pars.material);
    }

    EB_TPL
    inline void EB_TYPE::initDynamicSpriteBody(const SpriteBodyPars& pars) {
        CRenderable rend = this->template get<CRenderable>();
        SpriteRenderable* r = rend.initRCloned<SpriteRenderable>(pars.sprite_prototype);
        initRectBodyInner_(r, pars);
    }

    EB_TPL
    inline void EB_TYPE::moveTo(const Vec2& target_pos, u32 lookahead) {
        GameBase& game = GameBase::get();
        CBodyData* cbody = this->template getData<CBodyData>();
        const Vec2& curr_pos = this->template getData<CTransformData>()->getPosition();
        const Vec2& lin_vel = this->template getData<CSpeedData>()->getLinearSpeed();
        f32 mass = cbody->getMassData().mass;
        Vec2 force = gphyx::calcMovementForce(target_pos, curr_pos, lin_vel, mass,
                                              game.getTargetUPS(), game.getTargetTicklen(), lookahead);
        cbody->applyForceAtCenter(force);
    }

    EB_TPL
    inline void EB_TYPE::moveToLimitF(const Vec2& target_pos, f32 max_force_sqr, u32 lookahead) {
        GameBase& game = GameBase::get();
        CBodyData* cbody = this->template getData<CBodyData>();
        const Vec2& curr_pos = this->template getData<CTransformData>()->getPosition();
        const Vec2& lin_vel = this->template getData<CSpeedData>()->getLinearSpeed();
        f32 mass = cbody->getMassData().mass;
        Vec2 force = gphyx::calcMovementForce(target_pos, curr_pos, lin_vel, mass,
                                              game.getTargetUPS(), game.getTargetTicklen(), lookahead);
        f32 fsqr_len = force.getSqrLen();
        if (fsqr_len > max_force_sqr) {
            force *= sqrtf(max_force_sqr)/sqrtf(fsqr_len);
        }
        cbody->applyForceAtCenter(force);
    }

    EB_TPL
    inline void EB_TYPE::rotateTo(Angle target_rot, u32 lookahead) {
        GameBase& game = GameBase::get();
        CBodyData* cbody = this->template getData<CBodyData>();
        Angle curr_rot = this->template getData<CTransformData>()->getRotation();
        f32 ang_vel = this->template getData<CSpeedData>()->getAngularSpeed();
        f32 inertia = cbody->getMassData().inertia;
        f32 torque = gphyx::calcRotationTorque(target_rot, curr_rot, ang_vel, inertia,
                                               game.getTargetUPS(), game.getTargetTicklen(), lookahead);
        cbody->applyTorque(torque);
    }

    EB_TPL
    inline void EB_TYPE::rotateToLimitT(Angle target_rot, f32 max_torque, u32 lookahead) {
        GameBase& game = GameBase::get();
        CBodyData* cbody = this->template getData<CBodyData>();
        Angle curr_rot = this->template getData<CTransformData>()->getRotation();
        f32 ang_vel = this->template getData<CSpeedData>()->getAngularSpeed();
        f32 inertia = cbody->getMassData().inertia;
        f32 torque = gphyx::calcRotationTorque(target_rot, curr_rot, ang_vel, inertia,
                                               game.getTargetUPS(), game.getTargetTicklen(), lookahead);
        cbody->applyTorque(std::min(max_torque, torque));
    }

    EB_TPL
    inline void EB_TYPE::initCircleBodyInner_(const CircleBodyPars& pars) {
        CRenderable rend = this->template get<CRenderable>();

        CircleRenderable* r = rend.initR<CircleRenderable>();
        r->setStaticSharedGeom();
        r->setLayer(pars.layer_id);
        r->setColor(pars.color);
        r->setOuterRadius(pars.radius);

        // set collision shape
        CColliderSetter colls = this->template get<CColliderSetter>();
        colls.accShape().create<Circle>(Vec2{0, 0}, pars.radius);
        // calc bound
        colls.calcTightBound();
        colls.getData<CColliderData>()->setCollisionGroup(pars.collision_group);
        colls.getData<CColliderData>()->setCollidesWithMask(pars.collides_with);
    }

    EB_TPL
    template <typename RendT, typename ParsT>
    inline void EB_TYPE::initRectBodyInner_(RendT* rend, const ParsT& pars) {
        rend->setLayer(pars.layer_id);
        rend->setSize(pars.size);

        // set collision shape
        CColliderSetter colls = this->template get<CColliderSetter>();
        colls.accShape().create<ARect>(rend->getOffset(), rend->getSize());
        colls.calcRotationInvariantBound();
        colls.getData<CColliderData>()->setCollisionGroup(pars.collision_group);
        colls.getData<CColliderData>()->setCollidesWithMask(pars.collides_with);
        // set physical body
        CBodyCalcFromShape body = this->template get<CBodyCalcFromShape>();
        body.init(pars.material);
    }

}

#undef EB_TPL
#undef EB_TYPE