#include "CTreeTransform.h"
#include "CTransform.h"
#define WITHOUT_IMPL
#   include "../Systems/TreeTransformSystem.h"
#undef WITHOUT_IMPL

namespace grynca {

    inline void CTreeTransform::construct() {
        dirty_flags_ = 0;
        updateGlobalTransformIfNeeded();
    }

    inline CTreeTransform::~CTreeTransform() {
        dirtyUpdate_();
    }

    inline void CTreeTransform::init(Entity& parent) {
        ASSERT_M(!getData<CTreeTransformData>()->parent_id.isValid(),
                 "Must be called before setting parent");
        ASSERT_M(getData<CTreeTransformData>()->local_transform.isUnit(),
                 "Must be called before setting local transform");

        CTreeTransformData* p_ttd = parent.getData<CTreeTransformData>();
        addToParent_(parent, p_ttd);
        // set global transform to to that of a parent
        getData<CTransformData>()->set(lazyGetGlobalTransformRec_(parent, p_ttd, parent.getData<CTransformData>()));
    }

    template <typename EntAccessorT>
    inline void CTreeTransform::init(EntAccessorT& parent) {
        ASSERT_M(!getData<CTreeTransformData>()->parent_id.isValid(),
                "Must be called before setting parent");
        ASSERT_M(getData<CTreeTransformData>()->local_transform.isUnit(),
                "Must be called before setting local transform");

        CTreeTransformData* p_ttd = parent.template getData<CTreeTransformData>();
        Entity pe = parent.getEntity();
        addToParent_(pe, p_ttd);
        // set global transform to to that of a parent
        getData<CTransformData>()->set(lazyGetGlobalTransformRec_(pe, p_ttd, parent.template getData<CTransformData>()));
    }

    inline void CTreeTransform::setTransform(const Transform& t) {
        getData<CTransformData>()->set(t);
        recalcLocalTransform_();
        dirty_flags_ |= fTransformedMask;
    }

    inline void CTreeTransform::setPosition(const Vec2& p) {
        move(p - getData<CTransformData>()->getPosition());
    }

    inline void CTreeTransform::setRotation(const Angle& r) {
        rotate(r - getData<CTransformData>()->getRotation());
    }

    inline void CTreeTransform::setScale(const Vec2& s) {
        CTransformData* ctd = getData<CTransformData>();
        Vec2 scale_change = s/ctd->getScale();
        scale(scale_change);
    }

    inline void CTreeTransform::move(const Vec2& m) {
        CTransformData* ctd = getData<CTransformData>();
        CTreeTransformData* cttd = getData<CTreeTransformData>();
        ctd->move(m);

        // also change local transform
        Vec2 local_move = m.rotate(Angle::invertRotDir(ctd->getRotDir()));
        cttd->local_transform.move(local_move);
        dirty_flags_ |= fMovedMask;
    }

    inline void CTreeTransform::moveRelative(const Vec2& m) {
        Vec2 relative_move = m.rotate(getData<CTransformData>()->getRotDir());
        move(relative_move);
    }

    inline void CTreeTransform::rotate(const Angle& r) {
        getData<CTransformData>()->rotate(r);
        getData<CTreeTransformData>()->local_transform.rotate(r);
        dirty_flags_ |= fRotatedMask;
    }

    inline void CTreeTransform::scale(const Vec2& s) {
        getData<CTransformData>()->scale(s);
        getData<CTreeTransformData>()->local_transform.scale(s);
        dirty_flags_ |= fScaledMask;
    }

    inline const Transform& CTreeTransform::getTransform()const {
        return *getData<CTransformData>();
    }

    inline void CTreeTransform::setLocalTransform(const Transform& t) {
        getData<CTreeTransformData>()->local_transform = t;
        recalcGlobalTransform_();
        dirty_flags_ |= fTransformedMask;
    }

    inline void CTreeTransform::setLocalPosition(const Vec2& p) {
        moveLocal(p - getData<CTreeTransformData>()->local_transform.getPosition());
    }

