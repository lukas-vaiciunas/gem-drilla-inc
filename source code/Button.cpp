#include "Button.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Button::Button(float x, float y, const sf::Texture &texture) :
	sf::Drawable(),
	state_(State::None),
	sprite_(texture),
	x_(x),
	y_(y),
	width_(static_cast<float>(texture.getSize().x)),
	height_(static_cast<float>(texture.getSize().y)),
	scale_(1.0f),
	velScale_(0.8f),
	minScale_(1.0f),
	maxScale_(1.2f),
	isHovered_(false)
{
	sprite_.setPosition(x, y);
}

void Button::update(float deltaTime)
{
	if (!isHovered_) return;

	switch (state_)
	{
		case State::Expand:
			scale_ += velScale_ * deltaTime;
			if (scale_ >= maxScale_)
			{
				scale_ = maxScale_;
				state_ = State::Shrink;
			}
			break;
		case State::Shrink:
			scale_ -= velScale_ * deltaTime;
			if (scale_ <= minScale_)
			{
				scale_ = minScale_;
				state_ = State::Expand;
			}
			break;
	}
}

void Button::updateOnMouseMove(int mouseX, int mouseY)
{
	const float scaleRatio = 1.0f / Config::globalScale;
	const float relMouseX = mouseX * scaleRatio;
	const float relMouseY = mouseY * scaleRatio;

	bool wasHovered = isHovered_;

	isHovered_ = (relMouseX >= x_
		&& relMouseX < x_ + width_
		&& relMouseY >= y_
		&& relMouseY < y_ + height_);

	if (wasHovered && !isHovered_)
	{
		state_ = State::None;
		scale_ = 1.0f;
	}
	else if (!wasHovered && isHovered_)
	{
		state_ = State::Expand;
	}
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(scale_, scale_, x_ + width_ * 0.5f, y_ + height_ * 0.5f);

	target.draw(sprite_, states);
}

void Button::setTexture(const sf::Texture &texture)
{
	sprite_.setTexture(texture);
}

bool Button::isPressed(int mouseX, int mouseY, sf::Mouse::Button button) const
{
	return button == sf::Mouse::Button::Left
		&& isHovered_;
}