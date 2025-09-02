#include <forge/forge.h>

#define INSTALL_PATH FORGE_PREFERRED_INSTALL_PREFIX "/bin/rox-filer"

char *getname(void) { return "rox-desktop@rox-filer"; }
char *getver(void)  { return "2.11.0"; }
char *getdesc(void) { return "ROX file manager"; }
char *getweb(void)  { return "https://www.github.com/rox-desktop/rox-filer.git/"; }

char *download(void) {
        return git_clone("rox-desktop", "rox-filer");
}

int build(void) {
        cd("ROX-Filer");
        mkdirp("build");

        if (!forge_io_filepath_exists("./src/configure")) {
                cd("src");
                CMD("autoconf", return 0);
                cd("..");
        }

        cd("build");
        if (!configure("../src/", NULL)) return 0;

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
