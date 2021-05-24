#include "meteor.h"
#include "Explosion.h"
#include "GameScene.h"

sf::FloatRect Meteor::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

void Meteor::handleCollision(GameObject& otherGameObject)
{
	if (otherGameObject.hasTag("laser"))
	{
		sf::Vector2f pos = sprite_.getPosition();
		float x = pos.x;
		float y = pos.y;
		sf::FloatRect bounds = sprite_.getGlobalBounds();

		float explosionX = x + (bounds.width / 2.0f);
		float explosionY = y + (bounds.height / 2.0f);

		ExplosionPtr explosion = std::make_shared<Explosion>(sf::Vector2f(explosionX, explosionY));
		GAME.getCurrentScene().addGameObject(explosion);
		otherGameObject.makeDead();

		GameScene& scene = (GameScene&)GAME.getCurrentScene();
		scene.increaseScore();
	}

	makeDead();
}
const float SPEED = 0.25f;

Meteor::Meteor(sf::Vector2f pos)
{
	sprite_.setTexture(GAME.getTexture("Resources/meteor.png"));
	sprite_.setPosition(pos);
	assignTag("meteor");
	setCollisionCheckEnabled(true);

}

void Meteor::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Meteor::update(sf::Time& elapsed) {
	int msElapsed = elapsed.asMilliseconds();
	sf::Vector2f pos = sprite_.getPosition();

	if (pos.x < sprite_.getGlobalBounds().width * -1)
	{
		GameScene& scene = (GameScene&)GAME.getCurrentScene();
		scene.decreaseLives();

		makeDead();
	}
	else
	{
		sprite_.setPosition(sf::Vector2f(pos.x - SPEED * msElapsed, pos.y));
	}
}