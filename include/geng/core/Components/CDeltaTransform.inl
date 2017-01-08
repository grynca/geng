#include "CDeltaTransform.h"
#include "CTransform.h"

namespace grynca {

    inline CDeltaTransform::Setter::~Setter() {
        if (transform_changed_) {
            CTransform& ct = me_.getComponent<CTransform>();
            ct.set(cdt_.getParent(me_).getComponent<CTransform>().get() * cdt_.delta_transform_, me_);
        }
    }

    inline CDeltaTransform::Setter& CDeltaTransform::Setter::setPosition(const Vec2& p) {
        cdt_.delta_transform_.setPosition(p);
        transform_changed_ = true;
        return *this;
    }

    inline CDeltaTransform::Setter& CDeltaTransform::Setter::setRotation(const Angle& r) {
        cdt_.delta_transform_.setRotation(r);
        transform_changed_ = true;
        return *this;
    }

    inline CDeltaTransform::Setter& CDeltaTransform::Setter::setScale(const Vec2& s) {
        cdt_.delta_transform_.setScale(s);
        transform_changed_ = true;
        return *this;
    }

    inline CDeltaTransform::Setter& CDeltaTransform::Setter::move(const Vec2& m) {
        if (!m.isZero()) {
            cdt_.delta_transform_.move(m);
            transform_changed_ = true;
        }
        return *this;
    }

    inline CDeltaTransform::Setter& CDeltaTransform::Setter::moveRelative(const Vec2& m) {
        if (!m.isZero()) {
            cdt_.delta_transform_.moveRelative(m);
            transform_changed_ = true;
        }
        return *this;
    }

    inline CDeltaTransform::Setter& CDeltaTransform::Setter::rotate(const Angle& r) {
        if (r != 0.0f) {
            cdt_.delta_transform_.rotate(r);
            transform_changed_ = true;
        }
        return *this;
    }

    inline CDeltaTransform::Setter& CDeltaTransform::Setter::scale(const Vec2& s) {
        if (!s.isZero()) {
            cdt_.delta_transform_.scale(s);
            transform_changed_ = true;
        }
        return *this;
    }

    inline CDeltaTransform::Setter& CDeltaTransform::Setter::addChild(Entity& ch) {
        ASSERT(ch.getRoles()[GERoles::erTreeTransformId]);
        CDeltaTransform& child_cdt = ch.getComponent<CDeltaTransform>();
        child_cdt.parent_id_ = me_.getIndex();
        child_cdt.depth_ = cdt_.depth_+1;
        cdt_.children_.push_back(ch.getIndex());
        return *this;
    }

    inline CDeltaTransform::Setter::Setter(CDeltaTransform& cdt, Entity& me)
    : transform_changed_(false), cdt_(cdt), me_(me)
    {}


    inline CDeltaTransform::CDeltaTransform()
     : flags_(u8(0)), depth_(u16(0))
    {}

    inline bool CDeltaTransform::isRoot()const {
        return parent_id_.isValid();
    }

    inline bool CDeltaTransform::isLeaf()const {
        return children_.empty();
    }

    inline EntityIndex CDeltaTransform::getParentIndex()const {
        return parent_id_;
    }

    inline Entity CDeltaTransform::getParent(const Entity& me)const {
        return me.getManager().getEntity(parent_id_);
    }

    inline u32 CDeltaTransform::getChildrenCount() const {
        return children_.size();
    }

    inline EntityIndex CDeltaTransform::getChildIndex(u32 child_id)const {
        return children_[child_id];
    }

    inline Entity CDeltaTransform::getChild(u32 child_id, const Entity& me)const {
        return me.getManager().getEntity(children_[child_id]);
    }

    inline CDeltaTransform::Setter CDeltaTransform::getSetter(Entity& me) {
        return Setter(*this, me);
    }

    inline u16 CDeltaTransform::getDepth()const {
        return depth_;
    }

    inline const Transform& CDeltaTransform::get()const {
        return delta_transform_;
    }

    inline Transform& CDeltaTransform::acc_() {
        return delta_transform_;
    }
}