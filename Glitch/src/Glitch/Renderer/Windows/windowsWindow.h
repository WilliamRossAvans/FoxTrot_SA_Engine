#pragma once
#include "Glitch\Renderer\window.h"
#include "Glitch/Log/Log.h"
#include "windowsWindow.h"
#include "Glitch/Events/ApplicationEvent.h"
#include "Glitch/Events/KeyEvent.h"
#include "Glitch/Events/MouseEvent.h"

#include "SDL.h"
namespace Glitch {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;

		// Inherited via Window
		virtual void OnUpdate() override;
		virtual unsigned int GetWidth() const override { return m_data->Width; }
		virtual unsigned int GetHeight() const override { return m_data->Height; }
		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_data->EventCallback = callback; }
		virtual void SetVsync(bool enabled) override;
		virtual bool IsVsync() const override;

		WindowProps* GetProperties() const override { return m_data; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		void PollEvents();

		SDL_Window* window = nullptr;		
		WindowProps* m_data;
	};
}

