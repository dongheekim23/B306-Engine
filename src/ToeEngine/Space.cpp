#include "Space.h"

namespace ToeEngine
{
  Space::Space(std::string& name) : m_name(name)
  {
    m_camera = CreateCamera();
  }

  Space::~Space()
  {
    m_entityVec.clear();
  }

  void Space::Update(float dt)
  {
    for (auto& system : m_systemVec)
    {
      PopulateEntities(system);

      system->Update(dt);
    }
  }

  void Space::AddSystem(SystemPtr system)
  {
    for (auto sys : m_systemVec)
    {
      if (sys == system)
      {
        throw std::exception("System already exists in the space!");
      }
    }
    m_systemVec.push_back(system);
  }

  void Space::RemoveSystem(SystemPtr system)
  {
    auto sys = std::find(m_systemVec.begin(), m_systemVec.end(), system);

    if (sys == m_systemVec.end())
    {
      throw std::exception("System does not exist in this space!");
    }
    m_systemVec.erase(sys);
  }

  EntityPtr Space::CreateCamera()
  {
    // TODO : Assign a prefab here
    EntityPtr camera = EntityPtr(new Entity);

    return camera;
  }

  EntityPtr Space::GetCamera() const
  {
    return m_camera;
  }

  void Space::PopulateEntities(SystemPtr system) const
  {
    system->m_entityVec.clear();

    if (system->GetMask() != MC_NoObjects)
    {
      for (auto& it : m_entityVec)
      {
        mask m = system->GetMask();
        if (it->CheckMask(m))
          system->m_entityVec.push_back(it);
      }
    }
  }

  EntityVec Space::GetEntities(mask m) const
  {
    EntityVec matchedEntities;

    for (auto it : m_entityVec)
    {
      if (it->CheckMask(m))
        matchedEntities.push_back(it);
    }

    return matchedEntities;
  }

  EntityPtr Space::GetEntityByName(std::string name)
  {
    for (auto entity : m_entityVec)
    {
      if (entity->Name() == name)
        return entity;
    }
    throw std::exception("There is no entity with the name in this space");
  }

  void Space::RemoveEntity(EntityPtr entity)
  {
    for (auto& it : m_entityVec)
    {
      if (it == entity)
      {
        it.reset();
        it = m_entityVec.back();
        m_entityVec.pop_back();
        return;
      }
    }
    throw std::exception("There is no entity matches the input in this space");
  }

  void Space::AddEntity(EntityPtr entity)
  {
    m_entityVec.push_back(entity);
  }

  void Space::Clear()
  {
    m_entityVec.clear();
    m_systemVec.clear();
  }
}