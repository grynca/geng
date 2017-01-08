#include "ViewPort.h"

namespace grynca {

    inline ViewPort::ViewPort()
     : ViewPort(Vec2{0,0})
    {}

    inline ViewPort::ViewPort(const Vec2& size)
    {
        setZoom(Vec2{1,1});
    }

    inline void ViewPort::setZoom(const Vec2& z) {
        zoom_ = z;
        // also apply orthographic 2d projection
        projection_ = Mat3::createProjection2D(size_/z);
        // change bound radius
        //glm::vec2 half_extent = (size/z)/2.0f;
        //f32 half_extent_l = glm::length(half_extent);
        //bound_.setRadius(half_extent_l);
    }

    inline const Vec2& ViewPort::getZoom() {
        return zoom_;
    }

    inline void ViewPort::zoom(const Vec2& z) {
        setZoom(z*getZoom());
    }

    inline void ViewPort::rotate(Angle a) {
        t_.rotate(a);
    }

    inline void ViewPort::moveRelative(const Vec2& m) {
        t_.moveRelative(m);
        //bound_.setCenter(pos_.getPosition());
    }

    inline void ViewPort::setPosition(const Vec2& p) {
        t_.setPosition(p);
        //bound_.setCenter(pos_.getPosition());
    }

    inline const Vec2& ViewPort::getPosition() {
        return t_.getPosition();
    }

    inline const Vec2& ViewPort::getBaseSize() {
        return size_;
    }

    inline void ViewPort::setBaseSize(const Vec2& size) {
        size_ = size;
        setZoom(zoom_);
    }

    inline void ViewPort::updateTransforms() {
        camera_transform_ = t_.calcMatrix();
        view_transform_ = Mat3::invert(getCameraTransform());
        screen_transform_ = Mat3::createTranslationT(size_*0.5)*view_transform_;
    }

    inline const Mat3& ViewPort::getCameraTransform() {
        return camera_transform_;
    }

    inline const Mat3& ViewPort::getViewTransform() {
        return view_transform_;
    }

    inline const Mat3& ViewPort::getScreenTransform() {
        return screen_transform_;
    }

    inline const Mat3& ViewPort::getProjectionTransform() {
        return projection_;
    }

    inline Vec2 ViewPort::viewToWorld(const Vec2& v) {
        Vec2 v_normalized(2.0f*v.getX()/size_.getX() -1.0f,
                               -2.0f*v.getY()/size_.getY() +1.0f);
        return camera_transform_
               *Mat3::createProjectionIverse2D(size_/zoom_)
               *v_normalized;
    }

    inline Vec2 ViewPort::worldToView(const Vec2& v) {
        Vec2 clip_coords =projection_*view_transform_*v;
        Vec2 clip_coords_norm(0.5f*clip_coords.getX()+0.5f, -0.5f*clip_coords.getY()+0.5f);       // from -1..1 to 0..1
        return clip_coords_norm*size_;
    }

}