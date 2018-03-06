#include "Dude.h"

inline void Dude::Resources::initSingleton(GameBase& game) {

    fast_vector<BodyParsBase*> common_pars{&chest_params, &head_params};
    for (u32 i=0; i<ltCount; ++i) {
        common_pars.push_back(&limb_params[i]);
    }

    for (u32 i=0; i<common_pars.size(); ++i) {
        common_pars[i]->material = Material::Pillow();
        common_pars[i]->collision_group = MyCollGroups::cgDudeLimbId;
        common_pars[i]->collides_with.set();
        common_pars[i]->collides_with.reset(MyCollGroups::cgDudeLimbId);
    }

    chest_params.size = {10, 30};
    chest_params.color = Colorf::Green();
    chest_params.layer_id = 5;chest_params.noffset_type = NormOffset::otCenter;

    head_params.radius = 10;
    head_params.color = Colorf::SkinLight();
    head_params.layer_id = 6;
    head_params.position = {0, -chest_params.size.getY()*0.5f};

    limb_params[ltLarm].size = {6, 25};
    limb_params[ltLarm].color = Colorf::SkinLight();
    limb_params[ltLarm].layer_id = 4;
    limb_params[ltLarm].noffset_type = NormOffset::otTopCenter;
    limb_params[ltLarm].position = {-(chest_params.size.getX()+ limb_params[ltLarm].size.getX())*0.5f,
                            -chest_params.size.getY()*0.4f};
    limb_params[ltLarm].rotation = Angle::Pi_4+Angle::Pi_2;

    limb_params[ltRarm].size = {6, 25};
    limb_params[ltRarm].color = Colorf::SkinLight();
    limb_params[ltRarm].layer_id = 4;
    limb_params[ltRarm].noffset_type = NormOffset::otTopCenter;
    limb_params[ltRarm].position = {(chest_params.size.getX() + limb_params[ltRarm].size.getX())*0.5f,
                                    -chest_params.size.getY()*0.4f};
    limb_params[ltRarm].rotation = -(Angle::Pi_4+Angle::Pi_2);

    limb_params[ltLleg].size = {6, 30};
    limb_params[ltLleg].color = Colorf::Brown();
    limb_params[ltLleg].layer_id = 4;
    limb_params[ltLleg].noffset_type = NormOffset::otTopCenter;
    limb_params[ltLleg].position = {-limb_params[ltLleg].size.getX()*0.5f, chest_params.size.getY()*0.45f};
    limb_params[ltLleg].rotation = Angle::Pi_4;

    limb_params[ltRleg].size = {6, 30};
    limb_params[ltRleg].color = Colorf::Brown();
    limb_params[ltRleg].layer_id = 4;
    limb_params[ltRleg].noffset_type = NormOffset::otTopCenter;
    limb_params[ltRleg].position = {limb_params[ltRleg].size.getX()*0.5f, chest_params.size.getY()*0.45f};
    limb_params[ltRleg].rotation = -Angle::Pi_4;

    dout("Dude coll.gr: " << chest_params.collision_group << std::endl);
    dout("     coll.with: " << chest_params.collides_with << std::endl);
}


inline void Dude::init(const Vec2& pos) {
    static Resources &res = Resources::get();
    static Game& game = Game::get();

    Dude& chest = *this;
    {
        chest.initDynamicRectBody1(res.chest_params);
        chest.get<CTransformSetter>().setPosition(pos);
    }

    EBody head = game.createEntity<EBody>();
    {
        head.initDynamicCircleBody(res.head_params);
        Vec2 head_pos = pos + res.head_params.position;
        head.get<CTransformSetter>().setPosition(head_pos);
        head.get<CTreeJoint>().init<RevoluteJoint>(chest, head_pos);
    }

    auto limbs = game.createEntities<EBodyTree, Resources::ltCount>();
    for (u32 i=0; i<Resources::ltCount; ++i) {
        limbs[i].initDynamicRectBody1(res.limb_params[i]);

        Transform limb_tr = (*chest.getData<CTransformData>())
                            * Transform(res.limb_params[i].position, res.limb_params[i].rotation);

        limbs[i].get<CTransformSetter>().setTransform(limb_tr);
        limbs[i].get<CTreeJoint>().init<RevoluteJoint>(chest, limb_tr.getPosition());
        limbs[i].get<CSpeedSetter>().accSpeed().setAngularSpeed(0.5f*randSign());
    }
}

inline void Dude::update() {
    Resources &res = Resources::get();
    static Game& game = Game::get();

    Transform dude_tr = *getData<CTransformData>();
    CTreeJoint tree = get<CTreeJoint>();

    for (u32 i=0; i<Resources::ltCount; ++i) {
        Angle rot_min = res.limb_params[i].rotation - Angle::Pi_4;
        Angle rot_max = res.limb_params[i].rotation + Angle::Pi_4;

        Entity limb = tree.getChild(1+i);
        f32 ang_vel = limb.getData<CSpeedData>()->getAngularSpeed();
        CBodyData* cbody = limb.getData<CBodyData>();
        Transform limb_local_tr = *limb.getData<CTransformData>() - dude_tr;
        Angle limb_rot = limb_local_tr.getRotation();
        if (minAngleDiff(limb_rot, rot_min) < 0 && ang_vel < 0.0f) {
            cbody->applyTorque(-sgn(ang_vel)*500*game.getTargetTicklen());
        }
        else if (minAngleDiff(rot_max,limb_rot) < 0 && ang_vel > 0.0f) {
            cbody->applyTorque(-sgn(ang_vel)*500*game.getTargetTicklen());
        }
        else {
            cbody->applyTorque(sgn(ang_vel)*20*game.getTargetTicklen());
        }

    }
}

inline void Dude::onKilled() {
//    Resources &res = Resources::get();
}