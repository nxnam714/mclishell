#include <stdio.h>
#include "AtOsal.h"

static void CliStart(void)
{
    ATCliStart();
}

static int Run(void)
{
    // if (!Init())
    //     {
    //     mPrintError("Init\r\n");

    //     AppCleanup();
    //     return EXIT_FAILURE;
    //     }

    CliStart();
//    AppCleanup();

    return 0;
}

int main()
{
    //SystemInit();

    return Run();
    return 0;
}