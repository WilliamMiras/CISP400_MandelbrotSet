#include <stdint.h>
#include <iostream>
#include <complex>
#include <cstdlib>
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
    m_zoomCount += 1;
    int x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    int y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_view.setSize(x_size, y_size);
}

void ComplexPlane::zoomOut()
{
    m_zoomCount -= 1;
    int x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    int y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
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
    float centerx,centery,cursorx,cursory;
    ss << m_view.getCenter().x << m_view.getCenter().y << m_mouseLocation.x << m_mouseLocation.y;
    ss >> centerx >> centery >> cursorx >>cursory;
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    complex<double> c(coord.x, coord.y);
    complex<double> z(0,0);
    size_t iter = 0;
    //for loop to count how many iterations?
    for(unsigned int i = 0; i < MAX_ITER; i++)
    {
        z = z*z + c;
        while(abs(z) < 2)
        {
            iter++;
        }
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
   r = 255;
   g = 255;
   b = 255; // setting the values to white so we can do grayscale for testing
   for(size_t i = (count * 4) -1; i > 0; i--)
   {
    r--;
    g--;
    b--;
   }
}