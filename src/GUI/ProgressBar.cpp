#include "GUI/ProgressBar.hpp"

ProgressBar::ProgressBar(sf::Vector2f position, sf::Vector2f size, sf::Color inner_color)
{
	back.setPosition(position);
	back.setSize(size);
	back.setFillColor(sf::Color(50, 50, 50, 200));

	inner.setPosition(position);
	inner.setSize(size);
	inner.setFillColor(inner_color);

	text.setFont(*ResourceManager::getFont("fonts/arial.ttf"));
	text.setCharacterSize(static_cast<unsigned>(size.y) / 2);
	text.setFillColor(sf::Color::White);
}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::update(const int current_value, const int max_value)
{
	if (current_value < 0)
		return;
		
	float percent = static_cast<float>(current_value) / static_cast<float>(max_value);
	float scale = back.getGlobalBounds().width / max_value;

	inner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(max_value * percent * scale)),
			inner.getSize().y
		)
	);

	barString = std::to_string(current_value) + " / " + std::to_string(max_value);
	text.setString(barString);

	sf::FloatRect barBounds = back.getGlobalBounds();
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setPosition(
		barBounds.left + (barBounds.width / 2) - (textBounds.width / 2),
		barBounds.top + (barBounds.height / 2) - (textBounds.height / 1.3)
	);
}

void ProgressBar::render(sf::RenderTarget & target)
{
	target.draw(back);
	target.draw(inner);
	target.draw(text);
}