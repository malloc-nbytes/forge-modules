#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/make-ca.html

char *deps[] = {"p11-glue@p11-kit", "GNU@libtasn1", NULL};
char *sugg[] = {"Mozilla@NSS", NULL};

char *msgs[] = {
        "Be sure to run " YELLOW "/usr/sbin/make-ca -g" RESET,
        "for packages to see that this is installed as a dependency.",
        "If running the script a second time with the same version of certdata.txt,",
        "for instance, to update the stores when make-ca is upgraded, or to add additional",
        "stores as the requisite software is installed, replace the " YELLOW "-g" RESET " switch with the",
        YELLOW "-r" RESET " switch in the command line. If packaging, run make-ca --help to see all available command line options.",
        "",
        "  -LFS [" YELLOW "https://www.linuxfromscratch.org/blfs/view/stable/postlfs/make-ca.html" RESET "]",
        NULL,
};

char *getname(void)  { return "make-ca@make-ca"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "PKI setup script"; }
char *getweb(void)   { return "https://github.com/lfs-book/make-ca/"; }

char *
download(void)
{
        return git_clone("lfs-book", "make-ca");
}

int
install(void)
{
        if (!make("install")) return 0;
        return cmd("install -vdm755 /etc/ssl/local");
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
        .build           = NULL,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
