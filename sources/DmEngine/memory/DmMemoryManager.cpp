/*
This file is part of DmEngine project.
MIT License

Copyright (c) 2025-2099 Marat Sungatullin

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

#include "memory/DmMemoryManager.h"

#include "common/DmSimpleMacros.h"




#include <cassert>
#include <new>

void* operator new[](size_t nBytes,
                     const char* pName,
                     int flags, unsigned debugFlags,
                     const char* file, int line)
{
    return DmMemoryManager::GetInstance()->AllocateForEastl(nBytes);
}


void* operator new[](size_t nBytes, size_t alignment, size_t alignmentOffset,
                     const char* pName,
                     int flags, unsigned debugFlags,
                     const char* file, int line)
{
    return DmMemoryManager::GetInstance()->AllocateForEastl(nBytes);
}



DmMemoryManager* DmMemoryManager::InstanceOp(Op oper)
{
    const size_t nInstMemSize = DM_ALIGNED_SIZE_OF(DmMemoryManager, 16);
    static uint8_t s_instanceMemory[nInstMemSize];
    static DmMemoryManager* s_pInstance{};

    if (uint32_t(oper) == kOP_GET_OR_CREATE)
    {
        if (s_pInstance)
            return s_pInstance;

        assert(!s_pInstance);
        s_pInstance = ::new((void*)&s_instanceMemory[0]) DmMemoryManager();
        return s_pInstance;
    }
    else if (uint32_t(oper) == kOP_DESTROY)
    {
        if (!s_pInstance)
            return nullptr;
        s_pInstance->~DmMemoryManager();
        s_pInstance = nullptr;
    }
    return nullptr;
}


DmMemoryManager* DmMemoryManager::GetInstance()
{
    return InstanceOp(kOP_GET_OR_CREATE);
}

void DmMemoryManager::DestroyInstance()
{
    InstanceOp(kOP_DESTROY);
}


void* DmMemoryManager::AllocateForEastl(size_t nBytes)
{
    return ::new uint8_t [nBytes];
}
