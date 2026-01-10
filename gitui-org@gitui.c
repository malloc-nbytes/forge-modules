#include <forge/forge.h>

char *getname(void)     { return "gitui-org@gitui"; }
char *getver(void)      { return "rolling"; }
char *getdesc(void)     { return "Fast terminal-ui for git"; }
char *getweb(void)      { return "https://github.com/gitui-org/gitui"; }

char *
download(void)
{
        CMD("git clone https://github.com/gitui-org/gitui.git --depth=1", return NULL);
        return "gitui";
}

int
build(void)
{
        CMD("cargo build --release", return 0);
}

int
install(void)
{
        return cmd("cargo install gitui --locked");
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
