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
#include <gtc/constants.hpp>
#include <gtx/vector_angle.hpp>
#include <utility>

BaseEnemy::BaseEnemy(const glm::vec2 &position, const glm::vec2 &hitBoxSize, GameState *attachToState,
                     std::weak_ptr<Entity> targetEntity, const size_t &collisionLayer) :
        Entity(position, hitBoxSize, collisionLayer, "../tmp/MechaChad-0001.png"),
        mGame(attachToState),
        mTargetEntity(std::move(targetEntity))
{
    mQueryLayers = quad::layers::Boundary | quad::layers::PlayerProjectile;
}

std::vector<glm::vec2> BaseEnemy::getUnitCirclePoints(unsigned int n, const float &offSet)
{
    const float offSetRadians = glm::radians(offSet);
    std::vector<glm::vec2> points;
    points.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        float theta = static_cast<float>(i) / static_cast<float>(n) * glm::two_pi<float>() + offSetRadians;
        float y = -glm::sin(theta);
        float x = glm::cos(theta);
        points.emplace_back(glm::vec2{ x, y });
    }
    return points;
}

std::vector<glm::vec2> BaseEnemy::getUnitConePoints(unsigned int n, const glm::vec2 &direction, float coneSpread)
{
    std::vector<glm::vec2> points;
    const float coneSpreadRadians = glm::radians(coneSpread);
    // Find the 'left most' vector angle.
    auto angle = glm::orientedAngle(direction, glm::vec2(-1.f, 0.f)) + glm::pi<float>() - coneSpreadRadians / 2;

    // Then work toward the 'right most' vector.
    for (int i = 0; i < n; ++i)
    {
        float y = -glm::sin(angle);
        float x = glm::cos(angle);
        points.emplace_back(glm::vec2{ x, y });

        angle += coneSpreadRadians / static_cast<float>(n);
    }
    return points;
}
