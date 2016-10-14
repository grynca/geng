#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "maths/Transform.h"
#include "geng/graphics/DrawSortingKey.h"
#include "geng/graphics/CoordFrame.h"

namespace grynca {

    // fw
    class Window;
    class Geom;
    class Shader;
    class VertexData;

    class NormOffset {
    public:
        static Vec2 Center() { return Vec2{-0.5f, -0.5f}; };
        static Vec2 LeftTop() { return Vec2{0,0}; }
        static Vec2 RightTop() { return Vec2{-1, 0}; }
        static Vec2 RightBot() { return Vec2{-1, -1}; }
        static Vec2 LeftBot() { return Vec2{0, -1}; }
    };

    class RenderableBase {
    public:
        virtual ~RenderableBase();

        Transform& accLocalTransform();

        bool getVisible()const;
        void setVisible(bool value);

        CoordFrame getCoordFrame()const;
        void setCoordFrame(CoordFrame f);

        Shader& getShader()const;
        VertexData& getVertexData()const;
        Geom& getGeom()const;

        uint16_t getLayerId()const;
        void setLayerId(uint16_t layer_id);

        template <typename ShaderType>
        void setShader();

        template <typename VertexDataType>
        void setVertexLayout();
                
        static bool compare(RenderableBase* r1, RenderableBase* r2);
    protected:
        friend class Renderer2D;

        enum Flags {
            fVisible,
            fScreenCoordFrame
        };

        RenderableBase();

        template <typename ShaderType, typename VertexDataType>
        void init(Geom& geom);
        void render();
        virtual void setUniforms(const Mat3& mvp, Shader& s) = 0;

        Window& getWindow()const;
        Shader& getShaderInner(Window& w)const;
        VertexData& getVertexDataInner(Window& w)const;

        Transform local_transform_;
        DrawSortingKey sorting_key_;
        VertexData::ItemRef geom_ref_;
        float layer_z_;
        uint8_t flags_;
    private:
        float calcLayerZ_(uint32_t layer_id);
    };
}

#include "RenderableBase.inl"
#endif //RENDERABLE_H
