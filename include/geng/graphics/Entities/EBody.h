#ifndef EBODY_H
#define EBODY_H

namespace grynca {

    struct BodyParsBase {
        u16 layer_id;
        Material material;
        u32 collision_group;
        CollisionGroupsMask collides_with;
    };

    struct RectBodyPars : BodyParsBase {
        Vec2 size;
        Colorf color;
    };

    struct RectBodyPars1 : RectBodyPars {
        NormOffset::Type noffset_type;      // uses static unit quad geom for norm.offset type
    };

    struct RectBodyPars2 : RectBodyPars {
        VertexData::IRefPtr geom_ptr;       // uses shared geom
    };

    struct CircleBodyPars : BodyParsBase {
        Colorf color;
        f32 radius;
    };

    struct SpriteBodyPars : BodyParsBase {
        Vec2 size;
        Renderer2D::IPtr sprite_prototype;
    };


    template <typename... AdditionalCompTypes>
    class EBodyT : public GengEntityDef<CTransformData, CSpeedData, CColliderData, CBodyData, CTreeJointData, CRenderableData, AdditionalCompTypes...> {
        typedef GengEntityDef<CTransformData, CSpeedData, CColliderData, CBodyData, CTreeJointData, CRenderableData, AdditionalCompTypes...> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EBodyT);

        void initDynamicRectBody1(const RectBodyPars1& pars);
        void initDynamicRectBody2(const RectBodyPars2& pars);
        void initDynamicCircleBody(const CircleBodyPars& pars);
        void initStaticCircleBody(const CircleBodyPars& pars);        // sets mass 0.0f
        void initDynamicSpriteBody(const SpriteBodyPars& pars);

        // lookahead - how many ticks ahead we are predicting
        // applies force to the center of body
        void moveTo(const Vec2& target_pos, u32 lookahead = 20);        // uses whatever force neccessary
        void moveToLimitF(const Vec2& target_pos, f32 max_force_sqr, u32 lookahead = 20);
        void rotateTo(Angle target_rot, u32 lookahead = 20);            // uses whatever torque neccessary
        void rotateToLimitT(Angle target_rot, f32 max_torque, u32 lookahead = 20);
    private:
        void initCircleBodyInner_(const CircleBodyPars& pars);
        template <typename RendT, typename ParsT>
        void initRectBodyInner_(RendT* rend, const ParsT& pars);
    };

    class EBody : public EBodyT<> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EBody);
    };

    template <typename... AdditionalCompTypes>
    class EBodyTreeT : public EBodyT<CTreeTransformData, AdditionalCompTypes...> {
        typedef EBodyT<CTreeTransformData, AdditionalCompTypes...> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EBodyTreeT);
    };

    class EBodyTree : public EBodyTreeT<> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EBodyTree);
    };
}

#include "EBody.inl"
#endif //EBODY_H
