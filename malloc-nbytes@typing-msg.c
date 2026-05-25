#include <forge/forge.h>

char *getname(void)  { return "malloc-nbytes@typing-msg"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Play a typing animation in the terminal"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/typing-msg.git/"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "typing-msg");
}

int
build(void)
{
        return cmd("sh build.sh");
}

int
install(void)
{
        CMD("install -d " FORGE_PREFERRED_INSTALL_PREFIX "/bin", return 0);
        return cmd("install -m 755 ./typing-msg " FORGE_PREFERRED_INSTALL_PREFIX "/bin/typing-msg");
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
