#include <forge/forge.h>

#include <stdio.h>

#define SCRATCH "00-dwm-scratchpad.diff"
#define GAPS    "01-dwm-fullgaps-6.4.diff"
#define AWESOME "dwm-awesomebar-6.6.diff"

char *getname(void)  { return "suckless@dwm-6.7.0"; }
char *getver(void)   { return "6.7.0"; }
char *getdesc(void)  { return "DWM with some patches"; }
char *getweb(void)   { return "https://dwm.suckless.org/"; }

char *
download(void)
{
        CMD("wget -O dwm++-6.7.tar.gz https://dl.suckless.org/dwm/dwm-6.7.tar.gz", return NULL);
        CMD("tar -xzf dwm++-6.7.tar.gz --transform='s/^dwm-6.7/dwm++-6.7/'", return NULL);
        CMD("rm dwm++-6.7.tar.gz", return NULL);

        CD("dwm++-6.7", return NULL);

        CMD("wget https://dwm.suckless.org/patches/scratchpad/dwm-scratchpad-20240321-061e9fe.diff", return NULL);
        CMD("wget https://dwm.suckless.org/patches/fullgaps/dwm-fullgaps-6.4.diff", return NULL);
        CMD("wget https://dwm.suckless.org/patches/awesomebar/dwm-awesomebar-20250923-6.6.diff", return NULL);

        CMD("mv dwm-scratchpad-20240321-061e9fe.diff " SCRATCH, return NULL);
        CMD("mv dwm-fullgaps-6.4.diff " GAPS, return NULL);
        CMD("mv dwm-awesomebar-20250923-6.6.diff " AWESOME, return NULL);

        CMD("wget https://raw.githubusercontent.com/malloc-nbytes/dwm-config/refs/heads/main/dwm-6.6", return NULL);
        CMD("mv dwm-6.6 config.h", return NULL);

        return "dwm++-6.7";
}

int
build(void)
{
        printf("============= PATCHING =============\n");

        CMD("patch -p1 < " SCRATCH, return 0);
        CMD("patch -p1 < " GAPS, return 0);
        CMD("patch -p1 < " AWESOME, return 0);

        return make(NULL);
}

int
install(void)
{
        return make("install");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
