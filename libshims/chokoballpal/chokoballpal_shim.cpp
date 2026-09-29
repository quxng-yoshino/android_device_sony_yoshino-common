#include <cstddef>
#include <new>
#include <ui/GraphicBuffer.h>

// libsomc_chokoballpal.so (Android 9) allocates GraphicBuffer with
// operator new(0x90) and then runs the Android 16 libui constructor,
// which writes a much larger object and corrupts the heap. Its
// operator new import is renamed to cbnwj (see extract-files.py) and
// routed here, so the allocation matches the current GraphicBuffer size.
extern "C" void* cbnwj(size_t size) {
    if (size == 0x90 && size < sizeof(android::GraphicBuffer)) {
        size = sizeof(android::GraphicBuffer);
    }
    return ::operator new(size);
}
