#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

bool
load_text (sf::Font &font, sf::Text &text)
{

  if (!font.loadFromFile ("../Arial.ttf"))
    {
      return false;
    }
  text.setCharacterSize (40);
  text.setFillColor (sf::Color::Red);

  text.setString ("Click Cartman and see what happens!");
  text.setFont (font);
  return true;
}
bool
load_sprite (sf::Texture &texture, sf::Sprite &sprite)
{

  if (!texture.loadFromFile ("../EricCartman.png"))
    {
      return false;
    }
  sprite.setTexture (texture);
  sprite.setPosition (300, 300);
  return true;
}
bool
load_sound (sf::SoundBuffer &buffer, sf::Sound &sound)
{
  sf::Texture texture;

  if (!buffer.loadFromFile ("../cartman.ogg"))
    {
      return false;
    }
  sound.setBuffer (buffer);
  return true;
}

int
main (int argc, char **argv)
{
  bool is_clicked = false;
  sf::Text text;

  sf::Clock click_timer;
  sf::RenderWindow window (sf::VideoMode ({ 1000, 1000 }), "!Cartman!");
  sf::Sprite sprite;
  sf::Sound sound;
  sf::Texture texture;
  sf::SoundBuffer soundBuffer;
  sf::Font font;

  bool is_ok = load_text (font, text) && load_sprite (texture, sprite)
               && load_sound (soundBuffer, sound);
  if (!is_ok)
    {
      std::cout << "failed to load assets";
      return 1;
    }
  while (window.isOpen ())
    {
      sf::Event event;
      while (window.pollEvent (event))
        {
          if (event.type == sf::Event::Closed)
            window.close ();
          if (event.type == sf::Event::MouseButtonPressed)
            {
              sf::Vector2i clickPos = sf::Mouse::getPosition (window);
              std::cout << "click pos: " << clickPos.x << "," << clickPos.y
                        << std::endl;

              if (sprite.getGlobalBounds ().contains (clickPos.x, clickPos.y))
                {
                  sound.play ();
                  is_clicked = true;
                  click_timer.restart ();
                }
            }
        }

      window.clear ();
      if (!is_clicked || click_timer.getElapsedTime ().asSeconds () < 4.0f)
        {
          window.draw (sprite);
        }
      else
        {
          text.setString ("Cartman took off after you smacked him around :(");
        }
      window.draw (text);
      window.display ();
    }

  return 0;
}