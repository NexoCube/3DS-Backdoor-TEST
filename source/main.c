#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include "global_backdoor.h"
#include "kernel_patches.h"

#define HBMENU_ID 0x000400000D921E00
#define HBMENU_MEDIATYPE 1 // SDCARD

int main(int argc, char **argv)
{

    bool isNew3ds = false;

    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    nsInit();
    aptInit();

    osSetSpeedupEnable(true);

    APT_CheckNew3DS(&isNew3ds);
    printf("3DS Kernel11 Code Exec testing\n");
    printf("Thanks Mrrraouu for the snippets ! \n\n");
    printf("System type: %s\n\n", isNew3ds ? "New 3DS" : "Old 3DS/2DS");


    if(checkSvcGlobalBackdoor())
    {
        printf("svcGlobalBackdoor was found\n");
        initsrv_allservices();
        patch_svcaccesstable();
    }
    else
        printf("svcGlobalBackdoor is not implemented\n");


    printf("\nPress SELECT to exit.\n");

    while(aptMainLoop())
    {
        hidScanInput();
        if(hidKeysDown() & KEY_SELECT)
            break;

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    aptExit();
    nsExit();
    gfxExit();

}