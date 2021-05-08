/**
 * @file BaseEnemy.cpp.cc
 * @brief The base entity class for all enemies.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */

#include "GameState.h"
#include "BaseEnemy.h"
#include "Player.h"
#include <glm.hpp>
#include <utility>

BaseEnemy::BaseEnemy(const glm::vec2 &position, const glm::vec2 &hitBoxSize, GameState *attachToState,
                     std::weak_ptr<Entity> targetEntity, const size_t &collisionLayer) :
        Entity(position, hitBoxSize, collisionLayer, "../tmp/MechaChad-0001.png"),
        mGame(attachToState),
        mTargetEntity(std::move(targetEntity))
{
    mQueryLayers = quad::layers::Boundary | quad::layers::PlayerProjectile;
}

void BaseEnemy::createProjectile(std::shared_ptr<BaseProjectile> projectile)
{
    mGame->createEntity(std::move(projectile));
}
