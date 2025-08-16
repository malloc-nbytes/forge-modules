#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>

#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes@i3conf"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "A (almost) stock i3 config"; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("malloc-nbytes", "i3-config");
}
int build(void) { return 1; }
int install(void) {
        char *user = env("SUDO_USER");
        forge_str config_fp = forge_str_from("/home/");
        forge_str_concat(&config_fp, user);
        forge_str_concat(&config_fp, "/.config/i3/");

        mkdirp(forge_str_to_cstr(&config_fp));

        char buf[256] = {0};
        sprintf(buf, "cp ./config %s", config_fp.data);
        cmd(buf);

        forge_str i3config = forge_str_from(forge_str_to_cstr(&config_fp));
        forge_str_concat(&i3config, "config");

        change_file_owner(forge_str_to_cstr(&i3config), user);

        cmd("cp i3status.conf /etc/i3status.conf");

        forge_str_destroy(&config_fp);
        forge_str_destroy(&i3config);

        return 1;
}
int uninstall(void) { return 1; }

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
