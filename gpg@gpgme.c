#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/gpgme.html

char *deps[] = {
        "gpg@libassuan-3.0.2",
        NULL,
};

char *sugg[] = {
        "gpg@GnuPG-2.4.8",
        NULL,
};

char **getdeps(void) { return deps; }
char **getsugg(void) { return sugg; }
char *getname(void)  { return "gpg@gpgme"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Cryptography support to be added to a program"; }
char *getweb(void)   { return "https://github.com/gpg/gpgme"; }

char *
download(void)
{
        return git_clone("gpg", "gpgme");
}

int
build(void)
{
        CMD("autoreconf -iv", return 0);
        if (!mkdirp("build")) return 0;
        CD("build", return 0);
        CMD("../configure --prefix=/usr  \
             --disable-static", return 0);
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
        .suggested       = getsugg,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
