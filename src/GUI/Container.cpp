#include "GUI/Container.hpp"

Container::Container()
{
  sf::VideoMode vm = sf::VideoMode::getDesktopMode();
  size = sf::Vector2f(600.f, 140.f);
  position = sf::Vector2f(vm.width / 2, vm.height - size.y / 2);

  container.setFillColor(sf::Color(50, 50, 50, 200));
  container.setSize(size);
  container.setOrigin(size.x / 2, size.y / 2);
  container.setPosition(position);
}

void Container::createLayout(const int &rowHeight, const sf::Vector2f& padding)
{

  int numRows = size.y / rowHeight;
  int rowWidth = size.x / 2;
  int numCols = 2;

  sf::Vector2f containerTopLeft = sf::Vector2f(position.x - (size.x / 2) + padding.x, position.y - (size.y / 2) + padding.y);
  for (int y = 0; y < numRows; y++) {
    for (int x = 0; x < numCols; x++) {
      sf::Vector2f pos = sf::Vector2f(containerTopLeft.x + rowWidth * x, containerTopLeft.y + rowHeight * y);

      sf::Text contentText;
      contentText.setFont(*ResourceManager::getFont("fonts/arial.ttf"));
      contentText.setCharacterSize(20);
      contentText.setFillColor(sf::Color::White);
      contentText.setPosition(pos);

      contents.push_back(contentText);
    }
  }
}

void Container::update(const std::vector<std::string> &values)
{
  int i = 0;
  for (int i =0; i < values.size(); i++)
  {
    contents[i].setString(values[i]);
  }
}

void Container::render(sf::RenderTarget &target)
{
  target.draw(container);
  for (sf::Text content : contents) {
    target.draw(content);
  }
}
