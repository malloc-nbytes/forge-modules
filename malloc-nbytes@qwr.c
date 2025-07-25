#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@qwr"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "A qemu wrapper for managing VMs"; }
char *download(void) {
        return git_clone("malloc-nbytes", "qwr");
}
void build(void) {
        cmd("/bin/sh build.sh");
}
void install(void) {
        cmd("cp qwr " FORGE_PREFERRED_INSTALL_PREFIX "/bin");
}
void uninstall(void) {
        cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/qwr");
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
        .update = forge_pkg_git_update,
        .get_changes = forge_pkg_git_pull,
};
