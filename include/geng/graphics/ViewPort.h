#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "maths/Transform.h"

namespace grynca {

    class ViewPort {
    public:

        struct Matrices {
            Mat3 projection;                // projection with applied zoom (e.g. for scene)
            Mat3 projection_zoomless;       // projection 1:1 with viewport resolution (e.g. for HUD)
            Mat3 camera;
            Mat3 view;
            Mat3 screen;
            Mat3 proj_view;
            Mat3 proj_screen;
        };

    public:

        ViewPort();     // creates dummy viewport with size (0,0)
        ViewPort(const Vec2& size);

        void setZoom(const Vec2& z);
        const Vec2& getZoom()const;

        void zoom(const Vec2& z);
        void setRotation(Angle a);
        void rotate(Angle a);
        void moveRelative(const Vec2& m);
        void setPosition(const Vec2& p);

        const Vec2& getPosition();
        Angle getRotation()const;

        // e.g. screen resolution
        Vec2& accBaseSize();
        Vec2 getBaseSize()const;
        void setBaseSize(const Vec2& size);

        // called each frame by Game
        //
        void updateMatrices();
        const Matrices& getMatrices()const;

        Circle& getBoundingCircle();

        Vec2 viewToWorld(const Vec2& v)const;
        Vec2 worldToView(const Vec2& v)const;

        // Screen Frame: 0,0 is left-top of screen, coords are pixels

        // helper functions for calculating transforms
        Mat3 calcScreenLocalTr(const Mat3& global_tr, const Mat3& local_tr)const;
        Mat3 calcScreenGlobalTr(const Mat3& global_tr)const;
        Mat3 calcWorldLocalTr(const Mat3& global_tr, const Mat3& local_tr)const;
        Mat3 calcWorldGlobalTr(const Mat3& global_tr)const;

    private:
        Transform t_;
        Matrices matrices_;     // precalculated matrices for each frame

        Vec2 size_;        // basic size of viewport (not-scaled)
        Vec2 zoom_;

        Circle bound_;
    };

}
#include "ViewPort.inl"
#endif //VIEWPORT_H
