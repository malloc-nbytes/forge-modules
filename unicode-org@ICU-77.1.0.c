#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/icu.html

char *rebuild[] = {
        "GNOME@libxml2",
        NULL,
};

char **getrebuild(void) { return rebuild; }
char *getname(void)  { return "unicode-org@ICU-77.1.0"; }
char *getver(void)   { return "77.1.0"; }
char *getdesc(void)  { return "C/C++ libraries providing Unicode and Globalization support"; }
char *getweb(void)   { return "https://github.com/unicode-org/icu/"; }

char *
download(void)
{
        CMD("wget https://github.com/unicode-org/icu/releases/download/release-77-1/icu4c-77_1-src.tgz", return NULL);
        CMD("tar -vxf icu4c-77_1-src.tgz", return NULL);
        CMD("rm icu4c-77_1-src.tgz", return NULL);
        return "icu";
}

int
build(void)
{
        if (!cd("source")) return 0;
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
        .deps            = NULL,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = getrebuild,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
