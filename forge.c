#include <forge/forge.h>

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
        CMD("autoreconf -iv", return 0);
        CMD("./configure --prefix=/usr --libdir=/usr/lib64", return 0);
        CMD("cp -v /usr/include/forge/conf.h ./src/forge/conf.h", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!make("install")) return 0;

        // Remove conf.h to preserve user config
        cmd("rm -f $DESTDIR/usr/include/forge/conf.h");

        // Install forge binary to temporary name
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
        .download    = download,
        .build       = build,
        .install     = install,
        .uninstall   = NULL,
        .update      = forge_pkg_git_update,
        .get_changes = forge_pkg_git_pull,
};
