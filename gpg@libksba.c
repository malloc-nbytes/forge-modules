#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libksba.html

char *deps[] = {
        "gpg@libgpg-error",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "gpg@libksba"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "A library used to make X.509 certificates and making the CMS easily accessible"; }
char *getweb(void)   { return "https://github.com/gpg/libksba"; }

char *
download(void)
{
        return git_clone("gpg", "libksba");
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
        .deps            = getdeps,
        .msgs            = NULL,
        .suggested       = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
