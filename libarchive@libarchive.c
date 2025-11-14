#include <forge/forge.h>

char *getname(void)  { return "libarchive@libarchive"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Multi-format archive and compression library"; }
char *getweb(void)   { return "https://github.com/libarchive/libarchive"; }

char *
download(void)
{
        return git_clone("libarchive", "libarchive");
}

int
build(void)
{
        CMD("autoreconf -iv", return 0);
        CMD("./configure --prefix=/usr --disable-static", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!make("install")) return 0;
        return cmd("ln -sfv bsdunzip $DESTDIR/usr/bin/unzip");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
