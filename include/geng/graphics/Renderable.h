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
        virtual ~Renderable();
        void render();

        Transform& getLocalTransform();
        void setMVP(const Mat3& mvp);
        const Mat3& getMVP()const;

        bool getVisible()const;
        void setVisible(bool value);

        CoordFrame getCoordFrame()const;
        void setCoordFrame(CoordFrame f);

        Window& getWindow()const;
        Shader& getShader()const;
        VertexData& getVertexData()const;
        Geom& getGeom()const;

        uint16_t getLayerId()const;
        void setLayerId(uint16_t layer_id);

        static bool compare(Renderable* r1, Renderable* r2);
    protected:
        Renderable();

        template <typename ShaderType, typename VertexDataType>
        void init(Geom& geom);

        virtual void preRender() = 0;

        Window* window_;
        bool visible_;
        Transform local_transform_;
        Mat3 mvp_;
        DrawSortingKey sorting_key_;
        VertexData::ItemRef geom_ref_;
        float layer_z_;
        CoordFrame coord_frame_;
    private:
        float calcLayerZ_(uint32_t layer_id);
    };

    typedef VVector<GraphicsDomain> Renderables;
}

#include "Renderable.inl"
#endif //RENDERABLE_H
