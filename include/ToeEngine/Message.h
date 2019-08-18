#pragma once

namespace Message
{
  typedef unsigned Message;

  enum MessageValue
  {
    // Add messages here

    // Player Movement
    MV_Up,
    MV_Down,
    MV_Right,
    MV_Left,

    MV_Escape,

    MV_ToggleFullscreen,

    MV_Count
  };
}