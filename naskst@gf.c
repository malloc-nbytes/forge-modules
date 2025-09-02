#include <forge/forge.h>

char *getname(void) { return "naskst@gf"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "A GDB frontend for Linux"; }
char *getweb(void)  { return "https://github.com/nakst/gf.git"; }

char *download(void) { return git_clone("nakst", "gf"); }
int build(void)      { return cmd("/bin/sh build.sh"); }
int install(void)    { return cmd("cp ./gf2 " FORGE_PREFERRED_INSTALL_PREFIX "/bin/"); }
int uninstall(void)  { return cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/gf2"); }

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