    inline void CTreeTransform::setLocalRotation(const Angle& r) {
        rotateLocal(r - getData<CTreeTransformData>()->local_transform.getRotation());
    }

    inline void CTreeTransform::setLocalScale(const Vec2& s) {
        CTreeTransformData* cttd = getData<CTreeTransformData>();
        Vec2 scale_change = s/cttd->local_transform.getScale();
        scaleLocal(scale_change);
    }

    inline void CTreeTransform::moveLocal(const Vec2& m) {
        CTransformData* ctd = getData<CTransformData>();
        CTreeTransformData* cttd = getData<CTreeTransformData>();
        cttd->local_transform.move(m);

        // also change global transform
        Vec2 global_move = m.rotate(ctd->getRotDir());
        ctd->move(global_move);
        dirty_flags_ |= fMovedMask;
    }

    inline void CTreeTransform::moveRelativeLocal(const Vec2& m) {
        Vec2 relative_move = m.rotate(getData<CTreeTransformData>()->local_transform.getRotDir());
        moveLocal(relative_move);
    }

    inline void CTreeTransform::rotateLocal(const Angle& r) {
        getData<CTransformData>()->rotate(r);
        getData<CTreeTransformData>()->local_transform.rotate(r);
        dirty_flags_ |= fRotatedMask;
    }

    inline void CTreeTransform::scaleLocal(const Vec2& s) {
        getData<CTransformData>()->scale(s);
        getData<CTreeTransformData>()->local_transform.scale(s);
        dirty_flags_ |= fScaledMask;
    }

    inline const Transform& CTreeTransform::getLocalTransform()const {
        return getData<CTreeTransformData>()->local_transform;
    }

    inline void CTreeTransform::attachParent(Entity& p, bool keep_local) {
        ASSERT(p.getRoles()[GERoles::erTreeTransformId]);

        if (getData<CTreeTransformData>()->parent_id.isValid()) {
            removeFromParent_();
        }
        CTreeTransformData* p_ttd = p.getData<CTreeTransformData>();
        addToParent_(p, p_ttd);
        setTransformInParent_(p, p_ttd, p.getData<CTransformData>(), keep_local);
    }

    template <typename EntAccessorT>
    inline void CTreeTransform::attachParent(EntAccessorT& p, bool keep_local) {
        ASSERT(p.getEntity().getRoles()[GERoles::erTreeTransformId]);
        if (getData<CTreeTransformData>()->parent_id.isValid()) {
            removeFromParent_();
        }
        CTreeTransformData* p_ttd = p.template getData<CTreeTransformData>();
        Entity pe = p.getEntity();
        addToParent_(pe, p_ttd);
        setTransformInParent_(pe, p_ttd, p.template  getData<CTransformData>(), keep_local);
    }

    inline void CTreeTransform::detachParent() {
        removeFromParent_();
        getData<CTreeTransformData>()->parent_id = EntityIndex::Invalid();
    }

    inline CTreeTransformData::CTreeTransformData()
     : pack(0)
    {}

    inline bool CTreeTransform::isRoot()const {
        const CTreeTransformData* data = getData<CTreeTransformData>();
        return !data->parent_id.isValid();
    }

    inline bool CTreeTransform::isLeaf()const {
        return getData<CTreeTransformData>()->children_count == 0;
    }

    inline EntityIndex CTreeTransform::getParentIndex()const {
        return getData<CTreeTransformData>()->parent_id;
    }

    inline Entity CTreeTransform::getParent()const {
        return getParentInner_(getData<CTreeTransformData>());
    }

    template <typename EntAcc>
    inline EntAcc CTreeTransform::getParent()const {
        ASSERT(!isRoot());
        return getEntity().getManager().getEntity<EntAcc>(getData<CTreeTransformData>()->parent_id);
    }

    inline u32 CTreeTransform::getChildrenCount() const {
        return u32(getData<CTreeTransformData>()->children_count);
    }

