#include "PathFinding.h"

#include <SDL_image.h>

using namespace Engine;

PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

void PathFinding::init()
{
    loadTexture();

    SDL_QueryTexture(m_Texture, NULL, NULL, &m_SourceRectangle.w, &m_SourceRectangle.h);
    m_DestinationRectangle.x = m_SourceRectangle.x = 0;
    m_DestinationRectangle.y = m_SourceRectangle.y = 0;
    m_DestinationRectangle.w = m_SourceRectangle.w;
    m_DestinationRectangle.h = m_SourceRectangle.h;
}

void PathFinding::render()
{
    SDL_Renderer* renderer = Window::GetSingleton()->getSDLRenderer();

    SDL_RenderClear(renderer); // clear the renderer to the draw color
    
    SDL_RenderCopy(renderer, m_Texture, &m_SourceRectangle, &m_DestinationRectangle);

    SDL_RenderPresent(renderer); // draw to the screen
}

void PathFinding::update()
{
    render();
}

void PathFinding::loadTexture() {
    SDL_Surface* tempSurface = IMG_Load("textures/kristina.jpg");

    m_Texture = SDL_CreateTextureFromSurface(Window::getWindow()->getSDLRenderer(), tempSurface);

    SDL_FreeSurface(tempSurface);
}

