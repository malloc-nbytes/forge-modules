#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/basicnet/libpsl.html

char *sugg[] = {
        "GNU@libidn2-2.3.8",
        "GNU@libunistring-1.3.0",
        NULL,
};

char *rebuild[] = {
        "cURL@cURL-8.15.0",
        NULL,
};

char **getsugg(void) { return sugg; }
char *getname(void)  { return "rockdaboot@libpsl-0.21.5"; }
char *getver(void)   { return "0.21.5"; }
char *getdesc(void)  { return "C library for the Public Suffix List"; }
char *getweb(void)   { return "https://github.com/rockdaboot/libpsl"; }

char *
download(void)
{
        CMD("wget https://github.com/rockdaboot/libpsl/releases/download/0.21.5/libpsl-0.21.5.tar.gz", return NULL);
        CMD("tar -vxf libpsl-0.21.5.tar.gz", return NULL);
        CMD("rm libpsl-0.21.5.tar.gz", return NULL);
        return "libpsl-0.21.5";
}

int
build(void)
{
        if (!mkdirp("build")) return 0;
        CD("build", return 0);
        CMD("meson setup --prefix=/usr --buildtype=release", return 0);
        return cmd("ninja");
}

int
install(void)
{
        CD("build", return 0);
        return cmd("ninja install");
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
