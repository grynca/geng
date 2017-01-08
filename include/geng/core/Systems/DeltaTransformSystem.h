#ifndef TRANSFORMSYSTEM_H
#define TRANSFORMSYSTEM_H

namespace grynca {

    class DeltaTransformSystem : public GengFlaggedSystem {
    public:
        virtual RolesMask NeededRoles() override {
            return GERoles::erTreeTransformMask();
        }

        virtual FlagsMask NeededFlags() override {
            return GEFlags::fMovedMask() | GEFlags::fRotScaledMask();
        }

        virtual void updateEntity(Entity& e, f32 dt) override {
            CTransform& ct = e.getComponent<CTransform>();
            CDeltaTransform& cdt = e.getComponent<CDeltaTransform>();

            // TODO: this is done uselessly after setting delta_transform also (do i care?)
            // update delta transform
            if (cdt.getParentIndex().isValid()) {
                // TODO: optimize out this if somehow ?
                cdt.acc_() = ct.get() / cdt.getParent(e).getComponent<CTransform>().get();
            }

            // flag descendants for transform update
            flagChildrenRec_(cdt, e);
        }

        virtual void postUpdate(f32 dt) override {
            std::sort(flagged_for_update_.begin(), flagged_for_update_.end(), [](const Entity& e1, const Entity& e2) {
                const CDeltaTransform& cdt1 = e1.getComponent<CDeltaTransform>();
                const CDeltaTransform& cdt2 = e2.getComponent<CDeltaTransform>();
                return cdt1.getDepth() < cdt2.getDepth();
            });

            for (u32 i=0; i<flagged_for_update_.size(); ++i) {
                Entity& e = flagged_for_update_[i];
                CTransform& ct = e.getComponent<CTransform>();
                CDeltaTransform& cdt = e.getComponent<CDeltaTransform>();
                CTransform& parent_ct = cdt.getParent(e).getComponent<CTransform>();

                ct.acc_() = parent_ct.get()*cdt.get();
                // set transfrom flag to all following systems in pipeline
                e.setFlag(GEFlags::fMovedId, this->getSystemId());
                e.setFlag(GEFlags::fRotScaledId, this->getSystemId());

                cdt.flags_.reset(CDeltaTransform::fParentTransformed);
            }
            flagged_for_update_.clear();
        }

    private:
        void flagChildrenRec_(const CDeltaTransform& cdt, Entity& e) {
            for (u32 i = 0; i < cdt.getChildrenCount(); ++i) {
                Entity che = cdt.getChild(i, e);
                CDeltaTransform& ch_cdt = che.getComponent<CDeltaTransform>();
                if (!ch_cdt.flags_[CDeltaTransform::fParentTransformed]) {
                    ch_cdt.flags_.set(CDeltaTransform::fParentTransformed);
                    flagged_for_update_.push_back(che);
                    flagChildrenRec_(ch_cdt, che);
                }
            }
        }

        fast_vector<Entity> flagged_for_update_;
    };
}

#endif //TRANSFORMSYSTEM_H
