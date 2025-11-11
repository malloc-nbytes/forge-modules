#include <forge/forge.h>

char *msgs[] = {
        "Install Qt for Qt-based GUI",
        "Install sphinx for building documents",
        NULL,
};

char *sugg[] = {
        "GNU@gcc",
        "git@git",
        NULL,
};

char *getname(void)  { return "Kitware@cmake"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "A music player in the terminal"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/ampire.git/"; }
char **getmsgs(void) { return msgs; }
char **getsuggested(void) { return sugg; }

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
        CMD("./bootstrap --prefix=/usr \
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
        .deps            = NULL,
        .msgs            = getmsgs,
        .suggested       = getsuggested,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
