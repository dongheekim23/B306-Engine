#include "Engine.h"

namespace ToeEngine
{
  Engine* ENGINE = nullptr;

  Engine::Engine()
  {
    assert(ENGINE == nullptr);
    ENGINE = this;
  }

  void Engine::Init()
  {
    m_running = true;

    // Add systems to the engine
    // (Add SDL system here)
    m_systemVec.push_back(SystemPtr(new Systems::WindowSDL));

    // Create a world for the engine to run in


    // Add systems to the world that are necessary for the world to run


    // Initialize all systems in the engine
    for (auto sys : m_systemVec)
      sys->Init();
  }

  void Engine::Shutdown()
  {
    for (auto sys : m_systemVec)
      sys->Shutdown();

    m_systemVec.clear();

    ENGINE = nullptr;
  }

  void Engine::Update()
  {
    m_start = clock::now();

    while (m_running)
    {
      auto end = clock::now();
      std::chrono::duration<float> duration = end - m_start;
      m_start = end;

      m_dt = duration.count();

      using Systems::WindowSDL;

      GETSYS(WindowSDL)->Update(m_dt);

      GETSYS(WindowSDL)->NewFrame();

      GETSYS(WindowSDL)->EndFrame();
    }
  }

  void Engine::SendMsg(EntityPtr e1, EntityPtr e2, Message::Message msg)
  {
    for (auto& sys : m_systemVec)
    {
      sys->SendMsg(e1, e2, msg);
    }

    // Call send msg for current state here
  }

  template <typename T>
  std::shared_ptr<T> Engine::GetSystem(EnumeratedSystem sysType)
  {
    for (auto& sys : m_systemVec)
    {
      if (sys->m_type == sysType)
        return std::static_pointer_cast<T>(sys);
    }

    throw std::exception("There is no such system in the engine");
  }
}