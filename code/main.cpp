#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
Event event;

int monitorWidth = VideoMode::getDesktopMode.width();
int monitorHeight = VideoMode::getDesktopMode.height();
VideoMode res(monitorWidth, monitorHeight);
float ratio = monitorHeight/monitorWidth;
ComplexPlane c(ratio);
RenderWindow win(res,"Mandlebrot Set", Style::Default);
Font font;
font.loadFromFile("/fonts/OldSchoolAdventures-42j9.ttf");
Text textbox("test",font,15);
textbox.setFillColor(sf::Color::White);
textbox.setOutlineColor(sf::Color::Black);
textbox.setScale(2.4,2.4);
textbox.setStyle(sf::Text::Bold);
textbox.setPosition(0,0);
VertexArray vertices;
vertices.setPrimitiveType(Points);
vertices.resize(monitorHeight*monitorWidth);
enum CurrentState {CALCULATING,DISPLAYING };
CurrentState now = CALCULATING;

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
                    clicked = win.mapPixelToCoords(Mouse::getPosition(win));
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
            if(event.type ==sf::Event::MouseMoved)
            {
                c.setMouseLocation(win.mapPixelToCoords(Mouse::getPosition(win)));
            }
            if(now == CALCULATING)
            {
                Uint8 r,g,b;
                for(int i = 0; i < monitorWidth; i++)
                {
                    for(int j = 0; i <monitorHeight; j++)
                    {
                        vertices[j,i].position = {j,i};
                        c.getView();
                    }
                }
            }
        }
    }
return 0;
}