#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/mitkrb.html

/* TODO: packages that rebuild this:
 * bind utilities
 * Cracklib
 * keyutils
 * openldap
 * yasm
 * libedit
 * cmocka
 * kdcproxy
 * pyrad
 * resolv_wrapper
 */

char *msgs[] = {
        "You need some time sychronization facility on your system",
        " like " YELLOW BOLD "ntp" RESET " since Kerberos won't authenticate",
        "if there is a time difference between a kerberized client and the KDC server.",
        NULL,
};

char **getmsgs(void) { return msgs; }
char *getname(void)  { return "MIT@kerberos"; }
char *getver(void)   { return "v5-1.22.1"; }
char *getdesc(void)  { return "A free implementation of Kerberos 5"; }
char *getweb(void)   { return "https://ist.mit.edu/accounts"; }

char *
download(void)
{
        CMD("wget https://kerberos.org/dist/krb5/1.22/krb5-1.22.1.tar.gz", return NULL);
        CMD("tar -vxf krb5-1.22.1.tar.gz", return NULL);
        CMD("rm krb5-1.22.1.tar.gz", return NULL);
        return "krb5-1.22.1";
}

int
build(void)
{
        CD("src", return 0);
        CMD("sed -i -e '/eq 0/{N;s/12 //}' plugins/kdb/db2/libdb2/test/run.test", return 0);
        CMD("./configure --prefix=/usr         \
            --sysconfdir=$DESTDIR/etc          \
            --localstatedir=$DESTDIR/var/lib   \
            --runstatedir=$DESTDIR/run         \
            --with-system-et                   \
            --with-system-ss                   \
            --with-system-verto=no             \
            --enable-dns-for-realm             \
            --disable-rpath", return 0);
        return make(NULL);
}

int
install(void)
{
        CD("src", return 0);
        if (!make("install"))
                return 0;
        return cmd("cp -vfr ../doc -T $DESTDIR/usr/share/doc/krb5-1.22.1");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = getmsgs,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
