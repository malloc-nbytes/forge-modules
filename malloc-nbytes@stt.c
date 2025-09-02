#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@stt"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "Simple Time Tracker"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/stt.git/"; }

char *download(void) { return git_clone("malloc-nbytes", "stt"); }
int build(void)      { return cmd("cargo build --release"); }
int install(void)    { return cmd("cp ./target/release/stt " FORGE_PREFERRED_INSTALL_PREFIX "/bin"); }
int uninstall(void)  { return cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/stt"); }

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
        .update          = forge_pkg_git_update, // or define your own if not using git
        .get_changes     = forge_pkg_git_pull,
};
