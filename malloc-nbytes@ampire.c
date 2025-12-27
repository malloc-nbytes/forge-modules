#include <forge/forge.h>

char *msgs[] = {
        "Remember to run `ldconfig`!",
        NULL,
};

char **getmsgs(void) { return msgs; }
char *getname(void)  { return "malloc-nbytes@ampire"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "A music player in the terminal"; }
char *getweb(void)   { return "https://www.github.com/malloc-nbytes/ampire.git/"; }

char *
download(void)
{
        CMD("git clone https://www.github.com/malloc-nbytes/ampire.git/ --recurse-submodules --shallow-submodules --depth=1", return NULL);
        return "ampire";
}

int
build(void)
{
        if (!mkdirp("build")) return 0;
        CD("build", return 0);
        CMD("cmake -S .. -B .", return 0);
        return make(NULL);
}

int
install(void)
{
        CD("build", return 0);
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
