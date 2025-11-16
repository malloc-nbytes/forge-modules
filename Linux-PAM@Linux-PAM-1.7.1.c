#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/linux-pam.html

// TODO: suggested: libnsl-2.0.1, libtirpc-1.3.6, rpcsvc-proto-1.4.4, Berkeley DB (deprecated), libaudit, and libeconf

// TODO: rebuild shadow
// TODO: require ninja, meson

char *msgs[] = {
        "The following kernel changes must be done for PAM:",
        "General setup --->",
        "  [*] Auditing support                                                   [AUDIT]",
        "",
        "NOTE: Installing/updating this package overwrites the configuration files in",
        YELLOW "    /etc/security" RESET " as well as " YELLOW "/etc/environment" RESET ".",
        "    If you have modified those files, be sure to back them up",
        "",
        "NOTE: For information on how to configure Linux-PAM, refer to:",
        YELLOW "    https://www.linuxfromscratch.org/blfs/view/stable/postlfs/linux-pam.html" RESET,
        NULL,
};

char *rebuild[] = {
        "Linux@libcap-2.76.0",
        NULL,
};

char **getrebuild(void) { return rebuild; }
char **getmsgs(void) { return msgs; }
char *getname(void)  { return "Linux-PAM@Linux-PAM-1.7.1"; }
char *getver(void)   { return "1.7.1"; }
char *getdesc(void)  { return "Pluggable Authentication Modules"; }
char *getweb(void)   { return "https://github.com/linux-pam/linux-pam"; }

char *
download(void)
{
        CMD("wget https://github.com/linux-pam/linux-pam/releases/download/v1.7.1/Linux-PAM-1.7.1.tar.xz", return NULL);
        CMD("tar -vxf Linux-PAM-1.7.1.tar.xz", return NULL);
        CMD("rm Linux-PAM-1.7.1.tar.xz", return NULL);
        return "Linux-PAM-1.7.1";
}

int
build(void)
{
        if (!mkdirp("build")) return 0;
        CD("build", return 0);
        CMD("meson setup ..        \
               --prefix=/usr       \
               --buildtype=release \
               -D docdir=/usr/share/doc/Linux-PAM-1.7.1", return 0);
        return cmd("ninja");
}

int
install(void)
{
        CD("build", return 0);

        CMD("install -v -m755 -d $DESTDIR/etc/pam.d", return 0);

        if (!forge_pkg_is_installed("Linux-PAM@Linux-PAM-1.7.1")) {
                // Create a new config.
                CMD("cat > $DESTDIR/etc/pam.d/other << EOF\n"
                    "auth     required       pam_deny.so\n"
                    "account  required       pam_deny.so\n"
                    "password required       pam_deny.so\n"
                    "session  required       pam_deny.so\n"
                    "EOF", return 0);
        } else {
                // Reuse the config that is there already.
                CMD("cat /etc/pam.d/other > $DESTDIR/etc/pam.d/other", return 0);
        }

        CMD("ninja test", return 0);

        if (!forge_pkg_is_installed("Linux-PAM@Linux-PAM-1.7.1")) {
                // Remove newly created config for tests.
                CMD("rm -fv $DESTDIR/etc/pam.d/other", return 0);
        }

        CMD("ninja install", return 0);
        CMD("chmod -v 4755 $DESTDIR/usr/sbin/unix_chkpwd", return 0);
        return cmd("rm -rf $DESTDIR/usr/lib/systemd");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = getmsgs,
        .suggested       = NULL,
        .rebuild         = getrebuild,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
