#include <forge/forge.h>

char *deps[] = {
        "libarchive@libarchive",
        "libuv@libuv",
        "nghttp2@nghttp2",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "Kitware@cmake"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Another build system"; }
char *getweb(void)   { return "https://github.com/Kitware/CMake"; }

char *
download(void)
{
        CMD("git clone -b release https://github.com/Kitware/CMake.git cmake --depth=1", return NULL);
        return "cmake";
}

int
build(void)
{
        CMD("sed -i '/\"lib64\"/s/64//' Modules/GNUInstallDirs.cmake", return 0);
        CMD("MAKEFLAGS=-j" FORGE_PREFERRED_MAKEFILE_JFLAGS " ./bootstrap --prefix=/usr \
            --system-libs        \
            --mandir=/share/man  \
            --no-system-jsoncpp  \
            --no-system-cppdap   \
            --no-system-librhash \
            --docdir=/share/doc/cmake-4.1.0", return 0);
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
