#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/npth.html

char *getname(void)  { return "gpg@nPth"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Library that provides non-preemptive priority-based scheduling for multiple threads"; }
char *getweb(void)   { return "https://github.com/gpg/npth"; }

char *
download(void)
{
        return git_clone("gpg", "npth");
}

int
build(void)
{
        CMD("autoreconf -iv", return 0);
        CMD("./configure --prefix=/usr", return 0);
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
