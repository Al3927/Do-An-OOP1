#include "stdafx.h"
#include "Gui.h"

const float gui::p2pX(const float perc, const sf::VideoMode& vm)
{
	/*
	 * Converts a percentage value to pixels relative to the current resolution in the x-axis.
	 *
	 * @param		float perc				The percentage value.
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 *
	 * @return		float					The calculated pixel value.
	 */

	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float perc, const sf::VideoMode& vm)
{
	/*
	 * Converts a percentage value to pixels relative to the current resolution in the y-axis.
	 *
	 * @param		float perc				The percentage value.
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 *
	 * @return		float					The calculated pixel value.
	 */

	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
	/*
	 * Calculates the character size for text using the current resolution and a constant.
	 *
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 * @param		unsigned modifier		Used to modify the character size in a more custom way.
	 *
	 * @return		unsigned				The calculated character size value.
	 */

	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	std::cout << this->text.getGlobalBounds().width << "\n";
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button()
{

}

//Accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned & gui::Button::getId() const
{
	return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//Functions
void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
