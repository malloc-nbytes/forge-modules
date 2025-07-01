#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes@stt"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Simple Time Tracker"; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("malloc-nbytes", "stt");
}
void build(void) {
	cmd("cargo build --release");
}
void install(void) {
	cmd("cp ./target/release/stt " FORGE_PREFERRED_INSTALL_PREFIX "/bin");
}
void uninstall(void) {
	cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/stt");
}

FORGE_GLOBAL pkg package = {
        .name = getname,
        .ver = getver,
        .desc = getdesc,
        .deps = NULL,
        .download = download,
        .build = build,
        .install = install,
        .uninstall = uninstall,
        .update = forge_pkg_git_update, // or define your own if not using git
};
