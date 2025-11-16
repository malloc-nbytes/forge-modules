#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/libpwquality.html

char *deps[] = {
        "cracklib@cracklib",
        "Linux-PAM@Linux-PAM-1.7.1",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "libpwquality@libpwquality-1.4.5"; }
char *getver(void)   { return "1.4.5"; }
char *getdesc(void)  { return "Functions for password quality checking"; }
char *getweb(void)   { return "https://github.com/libpwquality/libpwquality"; }

char *
download(void)
{
        CMD("wget https://github.com/libpwquality/libpwquality/releases/download/libpwquality-1.4.5/libpwquality-1.4.5.tar.bz2", return NULL);
        CMD("tar -vxf libpwquality-1.4.5.tar.bz2", return NULL);
        CMD("rm libpwquality-1.4.5.tar.bz2", return NULL);
        return "libpwquality-1.4.5";
}

int
build(void)
{
        CMD("./configure --prefix=/usr         \
            --disable-static                   \
            --with-securedir=/usr/lib/security \
            --disable-python-bindings", return 0);
        if (!make(NULL)) return 0;
        return cmd("pip3 wheel -w dist --no-build-isolation --no-deps --no-cache-dir $PWD/python");
}

int
install(void)
{
        if (!make("install")) return 0;
        return cmd("pip3 install --root=$DESTDIR --no-index --find-links dist --no-user pwquality");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
