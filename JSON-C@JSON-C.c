#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/general/json-c.html

char *deps[] = {"Kitware@cmake", NULL};

char **getdeps(void) { return deps; }
char *getname(void)  { return "JSON-C@JSON-C"; }
char *getver(void)   { return "0.18.0"; }
char *getdesc(void)  { return "Portable C library that encodes and decodes DER/BER data"; }
char *getweb(void)   { return "https://ftp.gnu.org/gnu/libtasn1/"; }

char *
download(void)
{
        if (!cmd("wget -O json-c.tar.gz https://s3.amazonaws.com/json-c_releases/releases/json-c-0.18.tar.gz"))
                return NULL;

        mkdirp("json-c");

        CMD("tar -vxf ./json-c.tar.gz -C json-c", {
                forge_io_rm_dir("json-c.tar.gz");
                return NULL;
        });

        (void)cmd("rm json-c.tar.gz");

        return "json-c";
}

int
build(void)
{
        if (!cd("json-c-0.18")) return 0;
        CMD("sed -i 's/VERSION 2.8/VERSION 4.0/' apps/CMakeLists.txt", return 0);
        CMD("sed -i 's/VERSION 3.9/VERSION 4.0/' tests/CMakeLists.txt", return 0);
        if (!mkdirp("build")) return 0;
        CD("build", return 0);
        CMD("cmake -D CMAKE_INSTALL_PREFIX=/usr \
                -D CMAKE_BUILD_TYPE=Release     \
                -D BUILD_STATIC_LIBS=OFF        \
                ..", return 0);
        return make(NULL);
}

int
install(void)
{
        if (!cd("json-c-0.18/build")) return 0;
        return make("install");
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
