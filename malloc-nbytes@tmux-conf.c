#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>

#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@tmux-conf"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "My config for tmux"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/tmux-conf.git/"; }

char *download(void) {
        return git_clone("malloc-nbytes", "tmux-conf");
}

int build(void) { return 1; }

int install(void) {
        char *user = env("SUDO_USER");
        forge_str config_fp = forge_str_from("/home/");
        forge_str_concat(&config_fp, user);
        forge_str_concat(&config_fp, "/.tmux.conf");

        if (forge_io_filepath_exists(config_fp.data)) {
                fprintf(stderr, "the config file `%s` already exists, it must not exist\n",
                        config_fp.data);
                forge_str_destroy(&config_fp);
                return 0;
        }

        char *buf = forge_cstr_builder("cp ./.tmux.conf ", config_fp.data, NULL);
        cmd(buf);

        change_file_owner(buf, user);

        forge_str_destroy(&config_fp);
        free(buf);

        return 1;
}

int uninstall(void) { return 1; }

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
