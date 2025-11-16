#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/libcap.html

char *deps[] = {
        "Linux-PAM@Linux-PAM-1.7.1",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "Linux@libcap-2.76.0"; }
char *getver(void)   { return "2.76.0"; }
char *getdesc(void)  { return "<No Description>"; }
char *getweb(void)   { return "https://www.kernel.org/pub/linux/libs/security/linux-privs/libcap2"; }

char *
download(void)
{
        CMD("wget \
             https://www.kernel.org/pub/linux/libs/security/linux-privs/libcap2/libcap-2.76.tar.xz",
            return NULL);
        CMD("tar -vxf libcap-2.76.tar.xz", return NULL);
        CMD("rm libcap-2.76.tar.xz", return NULL);
        return "libcap-2.76";
}

int
build(void)
{
        return cmd("make -C pam_cap");
}

int
install(void)
{
        CMD("install -v -m755 pam_cap/pam_cap.so $DESTDIR/usr/lib/security", return 0);
        return cmd("install -v -m644 pam_cap/capability.conf $DESTDIR/etc/security");
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
