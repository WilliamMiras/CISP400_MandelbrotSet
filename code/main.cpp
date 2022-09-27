#include "ComplexPlane.h"
int main()
{
Event event;
float ratio = 1920/1080.0;
ComplexPlane c(ratio);
VideoMode res(1920,1080,32);
RenderWindow win(res,"Mandlebrot Set", Style::Default);
Font font;
font.loadFromFile("/fonts/OldSchoolAdventures-42j9.ttf");
Text textbox("test",font,15);
textbox.setFillColor(sf::Color::White);
textbox.setOutlineColor(sf::Color::Black);
textbox.setScale(2.4,2.4);
textbox.setStyle(sf::Text::Bold);
textbox.setPosition(0,0);

    while(win.isOpen())
    {
        while(win.pollEvent(event))
        {
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {

                }
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    Vector2f clicked;
                    clicked.x = event.mouseButton.x;
                    clicked.y = event.mouseButton.y;
                    c.zoomOut();
                    c.setCenter(clicked);
                }
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.KeyPressed == sf::Keyboard::Escape)
                {
                    win.close();
                }
            }
        }
    }
return 0;
}