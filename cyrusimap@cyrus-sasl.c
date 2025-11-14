#include <forge/forge.h>

#include <stdio.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/cyrus-sasl.html

// rebuild: OpenLDAP@OpenLDAP-2.6.10

char *msgs[] = {
        "See https://www.cyrusimap.org/sasl/sasl/sysadmin.html for information on what to include in the application configuration files.",
        "See file:///usr/share/doc/cyrus-sasl-2.1.28/LDAP_SASLAUTHD for configuring saslauthd with OpenLDAP.",
        "See https://www.cyrusimap.org/sasl/sasl/gssapi.html#gssapi for configuring saslauthd with Kerberos.",
        NULL,
};

char *sugg[] = {
        "OpenLDAP@lmdb-0.9.33",
        NULL,
};

char *rebuilds[] = {
        "OpenLDAP@OpenLDAP-2.6.10",
        NULL,
};

char **getrebuilds(void) { return rebuilds; }
char **getsugg(void) { return sugg; }
char **getmsgs(void) { return msgs; }
char *getname(void)  { return "cyrusimap@cyrus-sasl"; }
char *getver(void)   { return "2.1.28"; }
char *getdesc(void)  { return "Simple Authentication and Security Layer implementation"; }
char *getweb(void)   { return "https://github.com/cyrusimap/cyrus-sasl"; }

char *
download(void)
{
        CMD("wget https://github.com/cyrusimap/cyrus-sasl/releases/download/cyrus-sasl-2.1.28/cyrus-sasl-2.1.28.tar.gz",
            return NULL);
        CMD("tar -vxf cyrus-sasl-2.1.28.tar.gz", return NULL);
        CMD("rm cyrus-sasl-2.1.28.tar.gz", return 0);
        return "cyrus-sasl-2.1.28";
}

int
build(void)
{
        printf(YELLOW "Note" RESET ": This package does not support parallel build.\n");

        printf("Applying patch...\n");
        CMD("wget https://www.linuxfromscratch.org/patches/blfs/12.4/cyrus-sasl-2.1.28-gcc15_fixes-1.patch -P ..", return 0);
        CMD("patch -Np1 -i ../cyrus-sasl-2.1.28-gcc15_fixes-1.patch", return 0);
        printf("Done\n");

        CMD("autoreconf -fiv", return 0);
        CMD("sed '/saslint/a #include <time.h>' -i lib/saslutil.c", return 0);
        CMD("sed '/plugin_common/a #include <time.h>' -i plugins/cram.c", return 0);
        CMD("./configure --prefix=/usr          \
            --sysconfdir=/etc                   \
            --enable-auth-sasldb                \
            --with-dblib=lmdb                   \
            --with-dbpath=/var/lib/sasl/sasldb2 \
            --with-sphinx-build=no              \
            --with-saslauthd=/var/run/saslauthd", return 0);
        return cmd("make -j1");
}

int
install(void)
{
        if (!make("install")) return 0;
        CMD("install -v -dm755 $DESTDIR/usr/share/doc/cyrus-sasl-2.1.28/html", return 0);
        CMD("install -v -m644 saslauthd/LDAP_SASLAUTHD $DESTDIR/usr/share/doc/cyrus-sasl-2.1.28", return 0);
        CMD("install -v -m644  doc/legacy/*.html $DESTDIR/usr/share/doc/cyrus-sasl-2.1.28/html", return 0);
        return cmd("install -v -dm700 $DESTDIR/var/lib/sasl");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = getmsgs,
        .suggested       = getsugg,
        .rebuild         = getrebuilds,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
