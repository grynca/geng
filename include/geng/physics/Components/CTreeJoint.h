#ifndef CTREEJOINT_H
#define CTREEJOINT_H

#include "../../GERoles.h"
#include "../../geng_config.h"

namespace grynca {

    // fw
    class CBodyData;

    class CTreeJointData {
    public:
        static RolesMask componentRoles() {
            return GERoles::erTreeJointMask();
        }

        Index parent_joint_id;
        fast_vector<Index> children_joint_ids;
    };

    class CTreeJoint : public EntityAccessor<CTreeJointData, CBodyData> {
    public:
        DEF_CONSTR_AND_MOVE_ONLY(CTreeJoint);

        // init attachement to parent
        template <typename JointType, typename... JointInitArgs>
        void init(Entity& parent, JointInitArgs&&... args);
        template <typename JointType, typename EntAccessorT, typename... JointInitArgs>
        void init(EntAccessorT& parent, JointInitArgs&&... args);


        template <typename JointType, typename... JointInitArgs>
        void attachParent(Entity& p, JointInitArgs&&... args);
        template <typename JointType, typename EntAccessorT, typename... JointInitArgs>
        void attachParent(EntAccessorT& p, JointInitArgs&&... args);

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
        template <typename JointType>
        Entity getChildAndJoint(u32 child_id, JointType*& joint_out)const;
        template <typename EntAcc, typename JointType>
        EntAcc getChildAndJoint(u32 child_id, JointType*& joint_out)const;
        template <typename EntAcc>
        EntAcc getChild(u32 child_id)const;
        u32 findChild(EntityIndex ch_eid)const;

        Index getParentJointId()const;
        Index getChildJointId(u32 child_id)const;
        u16 getChildJointTypeId(u32 child_id)const;
        Joint& getParentJoint()const;
        Joint& getChildJoint(u32 child_id)const;
        template <typename JointType>
        JointType& getParentJoint()const;
        template <typename JointType>
        JointType& getChildJoint(u32 child_id)const;
    private:
        PhysicsManager& accPhysicsManager_()const;
        u32 findChildInner_(const CTreeJointData* p_ctjd, EntityIndex ch_eid)const;
        void removeFromParent_();
        void addToParent_(CTreeJointData *p_ctjd, Index joint_id);
    };
}

#include "CTreeJoint.inl"
#endif //TREEJOINT_H
