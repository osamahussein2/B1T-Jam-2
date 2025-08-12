#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include "ItemType.h"

class Item : public Entity
{
    public:
                         Item(ItemType type);
                         ~Item();

   
        void                    update() override;
        void                    render() override;
        void                    moveEntity(Vector2 position) override;
        void                    collision(Entity* other) override;

        ItemType           getEntityID() const;

    private:
         ItemType   m_ItemType;
};

#endif

