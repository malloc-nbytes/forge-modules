#include <forge/forge.h>

char *deps[] = {
        "rockdaboot@libpsl-0.21.5",
        NULL,
};

char **getdeps(void) { return deps; }
char *getname(void)  { return "cURL@cURL-8.15.0"; }
char *getver(void)   { return "8.15.0"; }
char *getdesc(void)  { return "Library used for transferring files with URL syntax"; }
char *getweb(void)   { return "https://curl.se/"; }

char *
download(void)
{
        CMD("wget https://curl.se/download/curl-8.15.0.tar.xz", return NULL);
        CMD("tar -vxf curl-8.15.0.tar.xz", return NULL);
        CMD("rm curl-8.15.0.tar.xz", return NULL);
        return "curl-8.15.0";
}

int
build(void)
{
        CMD("./configure --prefix=/usr \
            --disable-static \
            --with-openssl   \
            --with-ca-path=/etc/ssl/certs", return 0);
        return make(NULL);
}

int
install(void)
{

        if (!make("install")) return 0;
        CMD("find docs \\( -name Makefile\\* -o  \
             -name \\*.1       -o  \
             -name \\*.3       -o  \
             -name CMakeLists.txt \\) -delete", return 0);
        return cmd("cp -v -R docs -T $DESTDIR/usr/share/doc/curl-8.15.0");
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

