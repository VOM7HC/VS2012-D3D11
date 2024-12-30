#pragma once

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;

ref class AppView sealed : public IFrameworkView
{
public:
    AppView();

    // IFrameworkView Methods
    virtual void Initialize(CoreApplicationView^ applicationView);
    virtual void SetWindow(CoreWindow^ window);
    virtual void Load(Platform::String^ entryPoint);
    virtual void Run();
    virtual void Uninitialize();

protected:
    // Event Handlers
    void OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args);
    void OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args);
    void OnResuming(Platform::Object^ sender, Platform::Object^ args);
    void OnWindowClosed(CoreWindow^ window, CoreWindowEventArgs^ args);
#if defined (WINAPI_FAMILY_TV_TITLE)
#endif
#if defined (WINAPI_FAMILY_APP)
    void OnLogicalDpiChanged(Platform::Object^ sender);
    void OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args);
#endif
#if defined (WINAPI_FAMILY_PHONE_APP)
    void OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args);
#endif
#if defined (WINAPI_FAMILY_APP) || defined (WINAPI_FAMILY_PHONE_APP)
    void OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args);
    void OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args);
    void OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args);
#endif
private:
    bool m_windowClosed;
};

ref class AppViewSource sealed : IFrameworkViewSource
{
public:
    virtual IFrameworkView^ CreateView();
};