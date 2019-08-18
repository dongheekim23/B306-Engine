#include "WindowSDL.h"

const int screenWidth = 800;
const int screenHeight = 600;

namespace ToeEngine
{
  extern Engine* ENGINE;
  namespace Systems
  {
    WindowSDL::WindowSDL() : System(std::string("WindowSDLSystem"), ESys::ES_WindowSDL),
      m_isFullscreen(false),
      m_window(nullptr),
      m_context(NULL),
      m_width(screenWidth),
      m_height(screenHeight)
    {
    }

    void WindowSDL::Init()
    {
      RegisterComponent(MC_NoObjects);

      m_window = SDL_CreateWindow("ToeEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        m_width, m_height, SDL_WINDOW_OPENGL);

      m_context = SDL_GL_CreateContext(m_window);

      glewInit();
    }

    void WindowSDL::Update(float dt)
    {
      PollEvents();
    }

    void WindowSDL::Shutdown()
    {
      SDL_GL_DeleteContext(m_context);
      SDL_Quit(); // Do I need to call this?
    }

    bool WindowSDL::GetMouseReleased()
    {
      return m_mouse.released;
    }

    bool WindowSDL::GetMouseTriggered()
    {
      return m_mouse.triggered;
    }

    glm::vec2 WindowSDL::GetMousePosition()
    {
      //glm::vec2 currCameraPos = ENGINE->GetActiceSpace()->GetCamera()->GET_COMPONENT(Transform)->position;
      glm::vec2 spaceMousePos;

      return spaceMousePos;
    }

    void WindowSDL::PollWindowEvent(SDL_Event& currEvent)
    {
      switch (currEvent.type)
      {
      case SDL_WINDOWEVENT:
        switch (currEvent.window.event)
        {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
          SDL_GetWindowSize(m_window, &m_width, &m_height);
          glViewport(0, 0, m_width, static_cast<GLsizei>(m_width / (static_cast<float>(m_width) / m_height)));
          break;
        }
        break;

      case SDL_QUIT:
        std::cout << "Quit Engine" << std::endl;
        ENGINE->Stop();
        break;
      }
    }

    void WindowSDL::PollKeyEvent(SDL_Event& currEvent)
    {
      switch (currEvent.type)
      {
      case SDL_KEYDOWN:
        if (currEvent.key.keysym.sym == SDLK_UP)
          ENGINE->SendMsg(nullptr, nullptr, Message::MV_Up);

        if (currEvent.key.keysym.sym == SDLK_DOWN)
          ENGINE->SendMsg(nullptr, nullptr, Message::MV_Down);

        if (currEvent.key.keysym.sym == SDLK_RIGHT)
          ENGINE->SendMsg(nullptr, nullptr, Message::MV_Right);

        if (currEvent.key.keysym.sym == SDLK_LEFT)
          ENGINE->SendMsg(nullptr, nullptr, Message::MV_Left);

        if (currEvent.key.keysym.sym == SDLK_ESCAPE)
          ENGINE->SendMsg(nullptr, nullptr, Message::MV_Escape);

        break;
      case SDL_KEYUP:
        break;
      }
    }

    void WindowSDL::PollMouseEvent(SDL_Event& currEvent)
    {

    }

    void WindowSDL::PollEvents()
    {
      m_mouse.triggered = false;

      while (SDL_PollEvent(&m_event))
      {
        PollWindowEvent(m_event);
        PollKeyEvent(m_event);
        PollMouseEvent(m_event);
      }
    }

    void WindowSDL::NewFrame()
    {
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
    }

    void WindowSDL::EndFrame()
    {
      SDL_GL_SwapWindow(m_window);
    }

    void WindowSDL::ToggleFullscreen()
    {
      if (m_isFullscreen)
      {
        SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
      }
      else
      {
        SDL_SetWindowFullscreen(m_window, 0);
      }

      m_isFullscreen != m_isFullscreen;
    }

    void WindowSDL::SendMsg(EntityPtr e1, EntityPtr e2, Message::Message msg)
    {
      switch (msg)
      {
      case Message::MV_ToggleFullscreen:
        ToggleFullscreen();
        break;

      case Message::MV_Escape:
        //ENGINE->Stop();
        PushSDLEvent(SDL_QUIT);
        break;
      }
    }

    void WindowSDL::PushSDLEvent(eventType type)
    {
      SDL_Event sdlEvent;
      sdlEvent.type = type;
      SDL_PushEvent(&sdlEvent);
    }
  }
}