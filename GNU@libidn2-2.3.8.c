#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libidn2.html

char *sugg[] = {
        "GNU@libunistring-1.3.0",
        NULL,
};

char **getsugg(void) { return sugg; }
char *getname(void)  { return "GNU@libidn2-2.3.8"; }
char *getver(void)   { return "2.3.8"; }
char *getdesc(void)  { return "Internationalized string handling based on (IETF)'s IDN working group."; }
char *getweb(void)   { return "https://ftp.gnu.org/gnu/libidn/"; }

char *
download(void)
{
        CMD("wget https://ftp.gnu.org/gnu/libidn/libidn2-2.3.8.tar.gz", return NULL);
        CMD("tar -vxf libidn2-2.3.8.tar.gz", return NULL);
        CMD("rm libidn2-2.3.8.tar.gz", return NULL);
        return "libidn2-2.3.8";
}

int
build(void)
{
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
        .suggested       = getsugg,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
