#include <forge/forge.h>

char *getname(void)  { return "malloc-nbytes@qcl"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "A header-only config language"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/qcl.git/"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "qcl");
}

int
build(void)
{
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
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
