#include "MainCharacter.h"

MainCharacter::MainCharacter(const sf::Texture& texture)
	:Entity(texture, 3),
	m_try_jump(false),
	m_try_catch_wall(false),
	m_current_state(IdleRight),
	m_is_hited(false),
	m_double_jump(false),
	m_on_wall(false)
{
	m_animation.addAnimation(IdleLeft, Animation::AnimationData({ 32,32 * 0,-32,32 }, sf::milliseconds(50), 11));
	m_animation.addAnimation(IdleRight, Animation::AnimationData({ 0,32 * 0,32,32 }, sf::milliseconds(50), 11));
	m_animation.addAnimation(MoveLeft, Animation::AnimationData({ 32,32 * 1,-32,32 }, sf::milliseconds(50), 12));
	m_animation.addAnimation(MoveRight, Animation::AnimationData({ 0,32 * 1,32,32 }, sf::milliseconds(50), 12));
	m_animation.addAnimation(JumpLeft, Animation::AnimationData({ 32,32 * 2,-32,32 }, sf::milliseconds(50), 1, false));
	m_animation.addAnimation(JumpRight, Animation::AnimationData({ 0,32 * 2,32,32 }, sf::milliseconds(50), 1, false));
	m_animation.addAnimation(FallLeft, Animation::AnimationData({ 32,32 * 3,-32,32 }, sf::milliseconds(50), 1, false));
	m_animation.addAnimation(FallRight, Animation::AnimationData({ 0,32 * 3,32,32 }, sf::milliseconds(50), 1, false));
	m_animation.addAnimation(HitLeft, Animation::AnimationData({ 32,32 * 4,-32,32 }, sf::milliseconds(50), 7, false));
	m_animation.addAnimation(HitRight, Animation::AnimationData({ 0,32 * 4,32,32 }, sf::milliseconds(50), 7, false));
	m_animation.addAnimation(DieLeft, Animation::AnimationData({ 32 * 7,32 * 5,-32,-32 }, sf::milliseconds(50), 1, false));
	m_animation.addAnimation(DieRight, Animation::AnimationData({ 32 * 6,32 * 5,32,-32 }, sf::milliseconds(50), 1, false));
	m_animation.addAnimation(WallJumpLeft, Animation::AnimationData({ 32,32 * 6,-32,32 }, sf::milliseconds(50), 5));
	m_animation.addAnimation(WallJumpRight, Animation::AnimationData({ 0,32 * 6,32,32 }, sf::milliseconds(50), 5));

	m_animation.setAnimation(m_current_state);
}

void MainCharacter::update(sf::Time dt)
{

	Entity::update(dt);

	if (getOnGround())
	{
		m_double_jump = true;
	}

	if (m_on_wall)
	{
		m_acceleration.y = 0.f;
		m_velocity.y = 0.f;		
		if (m_velocity.x != 0.f)
		{
			m_double_jump = true;
			m_on_wall = false;
		}
			
	}

	if (m_try_jump)
	{
		if (getOnGround())
		{
			setOnGround(false);
			m_velocity.y = -350.f;
		}	
		else if (m_double_jump && m_velocity.y>0.f)
		{

			m_velocity.y =- 300.f;
			m_double_jump = false;
		}
	}
	m_try_jump = false;
	m_try_catch_wall = false;
	//setOnGround(false);
	m_velocity.x = 0.f;
	if (m_is_hited)
		m_velocity.x = m_current_state & 1 ? -100.f : 100.f;

}

void MainCharacter::jump()
{
	m_try_jump = !m_is_hited;
}

void MainCharacter::moveLeft()
{
	if (!m_is_hited && isAlive())
		addVelocity(sf::Vector2f(-100.f, 0.f));
}

void MainCharacter::moveRight()
{
	if (!m_is_hited && isAlive())
		addVelocity(sf::Vector2f(100.f, 0.f));
}

void MainCharacter::moveUp()
{
	addVelocity(sf::Vector2f(0.f, -100.f));
}

void MainCharacter::moveDown()
{
	addVelocity(sf::Vector2f(0.f, 100.f));
}

void MainCharacter::catchWall()
{
	m_try_catch_wall = !m_is_hited;
}





sf::FloatRect MainCharacter::getGlobalBounds() const
{
	//return sf::FloatRect(getPosition(), sf::Vector2f(96, 96));
	return sf::FloatRect(getPosition() + sf::Vector2f(7.f, 4.f), sf::Vector2f(18.f, 28.f));
}

void MainCharacter::setState()
{
	States new_state = m_current_state;


	if (m_is_hited)
	{
		if (m_state_time < sf::seconds(1))
			new_state = (States)(HitLeft | m_dir);
		else
			m_is_hited = false;
	}
	else if (!isAlive())
	{
		new_state = (States)(DieLeft | (new_state & 1));
		m_is_hited = false;
	}
	else if(m_on_wall)
	{
		new_state = (States)((WallJumpLeft) | (new_state & 1));
	}
	else
	{
		if (m_velocity.x < -0.001)
			new_state = MoveLeft;
		else if (m_velocity.x > 0.001)
			new_state = MoveRight;
		else
			new_state = (States)(IdleLeft | (new_state & 1));

		if (!getOnGround())
			new_state = (States)((m_velocity.y > 0 ? FallLeft : JumpLeft) | (new_state & 1));
	}


	if (new_state != m_current_state)
	{
		m_current_state = new_state;
		m_animation.setAnimation(m_current_state);
		m_state_time = sf::Time::Zero;
	}
}



void MainCharacter::hit(int lives, float dir)
{
	
		//m_current_state = m_current_state|
	Entity::hit(lives);
	if (dir < 0)
		m_dir = 1;
	else
		m_dir = 0;
	m_is_hited = true;
	m_state_time = sf::Time::Zero;

	if (!getOnGround())
		m_velocity.y = 0;
	m_velocity.y -= 300;
	//m_velocity.x = 0;
	
}

void MainCharacter::reactOnCollision(const Collision::ContactData& contact_data)
{
	if (contact_data.contact_normal.y < 0)
		setOnGround(true);
	
	if (!getOnGround() && !m_is_hited && isAlive() && m_try_catch_wall &&
		contact_data.contact_normal.x != 0.f)
	{
		m_on_wall = true;
		if (contact_data.contact_normal.x > 0)
		{

		}
	}
}

void MainCharacter::colisionWithPlayer(Entity* player, const Collision::ContactData& contact_data)
{
}
