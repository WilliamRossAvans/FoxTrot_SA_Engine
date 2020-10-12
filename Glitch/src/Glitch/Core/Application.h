#pragma once
#include "Core.h"
#include "Glitch/Renderer/window.h"
#include <Glitch\Renderer\SceneManager\SceneManager.h>
#include <Glitch\Renderer\Renderer2d.h>
#include <Glitch\Physics\PhysicsEngine.h>

namespace Glitch {
	class GLITCH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	protected:
		ISDL2Facade* sdlFacade;
		PhysicsEngine physics;
		
		SceneManager* sceneManager = new SceneManager();
		Renderer2d* renderer;

		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_window;
		bool isRunning = true;
	};
	// to be defined in Game/Client
	Application* CreateApplication(); 
}


