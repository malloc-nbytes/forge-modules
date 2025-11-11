#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/basicnet/nghttp2.html

char *sugg[] = {"libxml@libxml", NULL};
// The following are only used if building the full package instead of only the main libraries: Boost-1.89.0, c-ares-1.34.5, cython-3.1.3, jansson-2.14.1, libevent-2.1.12, sphinx-8.2.3, jemalloc, libev, mruby, and Spdylay.

char *getname(void)  { return "nghttp2@nghttp2"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "HTTP/2 C Library and tools"; }
char *getweb(void)   { return "https://github.com/nghttp2/nghttp2"; }

char *
download(void)
{
        return git_clone("nghttp2", "nghttp2");
}

int
build(void)
{
        //CMD("git submodule update --init", return 0);
        CMD("autoreconf -i", return 0);
        CMD("automake", return 0);
        CMD("autoconf", return 0);
        CMD("./configure --prefix=/usr \
            --disable-static  \
            --enable-lib-only \
            --docdir=/usr/share/doc/nghttp2-1.66.0", return 0);
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
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
