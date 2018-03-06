#ifndef EVISUAL_H
#define EVISUAL_H

namespace grynca {

    template <typename... AdditionalCompTypes>
    class EVisualT : public GengEntityDef<CTransformData, CRenderableData, AdditionalCompTypes...> {
        typedef GengEntityDef<CTransformData, CRenderableData, AdditionalCompTypes...> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EVisualT);
    };

    class EVisual : public EVisualT<> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EVisual);
    };

    template <typename... AdditionalCompTypes>
    class EVisualDynamicT : public EVisualT<CSpeedData, AdditionalCompTypes...> {
        typedef EVisualT<CSpeedData, AdditionalCompTypes...> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EVisualDynamicT);
    };

    class EVisualDynamic : public EVisualDynamicT<> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EVisualDynamic);
    };

    template <typename... AdditionalCompTypes>
    class EVisualTreeT : public EVisualT<CTreeTransformData, AdditionalCompTypes...> {
        typedef EVisualT<CTreeTransformData, AdditionalCompTypes...> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EVisualTreeT);
    };

    class EVisualTree : public EVisualTreeT<> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(EVisualTree);
    };
}

#endif //EVISUAL_H
