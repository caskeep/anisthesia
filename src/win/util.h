/*
MIT License

Copyright (c) 2017 Eren Okka

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <memory>
#include <string>
#include <type_traits>

#include <windows.h>

namespace anisthesia {
namespace win {

struct HandleDeleter {
  using pointer = HANDLE;
  void operator()(pointer p) const { ::CloseHandle(p); }
};

using Handle = std::unique_ptr<HANDLE, HandleDeleter>;

////////////////////////////////////////////////////////////////////////////////
// Alternative to Microsoft::WRL::ComPtr in <wrl/client.h>

template <typename T>
struct ComInterfaceDeleter {
  static_assert(std::is_base_of<IUnknown, T>::value, "Invalid COM interface");
  using pointer = T*;
  void operator()(pointer p) const { if (p) p->Release(); }
};

template <typename T>
using ComInterface = std::unique_ptr<T, ComInterfaceDeleter<T>>;

////////////////////////////////////////////////////////////////////////////////

std::wstring GetFileNameFromPath(const std::wstring& path);
std::wstring GetFileNameWithoutExtension(const std::wstring& filename);
bool IsSystemDirectory(const std::wstring& path);

}  // namespace win
}  // namespace anisthesia
