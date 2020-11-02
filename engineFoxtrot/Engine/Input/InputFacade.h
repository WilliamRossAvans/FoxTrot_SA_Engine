#pragma once
#include "Commands.h"
#include "InputConstants.h"
#include "Events/Codes/KeyCodes.h"
#include "./Events/EventSingleton.h"
#include "./Events/Key/KeyPressed.h"
#include "./Events/Key/KeyReleased.h"
#include "./Events/Mouse/MouseMoved.h"
#include "./Events/Mouse/MousePressed.h"
#include "./Events/Mouse/MouseReleased.h"
#include "./Events/Mouse/MouseScrolledEvent.h"

#include "IInputFacade.h"

union SDL_Event;

/// @brief Facade for SDL input part
class InputFacade : public IInputFacade
{

public:
    InputFacade();
    ~InputFacade();

	bool fill(vector<Command*>& command_queue);
	void configure(KeyCode key, Command* command, bool runOnce);

private:
	bool input_mapping();
	void dispatcher(vector<Command*>& command_queue);

	void keydown(SDL_Event& event);
	void keyup(SDL_Event& event);

	ButtonState is_held(KeyCode key);
	Action was_pressed(KeyCode key);

	void pollEvents() override;

	map <KeyCode, ButtonState> state_map;
	map <KeyCode, Action> action_map;

	map <KeyCode, Command*> commands;
	vector<KeyCode> handleOnce;

	KeyCode eventToKeyCode(SDL_Event& event);
};



