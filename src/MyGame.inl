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
    getModule<Window>().setVSync(false);
#endif
    getModule<Server>().init(16, 0);

    // update systems
    addUpdateSystem<MovementSystem>();
    addUpdateSystem<DeltaTransformSystem>();
    addUpdateSystem<CollisionSystem>();

    // TODO: v initu nejak getnout z GameBase()
//    Fields client_state_fields;
//    DummyActionState::getFields(client_state_fields);
//    addUpdateSystem<ServerNetworkSystem<MyGame> >().init(client_state_fields);

    // render systems
    addRenderSystem<CollisionsDebugSystem>();
    addRenderSystem<RenderSystem>();

    initAssets();

    MyEntity::Resources::create(*this);
    HUD::Resources::create(*this);
    Shuttle::Resources::create(*this);

    shuttle_id = createEntity<Shuttle>(Shuttle::init).getIndex();
    test_ent_id = createEntity<MyEntity>(MyEntity::init).getIndex();
    hud_id = createEntity<HUD>(HUD::init).getIndex();

//    shuttle2_id = createEntity<Shuttle>([](Entity& e, MyGame& g){
//        Shuttle::init(e, g);
//        e.getComponent<CTransform>().setPosition({-100, -100}, e);
//        Speed& spd = e.getComponent<CMovable>().getSpeed();
//        spd.setAngularSpeed(Angle::Pi/4);
//    }).getIndex();
//
//    Entity ch1 = createEntity<GUIElement<MyGame> >([](Entity& e, MyGame& g) {
//        GUIElement<MyGame>::setBackgroundRect(e, {50, 50}, 12, Colorf::Green());
//    });

//    Entity ch2 = createEntity<GUIElement<MyGame> >([](Entity& e, MyGame& g) {
//        GUIElement<MyGame>::setBackgroundRect(e, {50, 50}, 12, Colorf::Blue());
//    });
//
//    gui_root_id = createEntity<GUIElement<MyGame> >([&ch1, &ch2](Entity& e, MyGame& g) {
//        CTransform& ct = e.getComponent<CTransform>();
//        ct.setPosition({50, 50}, e);
//        GUIElement<MyGame>::setBackgroundRect(e, {200, 200}, 11, Colorf::Red());
//        GUIElement<MyGame>::addChild(e, ch1, {100, 0});
//        GUIElement<MyGame>::addChild(e, ch2, {0, 100});
//    }).getIndex();

//    gui_ch1_id = ch1.getIndex();
//    gui_ch2_id = ch2.getIndex();
}

inline void MyGame::update() {
    udpateEntitySafe(shuttle_id, Shuttle::update);
    udpateEntitySafe(test_ent_id, MyEntity::update);
    udpateEntitySafe(hud_id, HUD::update);
    udpateEntitySafe(gui_root_id, [](Entity& e, GameBase& g) {
        e.getComponent<CTransform>().move(Vec2(10, 0)*g.getTargetTicklen(), e);
    });

    Events& events = getModule<Window>().getEvents();
    bool alt_down = events.isKeyDown(SDL_SCANCODE_LALT)|events.isKeyDown(SDL_SCANCODE_RALT);
    if (events.wasKeyPressed(SDL_SCANCODE_F4) && alt_down)
        quit();
    else if (events.wasKeyPressed(SDL_SCANCODE_RETURN) && alt_down)
        getModule<Window>().toggleFullscreen();

    static f32 camera_l_speed = (f32)100/60;
    Vec2 camera_motion;
    camera_motion.accX() -= (int)events.isKeyDown(SDL_SCANCODE_LEFT);
    camera_motion.accX() += (int)events.isKeyDown(SDL_SCANCODE_RIGHT);
    camera_motion.accY() -= (int)events.isKeyDown(SDL_SCANCODE_UP);
    camera_motion.accY() += (int)events.isKeyDown(SDL_SCANCODE_DOWN);
    if (camera_motion.getX() && camera_motion.getY()) {
        static f32 norm = 1.f/(f32)sqrt(2);
        camera_motion *= norm;
    }
    camera_motion *= camera_l_speed;
    getModule<Window>().getViewPort().moveRelative(camera_motion);
}

inline void MyGame::tick() {

}

inline void MyGame::initAssets() {
    AssetsManager& am = getModule<AssetsManager>();
    ImagesPack& images = am.getImagesPacks().addItem();
    FontPack& fonts = am.getFontsPacks().addItem();
    Textures2DManager& textures = getModule<Window>().getTextures();

    images.loadDir("data/sprites", GL_RGBA, 2048);
    Texture2D& sprites_tex = textures.addItem("sprites");
    sprites_tex.bind(tidSprites);
    sprites_tex.set(images.getPackImage());

    fonts.loadFont("data/fonts/arial.ttf", {{10, 50}}, 2048);
    Texture2D& fonts_tex = textures.addItem("fonts");
    fonts_tex.bind(tidFonts);
    fonts_tex.set(fonts.getPackImage());

    assets.fonts_pack_id = fonts.getId();
    assets.images_pack_id = images.getId();

    images.getPackImage()->saveToPNG("data/sprites_pack.png");
    fonts.getPackImage()->saveToPNG("data/fonts_pack.png");
}