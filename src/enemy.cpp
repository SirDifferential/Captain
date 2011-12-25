#include "enemy.hpp"
#include "sprite.hpp"
#include "manager.hpp"
#include "roomManager.hpp"
#include "room.hpp"
#include "ship.hpp"

Enemy::Enemy(std::string n, std::string s, Vector3 loc)
{
    fprintf(stderr, "Enemy constructing\n");
    name = n;
    spritePath = s;
    boost::shared_ptr<Sprite> tempPtr(new Sprite(s));
    enemySprite = tempPtr;
    location = loc;
    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;
}

Enemy::~Enemy()
{
}

void Enemy::operate()
{
    think();
    update();
    render();
}

void Enemy::think()
{
    // Placeholder: attempt to ram player. Can be modified for "travel to coords (x,y)"
    Vector3 playerCoords = manager.getRoomMgr()->giveCurrentRoom()->getPlayerShip()->getLocation();
    Vector3 playerVelocity = manager.getRoomMgr()->giveCurrentRoom()->getPlayerShip()->getVelocity();
    Vector3 distanceToPlayer;
    distanceToPlayer.x = playerCoords.x - location.x;
    distanceToPlayer.y = playerCoords.y - location.y;

    // Using distanceToPlayer, figure out the ratio by which thrust must be applied
    // Assuming vector(13, 6, 0)
    // sqrt(13^2 + 6^2)
    // 14.318
    // angle = atan(x/y)
    // 
    // Right now we know that the ship should head towards "angle"
    // Begin rotating, and keep thrusthing forwards if it is optimal
    // Thrust backwards if it is better
    // And not at all if angle is too close to being counter-productive
    // 
    // 
    // Calculate velocity change needed to correct course
}

void Enemy::update()
{
    location = location + velocity;
    enemySprite->x = location.x;
    enemySprite->y = location.y;
}

void Enemy::render()
{
    enemySprite->render();
}
