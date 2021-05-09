/**
 * @file ShootNode.cpp.cc
 * @brief Holds basic information for an AI to shoot.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 09/05/2021
 */


#include "ShootNode.h"
#include "BaseProjectile.h"

ShootNode::ShootNode(MechaChad *mechaChad, const std::string &soundPath) :
    Node(mechaChad, soundPath),
    mProjectileType(projectiles::Default),
    mAmountOfProjectiles(1),
    mProjectileSpawnVelocity(glm::vec2(10.f)),
    mShootSound("../sfx/shurikenThrow.mp3")
{

}
