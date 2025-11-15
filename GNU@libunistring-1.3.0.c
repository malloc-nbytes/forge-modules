#include <forge/forge.h>

char *rebuild[] = {"GNU@gnuTLS-3.8.10", "rockdaboot@libpsl-0.21.5", NULL};

char **getrebuild(void) { return rebuild; }
char *getname(void)  { return "GNU@libunistring-1.3.0"; }
char *getver(void)   { return "1.3.0"; }
char *getdesc(void)  { return "Functions for manipulating Unicode strings and for manipulating C strings"; }
char *getweb(void)   { return "https://ftp.gnu.org/gnu/libunistring"; }

char *
download(void)
{
        CMD("wget https://ftp.gnu.org/gnu/libunistring/libunistring-1.3.tar.xz", return NULL);
        CMD("tar -vxf libunistring-1.3.tar.xz", return NULL);
        CMD("rm libunistring-1.3.tar.xz", return NULL);
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

