#ifndef CTREECHILD_H
#define CTREECHILD_H

#include "maths/Transform.h"
#include "types/Index.h"

namespace grynca {

    class CDeltaTransform {
    public:
        class Setter {
        public:
            ~Setter();

            Setter& setPosition(const Vec2& p);
            Setter& setRotation(const Angle& r);
            Setter& setScale(const Vec2& s);
            Setter& move(const Vec2& m);
            Setter& moveRelative(const Vec2& m);
            Setter& rotate(const Angle& r);
            Setter& scale(const Vec2& s);
            Setter& addChild(Entity& ch);
        private:
            friend class CDeltaTransform;

            Setter(CDeltaTransform& cdt, Entity& me);

            bool transform_changed_;
            CDeltaTransform& cdt_;
            Entity& me_;
        };


    public:
        static RolesMask componentRoles() {
            return GERoles::erTreeTransformMask();
        }

        CDeltaTransform();

        bool isRoot()const;
        bool isLeaf()const;
        EntityIndex getParentIndex()const;
        Entity getParent(const Entity& me)const;
        u32 getChildrenCount() const;
        EntityIndex getChildIndex(u32 child_id)const;
        Entity getChild(u32 child_id, const Entity& me)const;
        Setter getSetter(Entity& me);
        u16 getDepth()const;

        const Transform& get()const;
        Transform& acc_();
    private:
        friend class Setter;
        friend class DeltaTransformSystem;

        enum Flags {
            fParentTransformed
        };

        std::bitset<8> flags_;
        u16 depth_;
        Transform delta_transform_;
        EntityIndex parent_id_;
        fast_vector<EntityIndex> children_;
    };

}

#include "CDeltaTransform.inl"
#endif //CTREECHILD_H
