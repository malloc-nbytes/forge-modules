#include <forge/forge.h>

char *deps[] = {"malloc-nbytes@earl", NULL};

char *getname(void) { return "malloc-nbytes@common-scripts"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Just some common scripts that I use"; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("malloc-nbytes", "common-scripts");
}
void build(void) {}

void install(void) {
        const char *install_path = FORGE_PREFERRED_INSTALL_PREFIX "/bin";
        char **files = ls(".");

        for (size_t i = 0; files[i]; ++i) {
                if (!strcmp(forge_io_file_ext(files[i]), "rl")) {
                        char *cmd_str = forge_str_builder("cp ", files[i], " ", install_path, NULL);
                        char *chmod_str = forge_str_builder("chmod +x ", install_path, "/", files[i], NULL);
                        cmd(cmd_str);
                        cmd(chmod_str);
                        free(cmd_str);
                        free(chmod_str);
                }
                free(files[i]);
        }
        free(files);
}

void uninstall(void) {
        const char *install_path = FORGE_PREFERRED_INSTALL_PREFIX "/bin";
        char **files = ls(".");

        for (size_t i = 0; files[i]; ++i) {
                if (!strcmp(forge_io_file_ext(files[i]), "rl")) {
                        char *cmd_str = forge_str_builder("rm ", install_path, "/", files[i], NULL);
                        cmd(cmd_str);
                        free(cmd_str);
                }
                free(files[i]);
        }
        free(files);
}

FORGE_GLOBAL pkg package = {
        .name = getname,
        .ver = getver,
        .desc = getdesc,
        .deps = getdeps,
        .download = download,
        .build = build,
        .install = install,
        .uninstall = uninstall,
        .update = forge_pkg_git_update,
        .get_changes = forge_pkg_git_pull,
};
