#include "World.h"


World::World(sf::RenderWindow* window, const TextureHolder& texture_holder)
    :m_window(window),
    m_texture_holder(texture_holder),
    m_main_character(nullptr),
    m_map(nullptr),
    m_lives(texture_holder.get(Textures::WorldGui)),
    m_view(),
    m_player("media/config/key.conf")
{
    m_main_character = new MainCharacter(m_texture_holder.get(Textures::Player));
    m_map = new TileMap(m_texture_holder.get(Textures::Map));
    m_view.reset(sf::FloatRect(sf::Vector2f(0, 0), m_map->getScreenSize()));
    Duck* duck = new Duck(texture_holder.get(Textures::Duck));
    duck->setPosition(170, 332);
    m_enemis.push_back(duck);
    duck = new Duck(m_texture_holder.get(Textures::Duck));
    duck->setPosition(70, 428);
    m_enemis.push_back(duck);
    duck = new Duck(m_texture_holder.get(Textures::Duck));
    duck->setPosition(667, 460);
    m_enemis.push_back(duck);

    Slime* slime = new Slime(m_texture_holder.get(Textures::Slime));
    slime->setPosition(sf::Vector2f(400, 466));
    slime->setLeftBorder(*m_map);
    slime->setRightBorder(*m_map);
    m_enemis.push_back(slime);
    slime = new Slime(m_texture_holder.get(Textures::Slime));
    slime->setPosition(sf::Vector2f(400, 66));
    slime->setLeftBorder(*m_map);
    slime->setRightBorder(*m_map);
    m_enemis.push_back(slime);
    //m_view.setViewport(sf::FloatRect(0.f, 0.f, 2.f, 2.f));
}

World::~World()
{
    for (auto iter = m_enemis.begin(); iter != m_enemis.end(); iter ++)
    {
        delete* iter;
    }

    delete m_main_character;
    delete m_map;
}

void World::update(const sf::Time& dt)
{
    //if (endGame())
    //    m_window->close();
    if (m_main_character->isAlive())
    {
        checkCollisionPlayerVsEnemy(dt);
        checkCollisionPlayerVsMap(dt);
    }
    
	m_main_character->update(dt);
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
    

	m_map->update(m_main_character->getCenter());
    m_lives.update(m_main_character->getLives());

}

void World::draw()
{
    m_view.setCenter(m_map->getCenter());
    m_window->setView(m_view);
	m_window->draw(*m_map);
    if (!m_enemis.empty())
    {
        for (auto iter = m_enemis.begin(); iter != m_enemis.end(); iter++)
        {
            m_window->draw(**iter);
        }
    }
    
	m_window->draw(*m_main_character);
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

bool World::handleEvents()
{
    m_player.handleEvents(m_main_character);
    return true;
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_player->moveDown();*/
}

void World::checkCollisionPlayerVsMap(const sf::Time& dt)
{
    m_main_character->setOnGround(false);
    sf::Vector2f old_left_top = m_main_character->getPosition();
    auto bounds = m_main_character->getGlobalBounds();

    sf::Vector2f old_right_down(bounds.left + bounds.width, bounds.top + bounds.height);
    sf::Vector2f dir = m_main_character->getDirection(dt);

    sf::Vector2f new_left_top = old_left_top + dir;
    sf::Vector2f new_right_down = old_right_down + dir;

    sf::FloatRect area;
    area.left = std::min(old_left_top.x, new_left_top.x);
    area.top = std::min(old_left_top.y, new_left_top.y);
    area.width = std::max(old_right_down.x, new_right_down.x) - area.left;
    area.height = std::max(old_right_down.y, new_right_down.y) - area.top;

    std::vector<sf::FloatRect> rects = m_map->getData().getRectFromArea(area);

    std::vector<std::pair<float, sf::FloatRect>> colide_rect;
    for (auto& r : rects)
    {
        Collision::ContactData col = Collision::dynamicRectvsRect(*m_main_character, r, dt);
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
        Collision::resolveDynamicRectvsRect(*m_main_character, i.second, dt);
    }
}

void World::checkCollisionPlayerVsEnemy(const sf::Time& dt)
{
    
    for (auto iter = m_enemis.begin(); iter != m_enemis.end(); iter++)
    {
        Collision::ContactData data = Collision::dynamicRectvsDynamicRect(**iter, *m_main_character, dt);
        (*iter)->colisionWithPlayer(m_main_character, data);
    }
}

bool World::endGame()
{
    return m_main_character->getPosition().y > m_map->getWorldSize().y + m_map->getScreenSize().y;
}
