#ifndef HITABLELIST_H
#define HITABLELIST_H

# include "Hitable.h"

class HitableList: public Hitable {
    public:
        HitableList() {}
        HitableList(Hitable** l, int n) {
            list = l;
            size = n;
        }
        virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const;
        Hitable** list;
        int size;
};

bool HitableList::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
    HitRecord tempRec;
    bool didHit = false;
    double closest = tMax;

    for (int i = 0; i < size; i++) {
        if (list[i]->hit(r, tMin, closest, tempRec))  {
            didHit = true;
            closest = tempRec.t;
            rec = tempRec;
        }
    }
    return didHit;
}

#endif // HITABLELIST_H