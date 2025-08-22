#include <forge/forge.h>

#define INSTALL_PATH FORGE_PREFERRED_INSTALL_PREFIX "/bin/rox-filer"

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "rox-desktop@rox-filer"; }
char *getver(void) { return "2.11.0"; }
char *getdesc(void) { return "ROX file manager"; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("rox-desktop", "rox-filer");
}
int build(void) {
        cd("ROX-Filer");
        mkdirp("build");

        if (!forge_io_filepath_exists("./src/configure")) {
                cd("src");
                cmd("autoconf");
                cd("..");
        }

        cd("build");
        configure("../src/", NULL);

        return make(NULL);
}
int install(void) {
        cd("ROX-Filer");
        return cmd("cp ./ROX-Filer " INSTALL_PATH);
}
int uninstall(void) {
        return cmd("rm " INSTALL_PATH);
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
