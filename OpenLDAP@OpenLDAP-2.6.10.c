#include <forge/forge.h>

#include <stdio.h>

// https://www.linuxfromscratch.org/blfs/view/stable/server/openldap.html

char *msgs[] = {
        "For information on how to set up OpenLDAP, see:",
        "    " YELLOW "https://www.linuxfromscratch.org/blfs/view/stable/server/openldap.html" RESET,
        NULL,
};

char *sugg[] = {
        "cyrusimap@cyrus-sasl",
        NULL,
};

char *deps[] = {
        "cyrusimap@cyrus-sasl",
        NULL,
};

char **getdeps(void) { return deps; }
char **getmsgs(void) { return msgs; }
char **getsugg(void) { return sugg; }
char *getname(void)  { return "OpenLDAP@OpenLDAP-2.6.10"; }
char *getver(void)   { return "2.6.10"; }
char *getdesc(void)  { return "Implementation of the Lightweight Directory Access Protocol"; }
char *getweb(void)   { return "https://www.openldap.org/software/download/OpenLDAP/openldap-release/"; }

char *
download(void)
{
        CMD("wget https://www.openldap.org/software/download/OpenLDAP/openldap-release/openldap-2.6.10.tgz",
            return NULL);
        CMD("tar -vxf openldap-2.6.10.tgz", return NULL);
        CMD("rm openldap-2.6.10.tgz", return NULL);
        return "openldap-2.6.10";
}

int
build(void)
{
        CMD("wget https://www.linuxfromscratch.org/patches/blfs/12.4/openldap-2.6.10-consolidated-1.patch -P ..",
            return 0);

        CMD("groupadd -g 83 ldap", return 0);
        CMD("useradd -c \"OpenLDAP Daemon Owner\"  \
         -d /var/lib/openldap -u 83                \
         -g ldap -s /bin/false ldap", goto bad);

        CMD("patch -Np1 -i ../openldap-2.6.10-consolidated-1.patch", goto bad);
        CMD("autoconf", goto bad);
        CMD("./configure --prefix=/usr         \
            --sysconfdir=/etc                  \
            --localstatedir=/var               \
            --libexecdir=/usr/lib              \
            --disable-static                   \
            --disable-debug                    \
            --with-tls=openssl                 \
            --with-cyrus-sasl                  \
            --without-systemd                  \
            --enable-dynamic                   \
            --enable-crypt                     \
            --enable-spasswd                   \
            --enable-slapd                     \
            --enable-modules                   \
            --enable-rlookups                  \
            --enable-backends=mod              \
            --disable-sql                      \
            --disable-wt                       \
            --enable-overlays=mod", goto bad);
        CMD("make depend -j" FORGE_PREFERRED_MAKEFILE_JFLAGS, goto bad);
        return make(NULL);

 bad:
        (void)cmd("userdel -r ldap");
        (void)cmd("groupdel ldap");
        return 0;
}

int
install(void)
{
        if (!make("install")) return 0;
        CMD("sed -e \"s/\\.la/.so/\" -i /etc/openldap/slapd.{conf,ldif}{,.default}", return 0);
        CMD("install -v -dm700 -o ldap -g ldap /var/lib/openldap", return 0);
        CMD("install -v -dm700 -o ldap -g ldap /etc/openldap/slapd.d", return 0);
        CMD("chmod -v 640 /etc/openldap/slapd.{conf,ldif}", return 0);
        CMD("chown -v root:ldap /etc/openldap/slapd.{conf,ldif}", return 0);
        CMD("install -v -dm755 /usr/share/doc/openldap-2.6.10", return 0);
        return cmd("cp -vfr doc/{drafts,rfc,guide} /usr/share/doc/openldap-2.6.10");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .msgs            = getmsgs,
        .rebuild         = NULL,
        .suggested       = getsugg,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
