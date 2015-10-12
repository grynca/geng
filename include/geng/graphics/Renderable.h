#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "types/containers/VVector.h"
#include "maths/Transform.h"
#include "DrawSortingKey.h"
#include "CoordFrame.h"
#include "GraphicsDomain.h"

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

        bool getVisible()const;
        void setVisible(bool value);

        CoordFrame getCoordFrame();
        void setCoordFrame(CoordFrame f);

        Window& getWindow();
        Shader& getShader();
        VertexData& getVertexData();
        Geom& getGeom();

        static bool compare(Renderable* r1, Renderable* r2);
    protected:
        Renderable();

        template <typename ShaderType, typename VertexDataType>
        void init(Geom& geom, uint32_t layer_id);
        virtual void preRender() = 0;

        Window* window_;
        bool visible_;
        Transform local_transform_;
        Mat3 mvp_;
        DrawSortingKey sorting_key_;
        uint32_t geom_id_;
        float layer_z_;
        CoordFrame coord_frame_;
    private:
        float calcLayerZ_(uint32_t layer_id);
    };

    typedef VVector<GraphicsDomain> Renderables;
}

#include "Renderable.inl"
#endif //RENDERABLE_H
