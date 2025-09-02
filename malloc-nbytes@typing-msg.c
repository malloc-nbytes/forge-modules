#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@typing-msg"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "A small program to simulate typing a message"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/typing-msg.git/"; }

char *download(void) { return git_clone("malloc-nbytes", "typing-msg"); }
int build(void)      { return cmd("./build.sh"); }
int install(void)    { return cmd("cp ./typing-msg " FORGE_PREFERRED_INSTALL_PREFIX "/bin"); }
int uninstall(void)  { return cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/typing-msg"); }

FORGE_GLOBAL pkg package = {
        .name        = getname,
        .ver         = getver,
        .desc        = getdesc,
        .web         = getweb,
        .deps        = NULL,
        .download    = download,
        .build       = build,
        .install     = install,
        .uninstall   = uninstall,
        .update      = forge_pkg_git_update,
        .get_changes = forge_pkg_git_pull,
};
