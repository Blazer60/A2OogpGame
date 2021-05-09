/**
 * @file BaseEnemy.cpp.cc
 * @brief The base entity class for all enemies.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 15/04/2021
 */

#include "ShootAtTargetNode.h"
#include "ShootInCircleNode.h"
#include "ChargeNode.h"
#include "MechaChad.h"
#include "GameState.h"
#include "BaseEnemy.h"
#include "Player.h"
#include "HexedProjectile.h"
#include "MomentumProjectile.h"
#include "RicochetProjectile.h"
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

void BaseEnemy::createProjectile(const glm::vec2 &velocity, const char type)
{
    // todo: The 128.f is mecha chad specific (hit box off set and size). Generalise this for all enemies.
    glm::vec2 spawnPosition = mTransform.position + glm::vec2(128.f);
    std::shared_ptr<BaseProjectile> projectile;

    switch (type)
    {
        case projectiles::Default:
        default:
            projectile = std::make_shared<BaseProjectile>(spawnPosition, velocity, quad::layers::EnemyProjectile);
            break;
        case projectiles::Hexed:
        {
            auto hexed = std::make_shared<HexedProjectile>(spawnPosition, velocity, quad::layers::EnemyProjectile);
            hexed->setTrackedEntity(mTargetEntity);
            projectile = std::move(hexed);
            break;
        }
        case projectiles::Ricochet:
            projectile = std::make_shared<RicochetProjectile>(spawnPosition, velocity, quad::layers::EnemyProjectile);
            break;
        case projectiles::Momentum:
            // Velocity in this case is actually acceleration.
            projectile = std::make_shared<MomentumProjectile>(spawnPosition, velocity, quad::layers::EnemyProjectile);
            break;
    }

    mGame->createEntity(std::move(projectile));
}

glm::vec2 BaseEnemy::getTargetDirection()
{
    if (auto target = mTargetEntity.lock())
    {
        return glm::normalize(target->getHitBoxCenter() - getHitBoxCenter());
    }
    return glm::vec2(0.f);
}