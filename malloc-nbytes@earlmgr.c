#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <forge/forge.h>

char *deps[] = {"malloc-nbytes@earl", NULL}; // Must be NULL terminated

char *getname(void) { return "malloc-nbytes@earlmgr"; }
char *getver(void) { return "1.0.0"; }
char *getdesc(void) { return "Manager application for EARL"; }
char **getdeps(void) { return deps; }
char *download(void) {
        return git_clone("malloc-nbytes", "earlmgr");
}
void build(void) {}
void install(void) {
	cd("src");
	char *user = get_prev_user();
	cmd_as("earl ./earlmgr.rl", user);
}
void uninstall(void) {
	cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/earlmgr");
	cmd("rm -r " FORGE_PREFERRED_INSTALL_PREFIX "/include/EARL/mgr");

	char *user = get_prev_user();
	forge_str bashrc = forge_str_from("/home/");
	forge_str_concat(&bashrc, user);
	forge_str_concat(&bashrc, "/.bashrc");
	char **lines = forge_io_read_file_to_lines(forge_str_to_cstr(&bashrc));

	int l1 = -1, l2 = -1;
	for (int i = 0; lines && lines[i]; ++i) {
		if (strncmp(lines[i], "export EARLMGR_INSTALL_LOC=", 26) == 0) {
			printf("removing: `%s` from .bashrc...\n", lines[i]);
			l1 = i;
		}
		if (strncmp(lines[i], "export EARLMGR_IMPORT_LOC=", 25) == 0) {
			printf("removing: `%s` from .bashrc...\n", lines[i]);
			l2 = i;
		}
	}

	forge_str content = forge_str_create();
	for (int i = 0; lines && lines[i]; ++i) {
		if (i == l1 || i == l2) continue;
		forge_str_concat(&content, lines[i]);
		forge_str_append(&content, '\n');
	}

	forge_io_write_file(forge_str_to_cstr(&bashrc), forge_str_to_cstr(&content));

	for (int i = 0; lines && lines[i]; ++i) free(lines[i]);
	if (lines) free(lines);
	forge_str_destroy(&bashrc);
}
void get_changes(void) {
	cmd("git pull");
	cd("src");
	char *user = get_prev_user();
        cmd_as("earlmgr -- update local", user);
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
        .update = forge_pkg_git_update, // or define your own if not using git
         
         // Make this NULL to just re-download the source code
         // or define your own if not using git
        .get_changes = get_changes,
};