    inline EntityIndex CTreeTransform::getChildIndex(u32 child_id)const {
        return getData<CTreeTransformData>()->children[child_id];
    }

    inline Entity CTreeTransform::getChild(u32 child_id)const {
        return getEntity().getManager().getEntity(getData<CTreeTransformData>()->children[child_id]);
    }

    template <typename EntAcc>
    inline EntAcc CTreeTransform::getChild(u32 child_id)const {
        return getEntity().getManager().getEntity<EntAcc>(getData<CTreeTransformData>()->children[child_id]);
    }

    inline u32 CTreeTransform::findChild(EntityIndex ch_eid)const {
        return findChildInner_(getData<CTreeTransformData>(), ch_eid);
    }

    inline u16 CTreeTransform::getDepth()const {
        return getData<CTreeTransformData>()->depth;
    }

    inline void CTreeTransform::updateGlobalTransformIfNeeded() {
        CTreeTransformData* cttd = getData<CTreeTransformData>();
        if (GET_BIT(cttd->flags, CTreeTransformData::fDirtyGlobalTransform)) {
            CTransformData* ctd = getData<CTransformData>();
            if (cttd->parent_id.isValid()) {
                Entity parent = getParentInner_(cttd);
                CTreeTransformData* p_cttd = parent.getData<CTreeTransformData>();
                CTransformData* p_ctd = parent.getData<CTransformData>();
                ctd->set(lazyGetGlobalTransformRec_(parent, p_cttd, p_ctd) * cttd->local_transform);
            }
            else {
                ctd->set(cttd->local_transform);
            }
            cttd->flags = CLEAR_BIT(cttd->flags, CTreeTransformData::fDirtyGlobalTransform);
            // when global transform is synced -> remove from TreeTransformSystem
            TreeTransformSystem* tts = getEntity().getManager().getSystemByType<TreeTransformSystem>(GameBase::spUpdate);
            ASSERT(tts);
            tts->unscheduleEntityUpdate(getEntityIndex());
            accEntity().clearTrackedFlagsForSystem(tts);
        }
    }

    inline void CTreeTransform::forceDirtyUpdate() {
        dirtyUpdate_();
        dirty_flags_ = 0;
    }

    inline void CTreeTransform::dirtyUpdate_() {
        switch (dirty_flags_) {
            case 0:
                break;
            case fMovedMask: {
                setTransformFlag_(GEFlags::fEntityMovedId);
            }break;
            case fRotatedMask: {
                setTransformFlag_(GEFlags::fEntityRotatedId);
            }break;
            case fScaledMask: {
                setTransformFlag_(GEFlags::fEntityScaledId);
            }break;

            default: {
                // more than 1 flag set -> notify about general entity transform
                setTransformFlag_(GEFlags::fEntityTransformedId);
            }break;
        }
    }

    inline void CTreeTransform::setTransformFlag_(u32 flag_id) {
        CTreeTransformData* cttd = getData<CTreeTransformData>();

        // set so that TreeTransformDataSystem does not schedule local transform update
        // (because it is already updated)
        cttd->flags = SET_BIT(cttd->flags, CTreeTransformData::fDirtyLocalTransform);
        accEntity().setFlag(flag_id);
        cttd->flags = CLEAR_BIT(cttd->flags, CTreeTransformData::fDirtyLocalTransform);
    }

    inline u32 CTreeTransform::findChildInner_(const CTreeTransformData* p_cttd, EntityIndex ch_eid)const {
        for (u32 i=0; i<p_cttd->children_count; ++i) {
            if (p_cttd->children[i] == ch_eid)
                return i;
        }
        return InvalidId();
    }

    inline void CTreeTransform::removeFromParent_() {
        Entity parent = getParentInner_(getData<CTreeTransformData>());
        CTreeTransformData* p_cttd = parent.getData<CTreeTransformData>();
        u32 ch_id = findChildInner_(p_cttd, getEntityIndex());
        ASSERT_M(ch_id != InvalidId(), "Not contained in parent.");
        arrayErase(p_cttd->children, ch_id, 1, p_cttd->children_count);
        --p_cttd->children_count;
    }

