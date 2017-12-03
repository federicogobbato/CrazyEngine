#include "PathFinding.h"

#include <SDL_image.h>
#include <Engine\Window.h>

using namespace Engine;

PathFinding::PathFinding()
{
    m_Window = static_cast<WindowSDL*>(Window::GetSingleton());
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
    m_Window->clearRenderer();

    SDL_RenderCopy(m_Window->getRenderer(), m_Texture, &m_SourceRectangle, &m_DestinationRectangle);

    m_Window->swapBuffer();
}

void PathFinding::update()
{
    render();
}

void PathFinding::loadTexture() {
    SDL_Surface* tempSurface = IMG_Load("textures/kristina.jpg");

    m_Texture = SDL_CreateTextureFromSurface(m_Window->getRenderer(), tempSurface);

    SDL_FreeSurface(tempSurface);
}

