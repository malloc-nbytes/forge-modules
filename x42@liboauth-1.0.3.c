#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/liboauth.html

char *deps[] = {
        "cURL@cURL-8.15.0",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "x42@liboauth-1.0.3"; }
char *getver(void)   { return "1.0.3"; }
char *getdesc(void)  { return "POSIX-C functions implementing the OAuth Core RFC 5849 standard"; }
char *getweb(void)   { return "https://sourceforge.net/projects/liboauth/files/"; }

char *
download(void)
{
        CMD("wget https://downloads.sourceforge.net/liboauth/", return NULL);
        CMD("tar -vxf liboauth-1.0.3.tar.gz", return NULL);
        CMD("rm liboauth-1.0.3.tar.gz", return NULL);
        return "liboauth-1.0.3";
}

int
build(void)
{
        CMD("wget \
                 https://www.linuxfromscratch.org/patches/blfs/12.4/liboauth-1.0.3-openssl-1.1.0-3.patch \
                 --directory-prefix=..", return 0);
        CMD("patch -Np1 -i ../liboauth-1.0.3-openssl-1.1.0-3.patch", return 0);
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
