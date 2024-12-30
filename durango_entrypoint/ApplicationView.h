//
// ApplicationView.h
//

#pragma once

#include "pch.h"
#include "Game.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;

// Application - implements the required functionality for an application
ref class ApplicationView sealed : public IFrameworkView
{
public:
    ApplicationView();

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
    void OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args);

private:
    Game^ m_game;
    bool m_windowClosed;
};

// ApplicationSource - responsible for creating the Application instance
// and passing it back to the system
ref class ApplicationViewSource sealed : IFrameworkViewSource
{
public:
    virtual IFrameworkView^ CreateView();
};
