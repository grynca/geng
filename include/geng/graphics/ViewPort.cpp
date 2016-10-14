#include "ViewPort.h"

namespace grynca {

    ViewPort::ViewPort()
     : ViewPort(Vec2{0,0})
    {}

    ViewPort::ViewPort(const Vec2& size)
    {
        setZoom(Vec2{1,1});
    }

    void ViewPort::setZoom(const Vec2& z) {
        zoom_ = z;
        // also apply orthographic 2d projection
        projection_ = Mat3::createProjection2D(size_/z);
        // change bound radius
        //glm::vec2 half_extent = (size_/z)/2.0f;
        //float half_extent_l = glm::length(half_extent);
        //bound_.setRadius(half_extent_l);
    }

    const Vec2& ViewPort::getZoom() {
        return zoom_;
    }

    void ViewPort::zoom(const Vec2& z) {
        setZoom(z*getZoom());
    }

    void ViewPort::rotate(Angle a) {
        t_.rotate(a);
    }

    void ViewPort::moveRelative(const Vec2& m) {
        t_.moveRelative(m);
        //bound_.setCenter(pos_.getPosition());
    }

    void ViewPort::setPosition(const Vec2& p) {
        t_.setPosition(p);
        //bound_.setCenter(pos_.getPosition());
    }

    const Vec2& ViewPort::getPosition() {
        return t_.getPosition();
    }

    const Vec2& ViewPort::getBaseSize() {
        return size_;
    }

    void ViewPort::setBaseSize(const Vec2& size) {
        size_ = size;
        setZoom(zoom_);
    }

    void ViewPort::updateTransforms() {
        camera_transform_ = t_.calcMatrix();
        view_transform_ = Mat3::invert(getCameraTransform());
    }

    const Mat3& ViewPort::getCameraTransform() {
        return camera_transform_;
    }

    const Mat3& ViewPort::getViewTransform() {
        return view_transform_;
    }

    const Mat3& ViewPort::getProjectionTransform() {
        return projection_;
    }

    Vec2 ViewPort::viewToWorld(const Vec2& v) {
        Vec2 v_normalized(2.0f*v.getX()/size_.getX() -1.0f,
                               -2.0f*v.getY()/size_.getY() +1.0f);
        return camera_transform_
               *Mat3::createProjectionIverse2D(size_/zoom_)
               *v_normalized;
    }

    Vec2 ViewPort::worldToView(const Vec2& v) {
        Vec2 clip_coords =projection_*view_transform_*v;
        Vec2 clip_coords_norm(0.5f*clip_coords.getX()+0.5f, -0.5f*clip_coords.getY()+0.5f);       // from -1..1 to 0..1
        return clip_coords_norm*size_;
    }

}