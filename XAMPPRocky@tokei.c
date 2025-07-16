#include <forge/forge.h>

char *deps[] = {/*rust*/NULL}; // Must be NULL terminated

char *getname(void)  { return "XAMPPRocky@tokei"; }
char *getver(void)   { return "1.0.0"; }
char *getdesc(void)  { return "Count your code, quickly"; }
char *download(void) { return git_clone("XAMPPRocky", "tokei"); }
void build(void)     { cmd("cargo build --release"); }
void install(void)   { cmd("cp ./target/release/tokei " FORGE_PREFERRED_INSTALL_PREFIX "/bin/"); }
void uninstall(void) { cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/tokei"); }

FORGE_GLOBAL pkg package = {
        .name        = getname,
        .ver         = getver,
        .desc        = getdesc,
        .deps        = NULL,
        .download    = download,
        .build       = build,
        .install     = install,
        .uninstall   = uninstall,
        .update      = forge_pkg_git_update,
        .get_changes = forge_pkg_git_pull,
};
