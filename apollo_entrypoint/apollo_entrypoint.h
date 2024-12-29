#pragma once

#include "pch.h"
#include "CubeRenderer.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;

ref class apollo_entrypoint sealed : public IFrameworkView
{
public:
    apollo_entrypoint();

    // IFrameworkView Methods.
    virtual void Initialize(CoreApplicationView^ applicationView);
    virtual void SetWindow(CoreWindow^ window);
    virtual void Load(Platform::String^ entryPoint);
    virtual void Run();
    virtual void Uninitialize();

protected:
    // Event Handlers.
    void OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args);
    void OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args);
    void OnResuming(Platform::Object^ sender, Platform::Object^ args);
    void OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args);
    void OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args);
    void OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args);
    void OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args);
    void OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args);

private:
    CubeRenderer^ m_renderer;
    bool m_windowClosed;
    bool m_windowVisible;
};

ref class Direct3DApplicationSource sealed : IFrameworkViewSource
{
public:
    virtual IFrameworkView^ CreateView();
};