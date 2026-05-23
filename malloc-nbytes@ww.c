#include <forge/forge.h>

char *msgs[] = {
        "This editor is a WIP. It may not function properly!",
        NULL,
};

char **getmsgs(void) { return msgs; }
char *getname(void)  { return "malloc-nbytes@ww"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "A terminal text editor for Emacs fans"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/ww.git/"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "ww");
}

int
build(void)
{
        CD("src", return 0);
        CMD(forge_cstr_builder("python3 premake.py --prefix=",
             FORGE_PREFERRED_INSTALL_PREFIX, NULL), return 0);
        if (!make(NULL)) return 0;
        return cmd("strip -v bin/ww");
}

int
install(void)
{
        CD("src", return 0);
        return make("install");
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
