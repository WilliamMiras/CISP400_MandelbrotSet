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
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    //for loop to count how many iterations?
}

void ComplexPlane::iterationsToRGB(size_t count, Unit8& r, Unit8& g, Unit8& b)
{
    /*
        Professor says to complete later as this is hard to do.
        Also do not know what to include for Unit8&, looked it up and said to include stdint.h?
    */
}