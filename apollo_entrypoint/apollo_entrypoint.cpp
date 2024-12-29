#include "pch.h"
#include "apollo_entrypoint.h"
#include "BasicTimer.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace concurrency;

apollo_entrypoint::apollo_entrypoint() :
    m_windowClosed(false),
    m_windowVisible(true)
{
}

void apollo_entrypoint::Initialize(CoreApplicationView^ applicationView)
{
    applicationView->Activated +=
        ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &apollo_entrypoint::OnActivated);

    CoreApplication::Suspending +=
        ref new EventHandler<SuspendingEventArgs^>(this, &apollo_entrypoint::OnSuspending);

    CoreApplication::Resuming +=
        ref new EventHandler<Platform::Object^>(this, &apollo_entrypoint::OnResuming);

    m_renderer = ref new CubeRenderer();
}

void apollo_entrypoint::SetWindow(CoreWindow^ window)
{
    window->VisibilityChanged +=
        ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &apollo_entrypoint::OnVisibilityChanged);

    window->Closed += 
        ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &apollo_entrypoint::OnWindowClosed);

    window->PointerPressed +=
        ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &apollo_entrypoint::OnPointerPressed);

    window->PointerMoved +=
        ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &apollo_entrypoint::OnPointerMoved);

    window->PointerReleased +=
        ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &apollo_entrypoint::OnPointerReleased);

    m_renderer->Initialize(CoreWindow::GetForCurrentThread());
}

void apollo_entrypoint::Load(Platform::String^ entryPoint)
{
}

void apollo_entrypoint::Run()
{
    BasicTimer^ timer = ref new BasicTimer();

    while (!m_windowClosed)
    {
        if (m_windowVisible)
        {
            timer->Update();
            CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
            m_renderer->Update(timer->Total, timer->Delta);
            m_renderer->Render();
            m_renderer->Present(); // This call is synchronized to the display frame rate.
        }
        else
        {
            CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
        }
    }
}

void apollo_entrypoint::Uninitialize()
{
}

void apollo_entrypoint::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
    m_windowVisible = args->Visible;
}

void apollo_entrypoint::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
    m_windowClosed = true;
}

void apollo_entrypoint::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
    // Insert your code here.
}

void apollo_entrypoint::OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args)
{
    // Insert your code here.
}

void apollo_entrypoint::OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args)
{
    // Insert your code here.
}

void apollo_entrypoint::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
    CoreWindow::GetForCurrentThread()->Activate();
}

void apollo_entrypoint::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
    // Save app state asynchronously after requesting a deferral. Holding a deferral
    // indicates that the application is busy performing suspending operations. Be
    // aware that a deferral may not be held indefinitely. After about five seconds,
    // the app will be forced to exit.
    SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();
    m_renderer->ReleaseResourcesForSuspending();

    create_task([this, deferral]()
    {
        // Insert your code here.

        deferral->Complete();
    });
}

void apollo_entrypoint::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
    // Restore any data or state that was unloaded on suspend. By default, data
    // and state are persisted when resuming from suspend. Note that this event
    // does not occur if the app was previously terminated.
    m_renderer->CreateWindowSizeDependentResources();
}

IFrameworkView^ Direct3DApplicationSource::CreateView()
{
    return ref new apollo_entrypoint();
}

[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
    auto direct3DApplicationSource = ref new Direct3DApplicationSource();
    CoreApplication::Run(direct3DApplicationSource);
    return 0;
}