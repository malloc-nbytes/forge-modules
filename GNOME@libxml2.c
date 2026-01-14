#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/libxml2.html

char *deps[] = {
        "unicode-org@ICU-77.1.0",
        NULL,
};

char *rebuild[] = {
        "GNOME@libxslt-1.1.43",
        NULL,
};

char **getrebuild(void) { return rebuild; }
char **getdeps(void) { return deps; }
char *getname(void)  { return "GNOME@libxml2"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Libraries and utilities used for parsing XML files"; }
char *getweb(void)   { return "https://github.com/GNOME/libxml2"; }

char *
download(void)
{
        return git_clone("GNOME", "libxml2");
}

int
build(void)
{
        CMD("autoreconf -iv", return 0);
        CMD("./configure --prefix=/usr     \
                --sysconfdir=/etc          \
                --disable-static           \
                --with-history             \
                --with-icu                 \
                PYTHON=/usr/bin/python3    \
                --docdir=/usr/share/doc/libxml2", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!make("install")) return 0;
        CMD("rm -vf $DESTDIR/usr/lib/libxml2.la", return 0);
        return cmd("sed '/libs=/s/xml2.*/xml2\"/' -i $DESTDIR/usr/bin/xml2-config");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = getrebuild,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
