#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libksba.html

char *deps[] = {
        "gpg@libgpg-error-1.55.0",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "gpg@libksba-1.6.7"; }
char *getver(void)   { return "1.6.7"; }
char *getdesc(void)  { return "A library used to make X.509 certificates and making the CMS easily accessible"; }
char *getweb(void)   { return "https://github.com/gpg/libksba"; }

char *
download(void)
{
        CMD("wget https://www.gnupg.org/ftp/gcrypt/libksba/libksba-1.6.7.tar.bz2", return NULL);
        CMD("tar -vxf libksba-1.6.7.tar.bz2", return NULL);
        CMD("rm libksba-1.6.7.tar.bz2", return NULL);
        return "libksba-1.6.7";
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
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
