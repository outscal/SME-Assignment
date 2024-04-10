#include "../../header/Enemy/EnemyController.h"
#include "../../header/Enemy/EnemyView.h"
#include "../../header/Enemy/EnemyModel.h"
#include "../../header/Enemy/EnemyConfig.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Entity/EntityConfig.h"
#include "../../header/Player/PlayerController.h"
#include "../../header/Particle/ParticleSystem.h"
#include "../../header/Sound/SoundService.h"

namespace Enemy
{
	using namespace Global;
	using namespace Time;
	using namespace Collision;
	using namespace Entity;
	using namespace Player;
	using namespace Sound;

	EnemyController::EnemyController(EnemyType type)
	{
		enemy_view = new EnemyView();
		enemy_model = new EnemyModel(type);
	}

	EnemyController::~EnemyController()
	{
		delete (enemy_view);
		delete (enemy_model);
	}

	void EnemyController::initialize()
	{
		enemy_model->initialize();
		enemy_model->setEnemyPosition(getRandomInitialPosition());
		enemy_view->initialize(this);
		bulletCooldown = 1.0f;
	}

	void EnemyController::fireBullet()
	{
		if (elapsedBulletCooldown < bulletCooldown)
		{
			// Still cooling down, cannot fire yet
			return;
		}

		// Create a new bullet
		Bullet::Bullet* bullet = new Bullet::Bullet();

		// Set position based on enemy's position
		bullet->setPosition(getEnemyPosition());

		// Set velocity for the bullet
		// Example velocity: (5.f, 0.f) for a bullet moving horizontally to the right
		bullet->setVelocity(sf::Vector2f(5.f, 0.f));

		// Add the bullet to the enemyBullets vector
		enemyBullets.push_back(bullet);

		// Reset the cooldown timer
		elapsedBulletCooldown = 0.f;
	}

	void EnemyController::updateEnemyBullets()
	{
		// Update position of each bullet
		for (auto it = enemyBullets.begin(); it != enemyBullets.end();)
		{
			(*it)->update(); // Update bullet position

			// Check if bullet is out of bounds
			if ((*it)->isOutOfBounds(*ServiceLocator::getInstance()->getGraphicService()->getGameWindow()))
			{
				delete (*it); // Free memory for the bullet
				it = enemyBullets.erase(it); // Remove bullet from vector
			}
			else
			{
				++it;
			}
		}
	}

	void EnemyController::update()
	{
		move();
		enemy_view->update();
		handleOutOfBounds();
		updateEnemyBullets();
	}

	void EnemyController::render()
	{
		enemy_view->render();
	}

	sf::Vector2f EnemyController::getRandomInitialPosition()
	{
		float x_offset_distance = (std::rand() % static_cast<int>(enemy_model->right_most_position.x - enemy_model->left_most_position.x));
		float x_position = enemy_model->left_most_position.x + x_offset_distance;
		float y_position = enemy_model->left_most_position.y;

		return sf::Vector2f(x_position, y_position);
	}

	void EnemyController::handleOutOfBounds()
	{
		sf::Vector2f enemyPosition = getEnemyPosition();
		sf::Vector2u windowSize = ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize();

		if (enemyPosition.x < 0 || enemyPosition.x > windowSize.x ||
			enemyPosition.y < 0 || enemyPosition.y > windowSize.y) 
		{
			ServiceLocator::getInstance()->getEnemyService()->destroyEnemy(this);
		}
	}

	sf::Vector2f EnemyController::getEnemyPosition()
	{
		return enemy_model->getEnemyPosition();
	}

	EnemyState EnemyController::getEnemyState()
	{
		return enemy_model->getEnemyState();
	}

	EnemyType EnemyController::getEnemyType()
	{
		return enemy_model->getEnemyType();
	}

	const sf::Sprite& EnemyController::getColliderSprite()
	{
		return enemy_view->getEnemySprite();
	}

	void EnemyController::onCollision(ICollider* other_collider)
	{
		PlayerController* player_controller = dynamic_cast<PlayerController*>(other_collider);
		if (player_controller)
		{
			processScore();
			destroy();
			return;
		}
	}

	void EnemyController::processScore()
	{
		ServiceLocator::getInstance()->getPlayerService()->increaseEnemiesKilled(1);
	}

	void EnemyController::destroy()
	{
		ServiceLocator::getInstance()->getParticleService()->spawnParticleSystem(enemy_model->getEnemyPosition(),
			Particle::ParticlesType::EXPLOSION);

		ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::EXPLOSION);
		ServiceLocator::getInstance()->getEnemyService()->destroyEnemy(this);
	}
}