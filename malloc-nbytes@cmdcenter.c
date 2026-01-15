#include <forge/forge.h>

char *msgs[] = {
        "This program only works with X11.",
        NULL,
};

char **getmsgs(void) { return msgs; }
char *getname(void)  { return "malloc-nbytes@cmdcenter"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Helpful Linux toggle-ables"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/cmdcenter.git/"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "cmdcenter");
}

int
build(void)
{
        CD("src", return 0);
        return cmd("/bin/bash build.sh");
}

int
install(void)
{
        CD("src", return 0);
        return cmd("install -m 755 ./cmdcenter " FORGE_PREFERRED_INSTALL_PREFIX "/bin/cmdcenter");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = getmsgs,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
