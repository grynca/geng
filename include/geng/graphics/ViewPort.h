#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "maths/Transform.h"

namespace grynca {

    class ViewPort {
    public:
        ViewPort();     // creates dummy viewport with size (0,0)
        ViewPort(const Vec2& size);

        void setZoom(const Vec2& z);
        const Vec2& getZoom();

        void zoom(const Vec2& z);

        void rotate(Angle a);
        void moveRelative(const Vec2& m);
        void setPosition(const Vec2& p);

        const Vec2& getPosition();

        // e.g. screen resolution
        const Vec2& getBaseSize();
        void setBaseSize(const Vec2& size);

        void updateTransforms();
        const Mat3& getCameraTransform();
        const Mat3& getViewTransform();
        const Mat3& getScreenTransform();
        const Mat3& getProjectionTransform();

        //Circle& getBoundingCircle();      //TODO:

        Vec2 viewToWorld(const Vec2& v);
        Vec2 worldToView(const Vec2& v);

    private:
        Transform t_;

        Vec2 size_;        // basic size of viewport (not-scaled)
        Vec2 zoom_;
        Mat3 projection_;

        Mat3 camera_transform_;
        Mat3 view_transform_;
        Mat3 screen_transform_;
    };

}
#include "ViewPort.inl"
#endif //VIEWPORT_H
