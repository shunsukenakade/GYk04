#pragma once
#include <d3d11.h>
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include <vector>
#include <list>
#include <string>

class Window
{
public:
	Window(std::string name = "no name", ImVec2 size = { 200.0f, 200.0f }, ImVec2 pos = {0.0f, 0.0f});
	~Window();

	std::string GetName() { return m_name; }
	ImVec2 GetSize() { return m_size; }
	ImVec2 GetPos() { return m_pos; }
	std::list<std::string>* GetTexts() { return &m_texts; }

private:
	std::string m_name; // ウィンドウ名
	ImVec2 m_size; // ウィンドウサイズ
	ImVec2 m_pos; // ウィンドウ位置
	std::list<std::string> m_texts;
};


class DebugWindow
{
private:
	static DebugWindow* m_instance;

public:
	static DebugWindow* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new DebugWindow();
		return m_instance;
	}

	void Init(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* context);
	void Uninit();
	void Update();
	void Draw();

	Window* CreateWnd(std::string name, ImVec2 size = {200.0f, 200.0f}, ImVec2 pos = {0.0f, 0.0f})
	{
		Window* window = new Window(name, size, pos);
		m_windows.push_back(window);
		return window;
	}

private:
	std::vector<Window*> m_windows;
};


