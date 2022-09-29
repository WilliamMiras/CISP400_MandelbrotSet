#include <stdint.h>
#include <iostream>
#include <complex>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "ComplexPlane.h"

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
    m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio); //Might need as Vector2f?
    m_view.setCenter(0.0, 0.0);
    m_zoomCount = 0;
}
View ComplexPlane::getView()
{
return m_view;
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_view.setSize(x_size, y_size);
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_view.setSize(x_size, y_size);
}

void ComplexPlane::setCenter(Vector2f coord)
{
    m_view.setCenter(coord);
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
    m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
    //https://cplusplus.com/reference/sstream/stringstream/stringstream/
    stringstream ss;
    double centerx,centery,cursorx,cursory;
    ss << m_view.getCenter().x << m_view.getCenter().y << m_mouseLocation.x << m_mouseLocation.y;
    ss >> centerx >> centery >> cursorx >>cursory;
    text.setString("Mandelbrot Set\nCenter: (" + to_string(centerx) + "," + to_string(centery) + ")\n" + "Cursor: " + "(" + to_string(cursorx) + "," + to_string(cursory) + ")\n" + "Left-click to Zoom in\nRight-click to Zoom out");
    text.setPosition(0,0);
    }

size_t ComplexPlane::countIterations(Vector2f coord)
{
    complex<double> c(coord.x, coord.y);
    complex<double> z(0,0);
    size_t iter = 0;

    while(abs(z) < 2 && iter < MAX_ITER)
    {
        
        z = z*z + c;
        iter++;
    }
    return iter;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    /*
        Professor says to complete later as this is hard to do.
        Also do not know what to include for Unit8&, looked it up and said to include stdint.h?
        its actually Uint8! which is just an integer from 0 to 255.
    */
   // setting the values to white so we can do grayscale for testing
   count = count * 4;
   if(count == MAX_ITER * 4)
   {
    r = 0;
    g = 0;
    b = 0;
   }
   else
   {
    if(count > 204)
    {
        r = 255;
        g = 0;
        b = 0;
    }
    else if(count > 153)
    {
        r = 255;
        g = 255;
        b = 0;
    }
    else if(count > 102)
    {
        r = 0;
        g = 255;
        b = 0;
   }
   else if(count > 51)
   {
    r = 0;
    g = 255;
    b = 255;
   }
   else
   {
    r = 100;
    g = 50;
    b = 255;
   }
   }
}