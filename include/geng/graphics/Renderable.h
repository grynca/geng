#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "types/containers/VVector.h"
#include "maths/Transform.h"
#include "DrawSortingKey.h"
#include "Frame.h"
#include "Graphics.h"

namespace grynca {

    // fw
    class Window;
    class Geom;
    class DrawSortingKey;
    class Shader;
    class VertexData;

    class Renderable {
    public:
        virtual ~Renderable() {}
        void render();

        Transform& getLocalTransform();
        void setMVP(const Mat3& mvp);
        const Mat3& getMVP();


        Frame getFrame();
        void setFrame(Frame f);

        Window& getWindow();
        Shader& getShader();
        VertexData& getVertexData();
        Geom& getGeom();

        static bool compare(Renderable* r1, Renderable* r2);
    protected:
        Renderable(Window& window);

        template <typename ShaderType, typename VertexDataType>
        void init(Geom& geom, uint32_t layer_id);
        virtual void preRender() = 0;

        Window* window_;
        Transform local_transform_;
        Mat3 mvp_;
        DrawSortingKey sorting_key_;
        uint32_t geom_id_;
        float layer_z_;
        Frame frame_;
    private:
        float calcLayerZ_(uint32_t layer_id);
    };

    typedef VVector<Graphics> Renderables;
}

#include "Renderable.inl"
#endif //RENDERABLE_H
