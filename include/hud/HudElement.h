/**
 * @file HudElement.h
 * @brief Abstract base class for elements that are
 * not impacted by the position of the camera.
 * Project: A2OOPGame
 * @author Ryan Purse
 * @version 1.0.0
 * Initial Version: 04/05/2021
 */


#ifndef A2OOPGAME_HUDELEMENT_H
#define A2OOPGAME_HUDELEMENT_H

#include <glm.hpp>
#include <string>
#include <unordered_map>
#include <SDL_ttf.h>
#include <memory>

/**
 * Transforms for HUD Elements. Similar to Transform
 * but uses integers for its position.
 * @see transform
 */
struct hudTransform
{
    glm::ivec2 position;
    double rotation;
    glm::vec2 scale;

    hudTransform(const glm::ivec2 &position, double rotation, const glm::vec2 &scale);
};


/**
 * Abstract base class for elements that are
 * not impacted by the position of the camera.
 * @see Entity
 * @author Ryan Purse
 * @version 1.0.0 [Initial Version: 04/05/2021]
 */
class HudElement
{
public:
    enum anchorPoints : char {
        Top     = 0b0000,
        Bottom  = 0b0001,
        Center  = 0b0010,
        Left    = 0b0000,
        Right   = 0b0100,
        Middle  = 0b1000
    };

    explicit HudElement(const glm::ivec2 &position, char anchorPoint=0);
    virtual ~HudElement() = default;

    virtual void update() = 0;

    char getAnchorPoint() const;
    void setAnchorPoint(char anchorPoint);

    glm::ivec2 getPosition() const;

    void setScale(const glm::vec2 &newScale);
    glm::vec2  getScale() const;

    bool isRenderable() const;

protected:
    hudTransform mTransform;
    char mAnchorPoint;
    bool mIsRenderable;
};


#endif //A2OOPGAME_HUDELEMENT_H
