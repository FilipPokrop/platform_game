#include "World.h"

World::World(sf::RenderWindow* window, const TextureHolder& texture_holder)
	:m_window(window),
    m_texture_holder(texture_holder),
	m_player(texture_holder.get(Textures::Player)),
	m_map(texture_holder.get(Textures::Map)),
    m_lives(texture_holder.get(Textures::WorldGui)),
    m_view(sf::FloatRect(sf::Vector2f(0,0),m_map.getScreenSize()))
{
    Duck* duck = new Duck(texture_holder.get(Textures::Duck));
    duck->setPosition(170, 332);
    m_enemis.push_back(duck);
    duck = new Duck(m_texture_holder.get(Textures::Duck));
    duck->setPosition(70, 428);
    m_enemis.push_back(duck);
    //m_view.setViewport(sf::FloatRect(0.f, 0.f, 2.f, 2.f));
}

World::~World()
{
    for (auto iter = m_enemis.begin(); iter != m_enemis.end(); iter ++)
    {
        delete* iter;
    }
}

void World::update(const sf::Time& dt)
{
    checkCollisionPlayerVsEnemy(dt);
    checkCollisionPlayerVsMap(dt);
	m_player.update(dt);
    if (!m_enemis.empty())
    {
        for (auto iter = m_enemis.begin(); iter != m_enemis.end();)
        {
            (*iter)->update(dt);
            if (!(*iter)->isAlive())
            {
                delete* iter;
                iter = m_enemis.erase(iter);
                //if (iter == m_enemis.end())
                    //break;
            }
            else
            {
                iter++;
            }
        }
    }
    

	m_map.update(m_player.getCenter());
    m_lives.update(m_player.getLives());

}

void World::draw()
{
    m_view.setCenter(m_map.getCenter());
    m_window->setView(m_view);
	m_window->draw(m_map);
    if (!m_enemis.empty())
    {
        for (auto iter = m_enemis.begin(); iter != m_enemis.end(); iter++)
        {
            m_window->draw(**iter);
        }
    }
    
	m_window->draw(m_player);
    m_window->setView(m_window->getDefaultView());
    m_window->draw(m_lives);
}

bool World::handleEvent(const sf::Event& event)
{
 //   switch (event.type)
 //   {
 //   case sf::Event::KeyPressed:
 //       switch (event.key.code)
 //       {
 //       

 //       default:
 //           return false;
 //           break;
 //       }
 //       break;

 //   case sf::Event::KeyReleased:
 //       switch (event.key.code)
 //       {

 //       default:
 //           return false;
 //           break;
 //       }
 //       break;
 //   default:
 //       return false;
 //       break;


 //   }
	//return true;
    return false;
}

void World::handleEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_player.jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_player.moveRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_player.moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	    m_player.jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_player.moveDown();
}

void World::checkCollisionPlayerVsMap(const sf::Time& dt)
{
    m_player.setOnGround(false);
    sf::Vector2f old_left_top = m_player.getPosition();
    auto bounds = m_player.getGlobalBounds();

    sf::Vector2f old_right_down(bounds.left + bounds.width, bounds.top + bounds.height);
    sf::Vector2f dir = m_player.getDirection(dt);

    sf::Vector2f new_left_top = old_left_top + dir;
    sf::Vector2f new_right_down = old_right_down + dir;

    sf::FloatRect area;
    area.left = std::min(old_left_top.x, new_left_top.x);
    area.top = std::min(old_left_top.y, new_left_top.y);
    area.width = std::max(old_right_down.x, new_right_down.x) - area.left;
    area.height = std::max(old_right_down.y, new_right_down.y) - area.top;

    std::vector<sf::FloatRect> rects = m_map.getData().getRectFromArea(area);

    std::vector<std::pair<float, sf::FloatRect>> colide_rect;
    for (auto& r : rects)
    {
        Colision::ContactData col = Colision::dynamicRectvsRect(m_player, r, dt);
        if (col)
        {
            colide_rect.push_back(std::make_pair(col.contact_time, r));
        }
    }
   
    std::sort(colide_rect.begin(), colide_rect.end(), [](std::pair<float, sf::FloatRect>& a, std::pair<float, sf::FloatRect>& b)
        {
            return a.first < b.first;
        });

    for (auto& i : colide_rect)
    {
        //std::cout << i.second.left/32 << " " << i.second.top / 32 << "; ";
        Colision::resolveDynamicRectvsRect(m_player, i.second, dt);
    }
}

void World::checkCollisionPlayerVsEnemy(const sf::Time& dt)
{
    
    for (auto iter = m_enemis.begin(); iter != m_enemis.end(); iter++)
    {
        Colision::ContactData data = Colision::dynamicRectvsDynamicRect(**iter, m_player, dt);
        (*iter)->colisionWithPlayer(&m_player, data);
    }
}
