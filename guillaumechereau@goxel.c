#include <forge/forge.h>

// TODO
/* char *deps[] = { */
/*         "pkg-config", */
/*         "scons", */
/*         "libglfw3-dev", */
/*         "libgtk-3-dev", */
/*         NULL, */
/* }; */

char *getname(void)  { return "guillaumechereau@goxel"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Free and Open Source 3D Voxel Editor"; }
char *getweb(void)   { return "https://github.com/guillaumechereau/goxel"; }

char *
download(void)
{
        return git_clone("guillaumechereau", "goxel");
}

int
build(void)
{
        return make("release");
}

int
install(void)
{
        return make("install");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
