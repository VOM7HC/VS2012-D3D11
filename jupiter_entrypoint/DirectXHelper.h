﻿#pragma once

#include <wrl/client.h>
#include <ppl.h>
#include <ppltasks.h>

namespace DX
{
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            // Set a breakpoint on this line to catch Win32 API errors.
            throw Platform::Exception::CreateException(hr);
        }
    }

    // Function that reads from a binary file asynchronously.
    inline Concurrency::task<Platform::Array<byte>^> ReadDataAsync(Platform::String^ filename)
    {
        using namespace Windows::Storage;
        using namespace Concurrency;

        auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;

        return create_task(folder->GetFileAsync(filename)).then([] (StorageFile^ file) 
        {
            return FileIO::ReadBufferAsync(file);
        }).then([] (Streams::IBuffer^ fileBuffer) -> Platform::Array<byte>^ 
        {
            auto fileData = ref new Platform::Array<byte>(fileBuffer->Length);
            Streams::DataReader::FromBuffer(fileBuffer)->ReadBytes(fileData);
            return fileData;
        });
    }
}
