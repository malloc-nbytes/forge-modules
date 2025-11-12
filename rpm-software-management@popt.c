#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/popt.html

char *getname(void)  { return "rpm-software-management@popt"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "C library for parsing command line parameters"; }
char *getweb(void)   { return "https://github.com/rpm-software-management/popt"; }

char *
download(void)
{
        return git_clone("rpm-software-management", "popt");
}

int
build(void)
{
        CMD("autoreconf -iv", return 0);
        CMD("./configure --prefix=/usr --disable-static", return 0);
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
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
