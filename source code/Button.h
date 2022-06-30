#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Mouse.hpp>

class Button : public sf::Drawable
{
public:
	Button(float x, float y, const sf::Texture &texture);

	void update(float deltaTime);
	void updateOnMouseMove(int mouseX, int mouseY);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setTexture(const sf::Texture &texture);

	bool isPressed(int mouseX, int mouseY, sf::Mouse::Button button) const;
private:
	enum class State : uint8_t
	{
		None,
		Expand,
		Shrink
	};

	State state_;

	sf::Sprite sprite_;
	float x_;
	float y_;
	float width_;
	float height_;
	float scale_;
	float velScale_;
	float minScale_;
	float maxScale_;

	bool isHovered_;
};