    inline void CTreeTransform::addToParent_(Entity &p_e, CTreeTransformData *p_cttd) {
        ASSERT(p_cttd->children_count < GENG_TREE_TRANSFORM_MAX_CHILDREN);
        ASSERT_M(findChildInner_(p_cttd, getEntityIndex())==InvalidId(),
                "Already contained in parent.");

        CTreeTransformData* cttd = getData<CTreeTransformData>();

        p_cttd->children[p_cttd->children_count] = getEntityIndex();
        ++p_cttd->children_count;

        cttd->parent_id = p_e.getIndex();
        cttd->depth = u16(p_cttd->depth+1);

        // TreeTransformSystem keeps max depth
        TreeTransformSystem* tts = getEntity().getManager().getSystemByType<TreeTransformSystem>(GameBase::spUpdate);
        ASSERT_M(tts, "TreeTransformSystem not available?");
        tts->checkMaxDepth(cttd->depth);
    }

    inline void CTreeTransform::setTransformInParent_(Entity &p_e, CTreeTransformData *p_cttd, CTransformData *p_ctd, bool keep_local) {
        CTreeTransformData* cttd = getData<CTreeTransformData>();
        CTransformData* ctd = getData<CTransformData>();

        if (keep_local) {
            ctd->set(lazyGetGlobalTransformRec_(p_e, p_cttd, p_ctd) * cttd->local_transform);
        }
        else {
            cttd->local_transform.set(*ctd - lazyGetGlobalTransformRec_(p_e, p_cttd, p_ctd));
        }
    }

    Transform& CTreeTransform::lazyGetGlobalTransformRec_(Entity& e, CTreeTransformData* cttd, CTransformData* ctd)const {
        // static
        if (GET_BIT(cttd->flags, CTreeTransformData::fDirtyGlobalTransform)) {
            if (cttd->parent_id.isValid()) {
                Entity parent = getParentInner_(cttd);
                CTreeTransformData* p_cttd = parent.getData<CTreeTransformData>();
                CTransformData* p_ctd = parent.getData<CTransformData>();
                ctd->set(lazyGetGlobalTransformRec_(parent, p_cttd, p_ctd) * cttd->local_transform);
            }
            else {
                ctd->set(cttd->local_transform);
            }
            cttd->flags = CLEAR_BIT(cttd->flags, CTreeTransformData::fDirtyGlobalTransform);
            // when global transform is synced -> remove from TreeTransformSystem
            TreeTransformSystem* tts = getEntity().getManager().getSystemByType<TreeTransformSystem>(GameBase::spUpdate);
            ASSERT(tts);
            tts->unscheduleEntityUpdate(e.getIndex());
            e.clearTrackedFlagsForSystem(tts);
            std::cout << " unscheduled " << e.getIndex() << std::endl;
        }
        return *ctd;
    }

    inline Entity CTreeTransform::getParentInner_(const CTreeTransformData* cttd)const {
        return getEntity().getManager().getEntity(cttd->parent_id);
    }

    inline void CTreeTransform::recalcGlobalTransform_() {
        CTreeTransformData* cttd = getData<CTreeTransformData>();
        CTransformData* ctd = getData<CTransformData>();

        if (cttd->parent_id.isValid()) {
            ctd->set(*getParent().getData<CTransformData>() * cttd->local_transform);
        }
        else {
            ctd->set(cttd->local_transform);
        }
    }

    inline void CTreeTransform::recalcLocalTransform_() {
        CTreeTransformData* cttd = getData<CTreeTransformData>();
        CTransformData* ctd = getData<CTransformData>();

        if (cttd->parent_id.isValid()) {
            cttd->local_transform.set(*ctd - *getParent().getData<CTransformData>());
        }
        else {
            cttd->local_transform.set(*ctd);
        }
    }

}