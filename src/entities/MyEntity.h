#ifndef MYENTITY_H
#define MYENTITY_H

//class CCustom {
//public:
//    u32 fieldA;
//    u16 fieldB;
//    f32 fieldC;
//};

//class MyEntity : public GengEntityDef<CSpeedData, CTransformData, CRenderableData, CNetworkedServerData> {
//    typedef GengEntityDef<CSpeedData, CTransformData, CRenderableData, CNetworkedServerData> Base;
//public:
//    enum {
//        pAnimSprite,
//        pPolygon,
//        pCircle,
//
//        partsCount
//    };
//
//    class Resources : public EntityResources<Resources> {
//    public:
//        void init(GameBase& game);
//
//        TextureRegion sprite_region;
//        SpriteAnimations::IPtr animation;
//    };
//
//    MyEntity(Entity& e) : Base(e) {}
//    void init();
//    void update();
//
////    virtual void getFields(Fields& f)const {
////        ADD_FIELD(MyEntity, fieldA);
////        ADD_FIELD(MyEntity, fieldB);
////        ADD_FIELD(MyEntity, fieldC);
////    }
//};


#include "MyEntity.inl"
#endif //MYENTITY_H
