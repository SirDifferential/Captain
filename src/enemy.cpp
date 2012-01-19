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
    Vector3 playerCoords = manager.getRoomMgr()->giveCurrentRoom()->getPlayerShip()->getLocation();
    Vector3 playerVelocity = manager.getRoomMgr()->giveCurrentRoom()->getPlayerShip()->getVelocity();
    Vector3 distanceToPlayer;
    distanceToPlayer.x = playerCoords.x - location.x;
    distanceToPlayer.y = playerCoords.y - location.y;

    // Placeholder: Accelerate towards angle alpha
    float targetAngle = atan(distanceToPlayer.x / distanceToPlayer.y);

    // Figure out the unit circle sign. Damn I hate calculating these. Is there a better way?
    if (distanceToPlayer.x >= 0 && distanceToPlayer.y >= 0)
    {
        // 0 - 90 degrees, 0 - pi/2
        // atan returns the correct angle directly
    }
    else if (distanceToPlayer.x >= 0 && distanceToPlayer.y < 0)
    {
        // 90 - 180 degrees, pi/2 - pi
        // atan returns -pi/2 - 0 when going clockwise
        // fixedAngle is 1.57079 if we are barely on the bottom-right part of the unit circle
        // and 3.14159 if we are at the bottom center
        float fixedAngle = 3.14159 + targetAngle;
        // This could be done in one line, buuuut...
        targetAngle = fixedAngle;
    }
    else if (distanceToPlayer.x < 0 && distanceToPlayer.y < 0)
    {
        // 180 - 270 degrees, pi/2 - 3/2 * pi
        // atan returns 0 - pi/2 when going clockwise
        // fixedAngle is 3.14159 if we are the bottom
        // and 4.71239 if we are at middle left
        float fixedAngle = 3.14159 + targetAngle;
        targetAngle = fixedAngle;
    }
    else if (distanceToPlayer.x < 0 && distanceToPlayer.y > 0)
    {
        // 270 - 360 degrees, 3/2 * pi - 2*pi
        // atan returns -pi/2 - 0 when going clockwise
        // fixedAngle is 6.28319 if we are at the top
        // and 4.71239 if we are at middle left
        float fixedAngle = 6.28319 + targetAngle;
        targetAngle = fixedAngle;
    }
    else
    {
        fprintf(stderr, "Mathematics broke, y u break universe?\n");
        fprintf(stderr, "distance X: %f, distance Y: %f\n", distanceToPlayer.x, distanceToPlayer.y);
    }

    fprintf(stderr, "distance X: %f distance Y: %f\n", distanceToPlayer.x, distanceToPlayer.y);
    fprintf(stderr, "target angle: %f\n", targetAngle);
    fprintf(stderr, "degrees: %f\n", targetAngle*(180/3.14159));

    // See whether it is faster to face the enemy via rotating to left or rotating to right
    float rotationDelta = targetAngle - shipRotation;

    // If rotationDelta is larger than 3.14159, it is faster to turn the other way
    if (rotationDelta > 3.14159f)
        rotationDelta = (6.28319f - targetAngle + shipRotation)*-1;

    fprintf(stderr, "Rotation delta: %f\n", rotationDelta);
    fprintf(stderr, "Ship rotation: %f\n", shipRotation);

    if (rotationDelta > 0.01f)
    {
        rotateLeft();
    }
    else if (rotationDelta < -0.01f)
    {
        rotateRight();
    }
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
    velocity.x += -1*sin(shipRotation)*thrust;
    velocity.y += cos(shipRotation)*thrust;
}

void Enemy::decelerate()
{
    velocity.x -= -1*sin(shipRotation)*thrust;
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
    shipRotation += 0.01f;
    if (shipRotation > 6.28318)  // Radians
        shipRotation = 0.0f;
    shipRotation = abs(shipRotation);
    enemySprite->rotation = shipRotation*(180/3.14159);    // Sprite rotation in degrees
}

void Enemy::rotateRight()
{
    shipRotation -= 0.01;
    if (shipRotation > 6.28318)
        shipRotation = 0.0f;
    shipRotation = abs(shipRotation);
    enemySprite->rotation = shipRotation*(180/3.14159);
}

void Enemy::strafeLeft()
{
    Vector3 normal_vector;
    normal_vector.x = -1*directional_thruster_power * cos(shipRotation);
    normal_vector.y = -1*directional_thruster_power * sin(shipRotation);
    velocity += normal_vector;
}

void Enemy::strafeRight()
{
    Vector3 normal_vector;
    normal_vector.x = directional_thruster_power * cos(shipRotation);
    normal_vector.y = directional_thruster_power * sin(shipRotation);
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
