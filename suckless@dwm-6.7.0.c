#include <forge/forge.h>

char *getname(void)  { return "suckless@dwm-6.7.0"; }
char *getver(void)   { return "6.7.0"; }
char *getdesc(void)  { return "A minimal window manager"; }
char *getweb(void)   { return "https://dwm.suckless.org/"; }

char *
download(void)
{
        CMD("wget https://dl.suckless.org/dwm/dwm-6.7.tar.gz", return NULL);
        CMD("tar -vxf dwm-6.7.tar.gz", return NULL);
        CMD("rm dwm-6.7.tar.gz", return NULL);
        return "dwm-6.7";
}

int
build(void)
{
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
