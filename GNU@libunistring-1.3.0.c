#include <forge/forge.h>

char *rebuild[] = {"GNU@gnuTLS-3.8.10", NULL};

char **getrebuild(void) { return rebuild; }
char *getname(void)  { return "GNU@gnuTLS-3.8.10"; }
char *getver(void)   { return "3.8.10"; }
char *getdesc(void)  { return "Tools which provide a secure layer over a reliable transport layer"; }
char *getweb(void)   { return "https://www.gnupg.org/ftp/gcrypt/gnutls/v3.8"; }

char *
download(void)
{
        CMD("wget https://ftp.gnu.org/gnu/libunistring/libunistring-1.3.tar.xz", return NULL);
        CMD("tar -vxf libunistring-1.3.tar.xz", return NULL);
        CMD("libunistring-1.3.tar.xz", return NULL);
        return "libunistring-1.3";
}

int
build(void)
{
        CMD("./configure --prefix=/usr  \
            --disable-static            \
            --docdir=/usr/share/doc/libunistring-1.3", return 0);
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
        .rebuild         = getrebuild,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};

