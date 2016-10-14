#include "MyGame.h"
#include "entities/MyEntity.h"
#include "entities/Shuttle.h"
#include "entities/HUD.h"

using namespace std;
using namespace grynca;

class DummyActionState {
public:
    void update(float dt) {

    }

    void clear() {

    }

    static void getFields(Fields& f) {
        ADD_FIELD(DummyActionState, a);
        ADD_FIELD(DummyActionState, b);
        ADD_FIELD(DummyActionState, c);
    }

    int a;
    float b;
    char c;
};


void MyGame::init() {
#ifndef WEB
    getModule<Window>().setVSync(false);
#endif
    getModule<Server>().init(16, 0);

    // update systems
    addUpdateSystem<MovementSystem<MyGame> >();
    addUpdateSystem<TransformSystem<MyGame> >().init();
    addUpdateSystem<CollisionSystem<MyGame> >();

    Fields client_state_fields;
    DummyActionState::getFields(client_state_fields);
    addUpdateSystem<ServerNetworkSystem<MyGame> >().init(client_state_fields);

    // render systems
    addRenderSystem<RenderSystem<MyGame> >().init();
    addRenderSystem<CollisionsDebugSystem<MyGame> >().init();

    initAssets();

    MyEntity::initResources(*this);
    Shuttle::initResources(*this);

    test_ent_id = MyEntity::create(*this).getIndex();
    shuttle_id = Shuttle::create(*this).getIndex();
    hud_id = HUD::create(*this).getIndex();

    Entity shuttle2 = Shuttle::create(*this);
    shuttle2.getComponent<CTransform>().setPosition({-100, -100}, shuttle2);
    Speed& spd = shuttle2.getComponent<CMovable>().getSpeed();
    spd.setAngularSpeed(Angle::Pi/4);
    shuttle2_id = shuttle2.getIndex();
}

void MyGame::update() {
    static int i=0;

    EntityManager& em = getEntitiesManager();
    Entity e = em.tryGetEntity(shuttle_id);
    if (e.isValid())
        Shuttle::update(e, *this);
    e = em.tryGetEntity(test_ent_id);
    if (e.isValid())
        MyEntity::update(e);
    e = em.tryGetEntity(hud_id);
    if (e.isValid())
        HUD::update(e, *this);

    Events& events = getModule<Window>().getEvents();
    bool alt_down = events.isKeyDown(SDL_SCANCODE_LALT)|events.isKeyDown(SDL_SCANCODE_RALT);
    if (events.wasKeyPressed(SDL_SCANCODE_F4) && alt_down)
        quit();
    else if (events.wasKeyPressed(SDL_SCANCODE_RETURN) && alt_down)
        getModule<Window>().toggleFullscreen();

    static float camera_l_speed = (float)100/60;
    Vec2 camera_motion;
    camera_motion.accX() -= (int)events.isKeyDown(SDL_SCANCODE_LEFT);
    camera_motion.accX() += (int)events.isKeyDown(SDL_SCANCODE_RIGHT);
    camera_motion.accY() -= (int)events.isKeyDown(SDL_SCANCODE_UP);
    camera_motion.accY() += (int)events.isKeyDown(SDL_SCANCODE_DOWN);
    if (camera_motion.getX() && camera_motion.getY()) {
        static float norm = 1.f/(float)sqrt(2);
        camera_motion *= norm;
    }
    camera_motion *= camera_l_speed;
    getModule<Window>().getViewPort().moveRelative(camera_motion);
}

void MyGame::tick() {

}

void MyGame::initAssets() {
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
}