#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
Event event;

int monitorWidth = VideoMode::getDesktopMode().width;
int monitorHeight = VideoMode::getDesktopMode().height;
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
                Vector2f clicked;
                clicked = win.mapPixelToCoords(Mouse::getPosition(win));
                c.setCenter(clicked);
                if(event.mouseButton.button == sf::Mouse::Left) {c.zoomIn();}
                if(event.mouseButton.button == sf::Mouse::Right) {c.zoomOut();}
                now = CALCULATING;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                win.close();
            }
            if(event.type ==sf::Event::MouseMoved)
            {
                c.setMouseLocation(win.mapPixelToCoords(Mouse::getPosition(win),c.getView()));
            }
            if(now == CALCULATING)
            {
                size_t counter;
                Uint8 r,g,b;
                for(int i = 0; i < monitorWidth; i++)
                {
                    for(int j = 0; j < monitorHeight; j++)
                    {
                        vertices[j,i].position = {j,i};
                        Vector2f coords = win.mapPixelToCoords(Vector2i {(float) j,(float) i},c.getView());
                        counter = c.countIterations(coords);
                        c.iterationsToRGB(counter,r,g,b);
                        vertices[j,i].color = {r,g,b};
                    }
                }
                now = DISPLAYING;
                c.loadText(textbox);
            }
            if(now == DISPLAYING)
            {
                win.clear();
                win.draw(vertices);
                win.draw(textbox);
                win.display();
            }
        }
    }
return 0;
}