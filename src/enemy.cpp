#include "enemy.hpp"
#include "sprite.hpp"
#include "manager.hpp"
#include "roommanager.hpp"
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

    velocity_max = 2.5f;
    directional_thruster_power = 0.01f;
    thrust = 0.005f;
    shipRotation = 0.0f;
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
    // TODO: Move the following stuff into something like ramEnemyShip(Vector3 enemyLoc, Vector3 enemyVel);
    // Placeholder: attempt to ram player. Can be modified for "travel to coords (x,y)"
    boost::shared_ptr<Ship> playerShip = manager.getRoomMgr()->giveCurrentRoom()->getPlayerShip();
    Vector3 playerCoords = playerShip->getLocation();
    Vector3 playerVelocity = playerShip->getVelocity();
    Vector3 distanceToPlayer;
    float distance_to_player = abs(sqrt( (playerCoords.x*playerCoords.x) + (playerCoords.y*playerCoords.y) ));
    distanceToPlayer.x = playerCoords.x - location.x;
    distanceToPlayer.y = playerCoords.y - location.y;
    
    // What is the angle between this ship and the player ship?
    float angle = 0.0f;
    angle = atan(distanceToPlayer.x / distanceToPlayer.y);
    if (distanceToPlayer.x <= 0 && distanceToPlayer.y >= 0)
    {
        angle = 6.28318f - (-1*angle);
    } else if (distanceToPlayer.x > 0 && distanceToPlayer.y > 0)
    {
        angle = angle;
    } else if (distanceToPlayer.x < 0 && distanceToPlayer.y < 0)
    {
        angle = 3.14159 + angle;
    } else if (distanceToPlayer.x > 0 && distanceToPlayer.y < 0)
    {
        angle = 3.14159 - (-1*angle);
    } else
    {
        fprintf(stderr, "Odd location at enemy think()\n");
    }

    // Figure out which is the fastest way to face the enemy

    // How much the ship has to turn to face zero? These are both positive as they are used
    // For figuring out what is the shortest path. Of course, turning left causes the rotation to be negative
    float distance_to_zero_via_right = 6.28318f - shipRotation;
    float distance_to_zero_via_left = shipRotation;

    float enemy_distance_to_zero_via_right = 6.28318f - angle;
    float enemy_distance_to_zero_via_left = angle;
    float rotational_distance = 0.0f;

    if (shipRotation+0.1 > angle)
    {
        float distance_by_turning_left = shipRotation - angle;
        float distance_by_turning_right_via_zero = distance_to_zero_via_right + enemy_distance_to_zero_via_left;

        if (distance_by_turning_left < distance_by_turning_right_via_zero)
        {
            rotational_distance = distance_by_turning_left;
            rotateLeft();
        }
        else
        {
            rotational_distance = distance_by_turning_right_via_zero;
            rotateRight();
        }
    } else if (shipRotation-0.1 < angle)
    {
        float distance_by_turning_right = angle - shipRotation;
        float distance_by_turning_left_via_zero = distance_to_zero_via_left + enemy_distance_to_zero_via_right;
        
        if (distance_by_turning_right < distance_by_turning_left_via_zero)
        {
            rotational_distance = distance_by_turning_right;
            rotateRight();
        }
        else
        {
            rotational_distance = distance_by_turning_left_via_zero;
            rotateLeft();
        }
    }

    if (distance_to_player > 3.0)
        accelerate();
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

void Enemy::accelerate()
{
    velocity.x += sin(shipRotation)*thrust;
    velocity.y += cos(shipRotation)*thrust;
}

void Enemy::decelerate()
{
    velocity.x -= sin(shipRotation)*thrust;
    velocity.y -= cos(shipRotation)*thrust;
}

void Enemy::stop()
{
    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;
}

void Enemy::rotateLeft()
{
    if (shipRotation < 0.0f)  // Radians
        shipRotation = 6.28318f;
    shipRotation -= 0.01f;
    if (shipRotation < 0.0f)  // Radians
        shipRotation = 6.28318f;
    enemySprite->rotation = shipRotation*(180/3.14159)*-1;    // Sprite rotation in degrees
}

void Enemy::rotateRight()
{
    if (shipRotation > 6.28318f)
        shipRotation = 0.0f;
    shipRotation += 0.01f;
    if (shipRotation > 6.28318f)
        shipRotation = 0.0f;
    
    enemySprite->rotation = shipRotation*(180/3.14159)*-1;
}

void Enemy::strafeLeft()
{
    Vector3 normal_vector;
    normal_vector.x = -1*directional_thruster_power * cos(shipRotation);
    normal_vector.y = directional_thruster_power * sin(shipRotation);
    velocity += normal_vector;
}

void Enemy::strafeRight()
{
    Vector3 normal_vector;
    normal_vector.x = directional_thruster_power * cos(shipRotation);
    normal_vector.y = -1*directional_thruster_power * sin(shipRotation);
    velocity += normal_vector;
}

void Enemy::resetAllVectors()
{
    location.x = 0;
    location.y = 0;
    location.z = 0;

    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;
}
