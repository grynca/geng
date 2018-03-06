#include "CTreeJoint.h"

namespace grynca {

    template <typename JointType, typename... JointInitArgs>
    inline void CTreeJoint::init(Entity& parent, JointInitArgs&&... args) {
        ASSERT_M(!getData<CTreeJointData>()->parent_joint_id.isValid(), "Must be called before setting parent");

        PhysicsManager& pm = accPhysicsManager_();
        JointType& j = pm.addJoint<JointType>(parent.getIndex().getInnerIndex(), getEntityIndex().getInnerIndex(), std::forward<JointInitArgs>(args)...);
        addToParent_(parent.getData<CTreeJointData>(), j.getId());
    }

    template <typename JointType, typename EntAccessorT, typename... JointInitArgs>
    inline void CTreeJoint::init(EntAccessorT& parent, JointInitArgs&&... args) {
        ASSERT_M(!getData<CTreeJointData>()->parent_joint_id.isValid(), "Must be called before setting parent");

        PhysicsManager& pm = accPhysicsManager_();
        JointType& j = pm.addJoint<JointType>(parent.getEntityIndex().getInnerIndex(), getEntityIndex().getInnerIndex(), std::forward<JointInitArgs>(args)...);
        addToParent_(parent.template getData<CTreeJointData>(), j.getId());
    }

    template <typename JointType, typename... JointInitArgs>
    inline void CTreeJoint::attachParent(Entity& p, JointInitArgs&&... args) {
        if (getData<CTreeJointData>()->parent_joint_id.isValid()) {
            removeFromParent_();
        }
        PhysicsManager& pm = accPhysicsManager_();
        JointType& j = pm.addJoint<JointType>(p.getIndex().getInnerIndex(), getEntityIndex().getInnerIndex(), std::forward<JointInitArgs>(args)...);
        addToParent_(p.getData<CTreeJointData>(), j.getId());
    }

    template <typename JointType, typename EntAccessorT, typename... JointInitArgs>
    inline void CTreeJoint::attachParent(EntAccessorT& p, JointInitArgs&&... args) {
        if (getData<CTreeJointData>()->parent_joint_id.isValid()) {
            removeFromParent_();
        }
        PhysicsManager& pm = accPhysicsManager_();
        JointType& j = pm.addJoint<JointType>(p.getEntityIndex().getInnerIndex(), getEntityIndex().getInnerIndex(), std::forward<JointInitArgs>(args)...);
        addToParent_(p.template getData<CTreeJointData>(), j.getId());
    }

    inline void CTreeJoint::detachParent() {
        removeFromParent_();
        getData<CTreeJointData>()->parent_joint_id.makeInvalid();
    }

    inline bool CTreeJoint::isRoot()const {
        return !getData<CTreeJointData>()->parent_joint_id.isValid();
    }

    inline bool CTreeJoint::isLeaf()const {
        return getData<CTreeJointData>()->children_joint_ids.empty();
    }

    inline EntityIndex CTreeJoint::getParentIndex()const {
        // parent is always body A in joint
        return getParentJoint().getBodyIdA();
    }

    inline Entity CTreeJoint::getParent()const {
        return getEntity().getManager().getEntity(getParentIndex());
    }

    template <typename EntAcc>
    inline EntAcc CTreeJoint::getParent()const {
        return getEntity().getManager().getEntity<EntAcc>(getParentIndex());
    }

    inline u32 CTreeJoint::getChildrenCount() const {
        return u32(getData<CTreeJointData>()->children_joint_ids.size());
    }

    inline EntityIndex CTreeJoint::getChildIndex(u32 child_id)const {
        // child is always body B in joint
        return getChildJoint(child_id).getBodyIdB();
    }

    inline Entity CTreeJoint::getChild(u32 child_id)const {
        return getEntity().getManager().getEntity(getChildIndex(child_id));
    }

    template <typename JointType>
    inline Entity CTreeJoint::getChildAndJoint(u32 child_id, JointType*& joint_out)const {
        joint_out = &getChildJoint<JointType>(child_id);
        return getEntity().getManager().getEntity(joint_out->getBodyIdB());
    }

    template <typename EntAcc, typename JointType>
    inline EntAcc CTreeJoint::getChildAndJoint(u32 child_id, JointType*& joint_out)const {
        joint_out = &getChildJoint<JointType>(child_id);
        return getEntity().getManager().getEntity<EntAcc>(joint_out->getBodyIdB());
    }

    template <typename EntAcc>
    inline EntAcc CTreeJoint::getChild(u32 child_id)const {
        return getEntity().getManager().getEntity<EntAcc>(getChildIndex(child_id));
    }

    inline u32 CTreeJoint::findChild(EntityIndex ch_eid)const {
        return findChildInner_(getData<CTreeJointData>(), ch_eid);
    }

    inline Index CTreeJoint::getParentJointId()const {
        return getData<CTreeJointData>()->parent_joint_id;
    }

    inline Index CTreeJoint::getChildJointId(u32 child_id)const {
        const CTreeJointData* data = getData<CTreeJointData>();
        return data->children_joint_ids[child_id];
    }

    inline u16 CTreeJoint::getChildJointTypeId(u32 child_id)const {
        return getChildJointId(child_id).getAuxIndex();
    }

    inline Joint& CTreeJoint::getParentJoint()const {
        return accPhysicsManager_().accJoint(getParentJointId());
    }

    inline Joint& CTreeJoint::getChildJoint(u32 child_id)const {
        return accPhysicsManager_().accJoint(getChildJointId(child_id));
    }

    template <typename JointType>
    inline JointType& CTreeJoint::getParentJoint()const {
        ASSERT(!isRoot());
        return accPhysicsManager_().accJoint<JointType>(getParentJointId());
    }

    template <typename JointType>
    inline JointType& CTreeJoint::getChildJoint(u32 child_id)const {
        return accPhysicsManager_().accJoint<JointType>(getChildJointId(child_id));
    }

    inline PhysicsManager& CTreeJoint::accPhysicsManager_()const {
        return GameBase::get().accPhysicsManager();
    }

    inline u32 CTreeJoint::findChildInner_(const CTreeJointData* p_tjd, EntityIndex ch_eid)const {
        PhysicsManager& pm = accPhysicsManager_();
        for (u32 i=0; i<p_tjd->children_joint_ids.size(); ++i) {
            const Joint& j = pm.getJoint(p_tjd->children_joint_ids[i]);
            if (j.getBodyIdB() == ch_eid)
                return i;
        }
        return InvalidId();
    }

    inline void CTreeJoint::removeFromParent_() {
        Entity parent = getParent();
        CTreeJointData* p_tjd = parent.getData<CTreeJointData>();
        u32 ch_id = findChildInner_(p_tjd, getEntityIndex());
        ASSERT_M(ch_id != InvalidId(), "Not contained in parent.");
        // remove joint
        Index joint_id = p_tjd->children_joint_ids[ch_id];
        accPhysicsManager_().removeJoint(joint_id);

        p_tjd->children_joint_ids.erase(p_tjd->children_joint_ids.begin()+ch_id);
    }

    inline void CTreeJoint::addToParent_(CTreeJointData* p_tjd, Index joint_id) {
        ASSERT_M(findChildInner_(p_tjd, getEntityIndex())==InvalidId(), "Already contained in parent.");

        CTreeJointData* cttd = getData<CTreeJointData>();
        p_tjd->children_joint_ids.push_back(joint_id);
        cttd->parent_joint_id = joint_id;
    }

}