#ifndef MYENTITY_H
#define MYENTITY_H

//class CCustom {
//public:
//    uint32_t fieldA;
//    uint16_t fieldB;
//    float fieldC;
//};

class MyEntity : public GengEntityDef<CMovable, CTransform, CRenderables, CNetworked> {
public:
    static void initResources(MyGame& game);
    static Entity create(MyGame& game);

    static void update(Entity& e);

//    virtual void getFields(Fields& f)const {
//        ADD_FIELD(MyEntity, fieldA);
//        ADD_FIELD(MyEntity, fieldB);
//        ADD_FIELD(MyEntity, fieldC);
//    }

private:
    static TextureRegion sprite_region;
    static Index animation_id;
};

#endif //MYENTITY_H
