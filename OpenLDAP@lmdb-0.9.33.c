#include <forge/forge.h>

#include <stdio.h>

// https://www.linuxfromscratch.org/blfs/view/stable/server/lmdb.html

char *getname(void)  { return "OpenLDAP@lmdb-0.9.33"; }
char *getver(void)   { return "0.9.33"; }
char *getdesc(void)  { return "Fast, compact, key-value embedded data store"; }
char *getweb(void)   { return "https://git.openldap.org/openldap/openldap/"; }

char *
download(void)
{
        CMD("wget https://git.openldap.org/openldap/openldap/-/archive/LMDB_0.9.33.tar.bz2",
            return NULL);
        CMD("tar -vxf LMDB_0.9.33.tar.bz2", return NULL);
        CMD("rm LMDB_0.9.33.tar.bz2", return 0);
        return "openldap-LMDB_0.9.33-3a29a24777c82a0165de813ae696a5068b5add30";
}

int
build(void)
{
        CD("libraries/liblmdb", return 0);
        if (!make(NULL)) return 0;
        return cmd("sed -i 's| liblmdb.a||' Makefile");
}

int
install(void)
{
        return cmd("make prefix=/usr -j" FORGE_PREFERRED_MAKEFILE_JFLAGS);
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = NULL,
        .suggested       = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
