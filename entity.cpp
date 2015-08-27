#include "entity.hpp"

Entity::Entity()
    : _texture()
{

}

void Entity::load(std::string texturefilename)
{
    _texture.loadFromFile(texturefilename);
    this->setTexture(_texture);
    this->setOrigin(this->getGlobalBounds().width/2, this->getGlobalBounds().height/2);
}

Entity::~Entity()
{
    delete this;
}

