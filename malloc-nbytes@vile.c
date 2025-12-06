#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@vile"; }
char *getver(void)  { return "rolling"; }
char *getdesc(void) { return "Run C in a REPL"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/vile.git/"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "vile");
}

int
build(void)
{
        return cmd("cc -o vile $(find . -type f -name '*.c') -Iinclude/ -lforge");
}

int
install(void)
{
        return cmd("cp ./vile " FORGE_PREFERRED_INSTALL_PREFIX "/bin/vile");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .deps            = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
