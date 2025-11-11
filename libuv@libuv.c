#include <forge/forge.h>

char *sugg[] = {"sphinx@sphinx", NULL};

char *getname(void)  { return "libuv@libuv"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Cross-platform asynchronous I/O "; }
char *getweb(void)   { return "https://github.com/libuv/libuv"; }

char *
download(void)
{
        return git_clone("libuv", "libuv");
}

int
build(void)
{
        CMD("sh autogen.sh", return 0);
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
        .suggested       = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
