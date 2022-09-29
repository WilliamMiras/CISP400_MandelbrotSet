#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
int main()
{
Event event;
VideoMode res(1920, 1080);
VideoMode monitor = res.getDesktopMode();
float monitorWidth = monitor.width;
float monitorHeight = monitor.height;
float ratio = monitorHeight / monitorWidth;
ComplexPlane c(ratio);
RenderWindow win(res,"Mandlebrot Set", Style::Default);

Font font;
font.loadFromFile("fonts/OldSchoolAdventures-42j9.ttf");
Text textbox("test",font,15);
textbox.setFillColor(sf::Color::White);
textbox.setOutlineColor(sf::Color::Black);
textbox.setScale(1,1);
textbox.setStyle(sf::Text::Bold);
textbox.setPosition(0,0);

VertexArray vertices(Points,monitorHeight*monitorWidth);
enum CurrentState { CALCULATING, DISPLAYING };
CurrentState now = CALCULATING;

    while(win.isOpen())
    {
        while(win.pollEvent(event))
        {
            if (event.key.code == Keyboard::Escape)
            {
                win.close();
            }
            if(event.type == Event::Closed) {win.close();}
            if(event.type == sf::Event::MouseButtonPressed)
            {
                Vector2f clicked;
                clicked = win.mapPixelToCoords(Mouse::getPosition(win),c.getView());
                
                if(event.mouseButton.button == sf::Mouse::Left) {c.zoomIn();}
                if(event.mouseButton.button == sf::Mouse::Right) {c.zoomOut();}
                c.setCenter(clicked);
                now = CALCULATING;
            }
            
            if(event.type == sf::Event::MouseMoved)
            {
                c.setMouseLocation(win.mapPixelToCoords(Mouse::getPosition(win),c.getView()));
            }
        }
        if(now == CALCULATING)
            {
                
                for(int j = 0; j < monitorWidth; j++)
                {
                    for(int i = 0; i < monitorHeight; i++)
                    {
                        size_t counter = 0;
                        Uint8 r,g,b = 0;
                        vertices[j+i*monitorWidth].position = {(float)j,(float)i};
                        Vector2i points{j,i};
                        Vector2f coords = win.mapPixelToCoords(points,c.getView());
                        counter = c.countIterations(coords);
                        c.iterationsToRGB(counter,r,g,b);
                        vertices[j+i*monitorWidth].color = {r,g,b};
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
return 0;
}