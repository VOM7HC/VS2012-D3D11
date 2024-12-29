#pragma once

#include "DirectXHelper.h"

using namespace Microsoft::WRL;
using namespace Windows;
using namespace Windows::UI::Core;

// Helper class that initializes DirectX APIs for 3D rendering.
ref class Direct3DBase abstract
{
internal:
    Direct3DBase();

public:
    virtual void Initialize(CoreWindow^ window);
    virtual void HandleDeviceLost();
    virtual void CreateDeviceResources();
    virtual void CreateWindowSizeDependentResources();
    virtual void UpdateForWindowSizeChange();
    virtual void ReleaseResourcesForSuspending();
    virtual void Render() = 0;
    virtual void Present();
    virtual float ConvertDipsToPixels(float dips);

protected private:
    // Direct3D Objects.
    ComPtr<ID3D11Device1> m_d3dDevice;
    ComPtr<ID3D11DeviceContext1> m_d3dContext;
    ComPtr<IDXGISwapChain1> m_swapChain;
    ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    ComPtr<ID3D11DepthStencilView> m_depthStencilView;

    // Cached renderer properties.
    D3D_FEATURE_LEVEL m_featureLevel;
    Foundation::Size m_renderTargetSize;
    Foundation::Rect m_windowBounds;
    Platform::Agile<CoreWindow> m_window;
};