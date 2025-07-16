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
#ifndef DM_MEMORY_MANAGER_H
#define DM_MEMORY_MANAGER_H

#include <EABase/eabase.h>

#include "eastl_related/DmEastlNeeds.h"

class DmMemoryManager
{
public:

    static DmMemoryManager* GetInstance();
    static void DestroyInstance();

    void* AllocateForEastl(size_t nBytes);
private:
    enum Op
    {
        kOP_GET_OR_CREATE,
        kOP_DESTROY
    };

    static DmMemoryManager* InstanceOp(Op oper);
};

#endif // DM_MEMORY_MANAGER_H

