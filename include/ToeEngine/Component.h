#pragma once

#include <memory>

namespace ToeEngine
{
  typedef unsigned mask;

#pragma region metaDataEnums
  
  // Used for indexing components
  enum EnumeratedComponent
  {
    EC_None              = 0,
    EC_Drawable          = 1,
    EC_RigidBody         = 2,
    EC_Sprite            = 3,
    EC_BoxCollider       = 4,
    EC_CircleCollider    = 5,
    EC_Camera            = 6,
    EC_Transform         = 7,
    EC_Particle          = 8,
    // Add more components here

    EC_Count,
  };

  // Used to rapidly check components attached to the object
  enum BitfieldComponent
  {
    MC_Alive             = 1,
    MC_Drawable          = 1 << 1,
    MC_RigidBody         = 1 << 2,
    MC_Sprite            = 1 << 3,
    MC_BoxCollider       = 1 << 4,
    MC_CircleCollider    = 1 << 5,
    MC_Camera            = 1 << 6,
    MC_Transform         = 1 << 7,
    MC_Particle          = 1 << 8,

    MC_NoObjects = -1
  };

#pragma endregion

  class Component
  {
  public:
    Component(EnumeratedComponent ec, BitfieldComponent bc) : m_type(ec), m_mask(bc) {}

    // These should be const since they should never be changed after being created
    const EnumeratedComponent m_type;
    const BitfieldComponent   m_mask;

    // Use virtual keyword to deallocate derived component types properly
    virtual ~Component() {}

  private:
    // Default constructor not allowed
    // Allow construction with parameters only
    Component() = delete;
  };

  typedef std::shared_ptr<Component> ComponentPtr;
}