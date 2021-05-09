/**
 * @file ShootNode.cpp.cc
 * @brief Holds basic information for an AI to shoot.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 09/05/2021
 */


#include "HelperFunctions.h"
#include "BaseEnemy.h"
#include "ShootInCircleNode.h"
#include "ShootNode.h"
#include "BaseProjectile.h"

ShootNode::ShootNode(BaseEnemy *enemy, const std::string &activateSound, const std::string &shotSound) :
    Node(enemy, activateSound),
    mProjectileType(projectiles::Default),
    mAmountOfProjectiles(1),
    mProjectileSpawnVelocity(glm::vec2(10.f)),
    mShootSound(shotSound),
    mProjectileCountIncrease(1)
{

}

void ShootNode::setProjectileType(char type)
{
    mProjectileType = type;
}

void ShootNode::setProjectileVelocity(glm::vec2 velocity)
{
    mProjectileSpawnVelocity = velocity;
}

void ShootNode::setAmountOfProjectiles(int amountOfProjectiles)
{
    mAmountOfProjectiles = amountOfProjectiles;
}

void ShootNode::setProjectileCountIncrease(int count)
{
    mProjectileCountIncrease = count;
}
