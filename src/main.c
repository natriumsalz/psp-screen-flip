#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspthreadman.h>
#include <stdint.h>
#include "screenflip.h"

PSP_MODULE_INFO("ScreenFlip", PSP_MODULE_USER, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

static volatile int g_running = 1;
static volatile int g_enabled = 0;

/*
 * This thread implements the requested SELECT toggle.
 * It deliberately does not claim to rotate the live game framebuffer:
 * that requires a firmware/game-compatible display hook (see README).
 */
static int input_thread(SceSize args, void *argp)
{
    SceCtrlData pad;
    int previous = 0;

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    while (g_running) {
        sceCtrlPeekBufferPositive(&pad, 1);
        int down = (pad.Buttons & PSP_CTRL_SELECT) != 0;

        if (down && !previous) {
            g_enabled = !g_enabled;
            /* Debug output is useful in PPSSPP/dev builds. */
            pspDebugScreenSetXY(0, 0);
            pspDebugScreenPrintf("ScreenFlip: %s   ",
                                 g_enabled ? "ON" : "OFF");
        }
        previous = down;
        sceKernelDelayThread(16000);
    }
    return 0;
}

int module_start(SceSize args, void *argp)
{
    SceUID thid = sceKernelCreateThread(
        "ScreenFlipInput", input_thread, 0x18, 0x1000, 0, NULL);
    if (thid >= 0) sceKernelStartThread(thid, 0, NULL);
    return 0;
}

int module_stop(SceSize args, void *argp)
{
    g_running = 0;
    return 0;
}

/* Exposed for the eventual display-hook integration. */
int screenflip_is_enabled(void) { return g_enabled; }
