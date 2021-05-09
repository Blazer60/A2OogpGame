/**
 * @file Barrier.cpp.cc
 * @brief The Wall for the arena that entities are held in. This is only the image part.
 * See wall collider for actual bounding boxes
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 19/04/2021
 */


#include "BarrierImage.h"
#include "QuadTreeHelpers.h"

BarrierImage::BarrierImage(const glm::vec2 &position) :
    Entity(position, glm::vec2(4.f), "assets/images/Walls-0001.png")
{
}

void BarrierImage::update()
{

}

void BarrierImage::onCollision(const std::shared_ptr<Entity> &other)
{

}
