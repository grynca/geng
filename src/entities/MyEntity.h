#ifndef MYENTITY_H
#define MYENTITY_H

//class CCustom {
//public:
//    u32 fieldA;
//    u16 fieldB;
//    f32 fieldC;
//};

class MyEntity : public GengEntityDef<CMovable, CTransform, CRenderables, CNetworked> {
public:
    class Resources : public Singleton<Resources> {
    public:
        Resources(GameBase& game);

        TextureRegion sprite_region;
        Index animation_id;
    };

    static void init(Entity& ent, GameBase& game);
    static void update(Entity& e, GameBase& game);

//    virtual void getFields(Fields& f)const {
//        ADD_FIELD(MyEntity, fieldA);
//        ADD_FIELD(MyEntity, fieldB);
//        ADD_FIELD(MyEntity, fieldC);
//    }
};


#include "MyEntity.inl"
#endif //MYENTITY_H
