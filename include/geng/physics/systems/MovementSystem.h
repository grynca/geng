#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../Speed.h"

namespace grynca {

    class MovementSystem : public System {
    public:
        struct UpdatePos {
            template <typename T>
            static void f(T& e, double dt) {
                Transform& t = e.transform;
                Speed& s = e.speed;
                t.setPosition(t.getPosition()+s.getLinearSpeed()*dt);
                t.setRotation(t.getRotation()+s.getAngularSpeed()*dt);
            }
        };

        template <typename T>
        void update(Entity& e, T& t, double dt) {
            Call<UpdatePos>::ifTrue<HasProps<T, props::has_transform, props::has_speed> > (t, dt);
        }

        virtual RolesMask getNeededRoles() {
            return {erMovable};
        }
    };

}

#endif //MOVEMENTSYSTEM_H
