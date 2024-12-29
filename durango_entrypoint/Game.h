//
// Game.h
//

#pragma once

#include "pch.h"
#include <agile.h>
#include "StepTimer.h"

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;

// A basic game implementation that creates a D3D11 device and
// provides a game loop
ref class Game sealed
{
public:
    Game();

    // Initialization and management
    void Initialize(CoreWindow^ window);

    // Basic game loop
    void Tick();
    void Render();

    // Rendering helpers
    void Clear();
    void Present();

    void Suspend();
    void Resume();

private:
    void Update(DX::StepTimer const& timer);

    void CreateDevice();
    void CreateResources();

    // Core Application state
    Platform::Agile<CoreWindow>     m_window;
    Windows::Foundation::Rect       m_windowBounds;

    // Direct3D Objects
    D3D_FEATURE_LEVEL                  m_featureLevel;
    ComPtr<ID3D11DeviceX>              m_d3dDevice;
    ComPtr<ID3D11DeviceContextX>       m_d3dContext;

    // Rendering resources
    ComPtr<IDXGISwapChain1>            m_swapChain;
    ComPtr<ID3D11RenderTargetView>     m_renderTargetView;
    ComPtr<ID3D11DepthStencilView>     m_depthStencilView;
    ComPtr<ID3D11Texture2D>            m_depthStencil;

    // Game state
    INT64                                              m_frame;
    DX::StepTimer                                      m_timer;
};

// PIX event colors
const DWORD EVT_COLOR_FRAME = PIX_COLOR_INDEX(1);
const DWORD EVT_COLOR_UPDATE = PIX_COLOR_INDEX(2);
const DWORD EVT_COLOR_RENDER = PIX_COLOR_INDEX(3);
