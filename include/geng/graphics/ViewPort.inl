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
        matrices_.projection_zoomless = Mat3::createProjection2D(size_);
        Vec2 zoomed_vp_size = size_/z;
        matrices_.projection = Mat3::createProjection2D(zoomed_vp_size);
        // translate 0,0 to left-top corner from center
        matrices_.proj_screen = matrices_.projection_zoomless * Mat3::createTranslationT(-0.5f*getBaseSize());
        // change bound radius
        Vec2 half_extent = zoomed_vp_size*0.5f;
        f32 half_extent_l = half_extent.getLen();
        bound_.setRadius(half_extent_l);
    }

    inline const Vec2& ViewPort::getZoom()const {
        return zoom_;
    }

    inline void ViewPort::zoom(const Vec2& z) {
        setZoom(z*getZoom());
    }

    inline void ViewPort::setRotation(Angle a) {
        t_.setRotation(a);
    }

    inline void ViewPort::rotate(Angle a) {
        t_.rotate(a);
    }

    inline void ViewPort::moveRelative(const Vec2& m) {
        t_.moveRelative(m);
        bound_.setCenter(t_.getPosition());
    }

    inline void ViewPort::setPosition(const Vec2& p) {
        t_.setPosition(p);
        bound_.setCenter(t_.getPosition());
    }

    inline const Vec2& ViewPort::getPosition() {
        return t_.getPosition();
    }

    inline Angle ViewPort::getRotation()const {
        return t_.getRotation();
    }

    inline Vec2& ViewPort::accBaseSize() {
        return size_;
    }

    inline Vec2 ViewPort::getBaseSize()const {
        return size_;
    }

    inline void ViewPort::setBaseSize(const Vec2& size) {
        size_ = size;
        setZoom(zoom_);
    }

    inline void ViewPort::updateMatrices() {
        matrices_.camera = t_.calcMatrix();
        matrices_.view = Mat3::invert(matrices_.camera);
        matrices_.screen = Mat3::createTranslationT(size_*0.5)*matrices_.view;
        matrices_.proj_view = matrices_.projection * matrices_.view;
    }

    inline const ViewPort::Matrices& ViewPort::getMatrices()const {
        return matrices_;
    }

    inline Circle& ViewPort::getBoundingCircle() {
        return bound_;
    }

    inline Vec2 ViewPort::viewToWorld(const Vec2& v)const {
        Vec2 v_normalized(2.0f*v.getX()/size_.getX() -1.0f,
                               -2.0f*v.getY()/size_.getY() +1.0f);
        return matrices_.camera
               *Mat3::createProjectionIverse2D(size_/zoom_)
               *v_normalized;
    }

    inline Vec2 ViewPort::worldToView(const Vec2& v)const {
        Vec2 clip_coords =matrices_.projection*matrices_.view*v;
        Vec2 clip_coords_norm(0.5f*clip_coords.getX()+0.5f, -0.5f*clip_coords.getY()+0.5f);       // from -1..1 to 0..1
        return clip_coords_norm*size_;
    }

    inline Mat3 ViewPort::calcScreenLocalTr(const Mat3& global_tr, const Mat3& local_tr)const {
        return matrices_.proj_screen * global_tr * local_tr;
    }

    inline Mat3 ViewPort::calcScreenGlobalTr(const Mat3& global_tr)const {
        return matrices_.proj_screen * global_tr;
    }

    inline Mat3 ViewPort::calcWorldLocalTr(const Mat3& global_tr, const Mat3& local_tr)const {
        return matrices_.proj_view * global_tr * local_tr;
    }

    inline Mat3 ViewPort::calcWorldGlobalTr(const Mat3& global_tr)const {
        return matrices_.proj_view * global_tr;
    }

}