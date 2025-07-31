#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@vile"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Manipulate C files easily"; }
char *download(void) {
        return git_clone("malloc-nbytes", "vile");
}
void build(void) {
        cd("src");
        cmd("/bin/sh build.sh");
}
void install(void) {
        cd("src");
        cmd("cp vile " FORGE_PREFERRED_INSTALL_PREFIX "/bin");
}
void uninstall(void) {
        cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/vile");
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
