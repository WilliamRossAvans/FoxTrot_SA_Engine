#pragma once
#include "KeyEvent.h"

/// @brief
/// KeyTypedEvent is triggered when a key is typed
class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(KeyCode _keycode) : KeyEvent(_keycode) {}

	/// @brief
	/// KeyTypedEvent to string
	/// @return string with key code pressed
	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << keycode;
		return ss.str();
	}
};