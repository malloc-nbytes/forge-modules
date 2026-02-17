#include <forge/forge.h>

char *getname(void)  { return "suckless@dmenu-5.4.0"; }
char *getver(void)   { return "5.4.0"; }
char *getdesc(void)  { return "A dynamic menu for X"; }
char *getweb(void)   { return "https://tools.suckless.org/dmenu/"; }

char *
download(void)
{
        CMD("wget https://dl.suckless.org/tools/dmenu-5.4.tar.gz", return NULL);
        CMD("tar -vxf dmenu-5.4.tar.gz", return NULL);
        CMD("rm dmenu-5.4.tar.gz", return NULL);
        return "dmenu-5.4";
}

int
build(void)
{
        return make(NULL);
}

int
install(void)
{
        CMD("mv stest " FORGE_PREFERRED_INSTALL_PREFIX "/bin/stest", return 0);
        CMD("mv dmenu_path " FORGE_PREFERRED_INSTALL_PREFIX "/bin/dmenu_path", return 0);
        CMD("mv dmenu_run " FORGE_PREFERRED_INSTALL_PREFIX "/bin/dmenu_run", return 0);
        return cmd("mv dmenu " FORGE_PREFERRED_INSTALL_PREFIX "/bin/dmenu");
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
