/**
 * This is the module for updating forge itself. I do not
 * recommend modifying this unless you know what you are doing.
 *
 * It uses a 'hack' to update itself, which must also work
 * in the package manager itself.
 *
 * Basically, if anything is changed in here, it will break.
 *
 * ¯\(ツ)/¯
 */

#include <forge/forge.h>

#include <string.h>

char *getname(void)  { return "forge"; }
char *getver(void)   { return "1.0.0"; }
char *getdesc(void)  { return "Forge your system"; }
char *getweb(void)   { return "https://github.com/malloc-nbytes/forge"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "forge");
}

int
build(void)
{
        const char *prefix = env("FORGE_PREFIX"); // hack
        const char *libdir = env("FORGE_LIBDIR"); // hack

        if (!prefix || !libdir || !strlen(prefix) || !strlen(libdir)) {
                printf(RED BOLD "Invalid $FORGE_PREFIX or $FORGE_LIBDIR, something went wrong" RESET "\n");
                return 0;
        }

        char *conf = forge_cstr_builder("./configure --prefix=", prefix, " --libdir=", libdir, NULL);

        CMD("autoreconf -iv", return 0);
        CMD(conf, return 0);
        CMD("cp -v /usr/include/forge/conf.h ./src/forge/conf.h", return 0);

        return make(NULL);
}

int
install(void)
{
        if (!make("install")) return 0;

        // Remove conf.h to preserve user config (hack).
        cmd("mv -v $DESTDIR/usr/include/forge/conf.h $DESTDIR/buildsrc");

        // Install forge binary to temporary name (hack).
        char *cmd_mv = forge_cstr_builder(
                "mv $DESTDIR/usr/bin/forge $DESTDIR/usr/bin/forge.new && "
                "chmod 755 $DESTDIR/usr/bin/forge.new",
                NULL
        );

        CMD(cmd_mv, { free(cmd_mv); return 0; });

        free(cmd_mv);

        return 1;
}

FORGE_GLOBAL pkg package = {
        .name        = getname,
        .ver         = getver,
        .desc        = getdesc,
        .web         = getweb,
        .deps        = NULL,
        .msgs        = NULL,
        .suggested   = NULL,
        .rebuild     = NULL,
        .download    = download,
        .build       = build,
        .install     = install,
        .uninstall   = NULL,
        .update      = forge_pkg_git_update,
        .get_changes = forge_pkg_git_pull,
};
