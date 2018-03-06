#include "MyGame.h"

class DummyActionState {
public:
    void update(f32 dt) {

    }

    void clear() {

    }

    static void getFields(Fields& f) {
        ADD_FIELD(DummyActionState, a);
        ADD_FIELD(DummyActionState, b);
        ADD_FIELD(DummyActionState, c);
    }

    int a;
    f32 b;
    char c;
};


inline void MyGame::init() {
#ifndef WEB
    accWindow().setVSync(false);
#endif
    accModule<Server>().init(16, 0);

    initAssets();

    initEntityTypes<EntityTypes>();


//    std::cout << entity_manager_.getTypesDebugString();
//
//    u32 dude_comps_cnt = Dude::ComponentDataTypes::getTypesCount();
//    u16 dude_tid = Dude::typeId();
//
//    u32 btree_comps_cnt = EBodyTree::ComponentDataTypes::getTypesCount();
//    u16 btree_tid = EBodyTree::typeId();

    // update systems
    addUpdateSystem<MovementSystem>();
    addUpdateSystem<TreeTransformSystem>();
    addUpdateSystem<BoundsSystem>();
    addUpdateSystem<PhysicsSystem>();

    // TODO: v initu nejak getnout z GameBase()
//    Fields client_state_fields;
//    DummyActionState::getFields(client_state_fields);
//    addUpdateSystem<ServerNetworkSystem<MyGame> >().init(client_state_fields);

    // render systems
    addRenderSystem<BoundsDebugRenderSystem>();
    addRenderSystem<RenderSystem>();

    shuttle_id = createAndInitEntity<Shuttle>().getEntity().getIndex();
    //test_ent_id = createAndInitEntity<MyEntity>().getEntity().getIndex();
    //hud_id = createAndInitEntity<HUD>().getEntity().getIndex();
    dude_id = createAndInitEntity<Dude>(Vec2{-200, -200}).getEntity().getIndex();

//    shuttle2_id = createAndInitEntity<Shuttle>([](Entity& e, MyGame& g){
//        Shuttle::init(e, g);
//        e.getComponent<CTransformData>().setPosition({-100, -100}, e);
//        Speed& spd = e.getComponent<CMovableData>().getSpeed();
//        spd.setAngularSpeed(Angle::Pi/4);
//    }).getIndex();
//
//    Entity ch1 = createAndInitEntity<GUIElement<MyGame> >([](Entity& e, MyGame& g) {
//        GUIElement<MyGame>::setBackgroundRect(e, {50, 50}, 12, Colorf::Green());
//    });

//    Entity ch2 = createAndInitEntity<GUIElement<MyGame> >([](Entity& e, MyGame& g) {
//        GUIElement<MyGame>::setBackgroundRect(e, {50, 50}, 12, Colorf::Blue());
//    });
//
//    gui_root_id = createAndInitEntity<GUIElement<MyGame> >([&ch1, &ch2](Entity& e, MyGame& g) {
//        CTransformData& ct = e.getComponent<CTransformData>();
//        ct.setPosition({50, 50}, e);
//        GUIElement<MyGame>::setBackgroundRect(e, {200, 200}, 11, Colorf::Red());
//        GUIElement<MyGame>::addChild(e, ch1, {100, 0});
//        GUIElement<MyGame>::addChild(e, ch2, {0, 100});
//    }).getIndex();

//    gui_ch1_id = ch1.getIndex();
//    gui_ch2_id = ch2.getIndex();
}

inline void MyGame::update() {
    auto& em = getEntitiesManager();
    Entity e;
    if (em.tryGetEntity(shuttle_id, e)) e.get<Shuttle>().update();
    //if (em.tryGetEntity(test_ent_id, e)) e.get<MyEntity>().update();
    if (em.tryGetEntity(hud_id, e)) e.get<HUD>().update();
//    if (em.tryGetEntity(gui_root_id, e)) e.callOnEntity([this](Entity& ee) {
//        ee.get<CTransform>().move(Vec2(10, 0)*getTargetTicklen());
//    });
    if (em.tryGetEntity(dude_id, e)) e.get<Dude>().update();

    Events& events = getModule<Window>().getEvents();
    bool alt_down = events.isKeyDown(SDL_SCANCODE_LALT)|events.isKeyDown(SDL_SCANCODE_RALT);
    if (events.wasKeyPressed(SDL_SCANCODE_F4) && alt_down)
        quit();
    else if (events.wasKeyPressed(SDL_SCANCODE_RETURN) && alt_down)
        accWindow().toggleFullscreen();

    static f32 camera_l_speed = (f32)100/60;

    Vec2 camera_motion = get2DMotionDir(events, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT);
    camera_motion *= camera_l_speed;
    accWindow().accViewPort().moveRelative(camera_motion);
}

inline void MyGame::tick() {

}

inline void MyGame::initAssets() {
    AssetsManager& am = getWindow().getAssets();
    assets.images_pack_id = am.loadSpritesDirToTextureThrow("data/sprites", GL_RGBA, 2048, tidSprites);
    assets.arial_pack_id = am.loadFontToTextureThrow("data/fonts/arial.ttf", {{10, 50}}, 2048, tidArial);
    assets.courier_pack_id = am.loadFontToTextureThrow("data/fonts/courier.ttf", {{10, 50}}, 2048, tidCourier);

#ifdef DEBUG_BUILD
    am.getImagesPacks().accItem(assets.images_pack_id).getPackImage()->saveToPNG("data/sprites_pack.png");
    am.getFontsPacks().accItem(assets.arial_pack_id).getPackImage()->saveToPNG("data/arial_pack.png");
    am.getFontsPacks().accItem(assets.courier_pack_id).getPackImage()->saveToPNG("data/courier_pack.png");
#endif
}