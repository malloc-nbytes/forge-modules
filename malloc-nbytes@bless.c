#include <forge/forge.h>

char *deps[] = {
        "Kitware@cmake",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void) { return "malloc-nbytes@bless"; }
char *getver(void)  { return "rolling"; }
char *getdesc(void) { return "A \"better\" version of `less`"; }
char *getweb(void)  { return "https://github.com/malloc-nbytes/bless"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "bless");
}

int
build(void)
{
        if (!mkdirp("build")) return 0;
        CD("build", return 0);
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
        .deps            = getdeps,
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
