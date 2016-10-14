#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "maths/Transform.h"
#include "maths/shapes/Shape.h"
#include "types/VariantCaller.h"
#include "../graphics/Renderables/SpriteRenderable.h"

namespace grynca {

    class Collidable : public Shape {
    public:
        ARect& boundSprite(SpriteRenderable& sprite) {
            accLocalTransform() = sprite.accLocalTransform();
            return Shape::set<ARect>(sprite.getNormOffset()*sprite.getSize(), sprite.getSize());
        }

        Transform& accLocalTransform() { return local_transform_; }
        ARect& getBound() { return bound_; }
        void recalcBound() {
            VariantCaller<RecalcBound>::call(*(Shape*)this, bound_);
        }
    private:
        struct RecalcBound {
            template <typename T>
            static void f(Shape& s, T& real_type, ARect& bound_out) {
                bound_out = real_type.calcARectBound();
            }
        };

        Transform local_transform_;
        ARect bound_;
    };

    typedef fast_vector<Collidable> Collidables;
};

#endif //COLLIDABLE_H
