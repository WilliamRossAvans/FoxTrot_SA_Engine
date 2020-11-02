#pragma once
/// @brief 
/// Type of button input
enum class InputType
{
    ACTION,
    STATE,
    RANGE
};

/// @brief 
/// Type of button action
enum class Action
{
    EXECUTE = true,
    STOP = false
};

/// @brief 
/// Button state
enum class ButtonState
{
    PRESSED = true,
    RELEASED = false
};
