#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libgpg-error.html

char *getname(void)  { return "gpg@libgpg-error"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Defines common error values for all GnuPG components"; }
char *getweb(void)   { return "https://github.com/gpg/libgpg-error"; }

char *
download(void)
{
        return git_clone("gpg", "libgpg-error");
}

int
build(void)
{
        CMD("./configure --prefix=/usr", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!make("install")) return 0;
        return cmd("install -v -m644 -D README /usr/share/doc/libgpg-error/README");
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
