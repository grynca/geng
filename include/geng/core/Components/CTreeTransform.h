#ifndef CTREECHILD_H
#define CTREECHILD_H

#include "maths/Transform.h"
#include "types/Index.h"

namespace grynca {

    class CTreeTransformData {
    public:
        static RolesMask componentRoles() {
            return GERoles::erTreeTransformMask();
        }

        CTreeTransformData();

        enum Flags {
            fDirtyGlobalTransform,
            fDirtyLocalTransform
        };

        Transform local_transform;
        union {
            struct {
                u8 flags;
                u8 children_count;
                u16 depth;
            };
            u32 pack;
        };
        EntityIndex parent_id;
        EntityIndex children[GENG_TREE_TRANSFORM_MAX_CHILDREN];
    };

    class CTreeTransform : public EntityAccessor<CTreeTransformData, CTransformData> {
        typedef EntityAccessor<CTreeTransformData, CTransformData> Base;
    public:
        DEF_CONSTR_AND_MOVE_ONLY(CTreeTransform);

        // TODO: rozdelit na Getter a Setter aby se zbytecne nedelal dirty update po getovani

        void construct();
        ~CTreeTransform();

        // warning: this sets gl. transform to parent's gl. transform
        //          local transform must be set after this
        void init(Entity& parent);
        template <typename EntAccessorT>
        void init(EntAccessorT& parent);

        // changes global transform (also updates local transform accordingly)
        void setTransform(const Transform& t);
        void setPosition(const Vec2& p);
        void setRotation(const Angle& r);
        void setScale(const Vec2& s);
        void move(const Vec2& m);
        void moveRelative(const Vec2& m);
        void rotate(const Angle& r);
        void scale(const Vec2& s);
        const Transform& getTransform()const;

        // Sets local Transform (also changes global transform accordingly)
        void setLocalTransform(const Transform& t);
        void setLocalPosition(const Vec2& p);
        void setLocalRotation(const Angle& r);
        void setLocalScale(const Vec2& s);
        void moveLocal(const Vec2& m);
        void moveRelativeLocal(const Vec2& m);
        void rotateLocal(const Angle& r);
        void scaleLocal(const Vec2& s);
        const Transform& getLocalTransform()const;

        // keep_local transforms node (and its children) to keep its local transform in new parent
        void attachParent(Entity& p, bool keep_local = false);
        template <typename EntAccessorT>
        void attachParent(EntAccessorT& p, bool keep_local = false);

        // node becomes root, its local transform changes to current global
        void detachParent();

        bool isRoot()const;
        bool isLeaf()const;
        EntityIndex getParentIndex()const;
        Entity getParent()const;
        template <typename EntAcc>
        EntAcc getParent()const;
        u32 getChildrenCount() const;
        EntityIndex getChildIndex(u32 child_id)const;
        Entity getChild(u32 child_id)const;
        template <typename EntAcc>
        EntAcc getChild(u32 child_id)const;
        u32 findChild(EntityIndex ch_eid)const;      // returns InvalidId() when child is not contained
        u16 getDepth()const;

        // is automatically called in constructor,
        //      call if you need sync (e.g. when you move parent)
        void updateGlobalTransformIfNeeded();
        void forceDirtyUpdate();
    private:
        enum {
            fMovedMask = BIT_MASK(0),
            fRotatedMask = BIT_MASK(1),
            fScaledMask = BIT_MASK(2),
            fTransformedMask = fMovedMask | fRotatedMask | fScaledMask
        };

        u32 findChildInner_(const CTreeTransformData* p_cttd, EntityIndex ch_eid)const;
        void removeFromParent_();
        void addToParent_(Entity &p_e, CTreeTransformData *p_cttd);
        void setTransformInParent_(Entity &p_e, CTreeTransformData *p_cttd, CTransformData *p_ctd, bool keep_local);
        Transform& lazyGetGlobalTransformRec_(Entity& e, CTreeTransformData* cttd, CTransformData* ctd)const;
        Entity getParentInner_(const CTreeTransformData* cttd)const;
        void recalcGlobalTransform_();
        void recalcLocalTransform_();
        void dirtyUpdate_();
        void setTransformFlag_(u32 flag_id);

        u8 dirty_flags_;
    };

}

#include "CTreeTransform.inl"
#endif //CTREECHILD_H
