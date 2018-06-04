
#ifndef SAFARI_ENTITY_H
#define SAFARI_ENTITY_H


class Entity {
private:
    int m_id;

    int generateId() {
        static int id = 0;
        return id++;
    }

    // position

    // bounding box

    // rotation


};


#endif //SAFARI_ENTITY_H
