#pragma once

#include "Includes.h"
#include "System.h"

namespace ToeEngine
{
  class Space
  {
  public:
    Space(std::string& name);
    ~Space();

    void Update(float dt);

    void AddSystem(SystemPtr);
    void RemoveSystem(SystemPtr);

    EntityPtr CreateEntity();
    EntityPtr CreateCamera();
    EntityPtr GetCamera() const;

    void PopulateEntities(SystemPtr) const;
    EntityVec GetEntities(mask) const;
    EntityPtr GetEntityByName(std::string);

    void RemoveEntity(EntityPtr);
    void AddEntity(EntityPtr);

    void Clear();

    const std::string& GetName() const { return m_name; }

  private:
    std::string m_name;
    EntityVec m_entityVec;
    EntityPtr m_camera;

    SystemVec m_systemVec;

    // Do not allow default and copy constructors
    Space() = delete;
    Space(Space& space) = delete;
  };

  typedef std::shared_ptr<Space> SpacePtr;
}