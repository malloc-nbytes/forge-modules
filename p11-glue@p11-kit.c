#include <forge/forge.h>

// https://www.linuxfromscratch.org/blfs/view/stable/postlfs/p11-kit.html

char *sugg[] = {"libtasn1@libtasn1", NULL};

char *getname(void)  { return "p11-glue@p11-kit"; }
char *getver(void)   { return "rolling"; }
char *getdesc(void)  { return "Provides a way to load and enumerate PKCS#11 modules"; }
char *getweb(void)   { return "https://github.com/p11-glue/p11-kit"; }

char *
download(void)
{
        return git_clone("p11-glue", "p11-kit");
}

int
build(void)
{
        CMD("sed '20,$ d' -i trust/trust-extract-compat", return 0);
        CMD("cat >> trust/trust-extract-compat << \"EOF\" "
            "/usr/libexec/make-ca/copy-trust-modifications "
            "/usr/sbin/make-ca -r "
            "\"EOF\"", return 0);
        if (!mkdirp("p11-build")) return 0;
        if (!cd("p11-build")) return 0;
        CMD("meson setup ..           \
                 --prefix=/usr        \
                 --buildtype=release  \
                 -D trust_paths=/etc/pki/anchors",
            return 0);
        return cmd("ninja");
}

int
install(void)
{
         CMD("ninja install", return 0);
         return cmd("ln -sfv /usr/libexec/p11-kit/trust-extract-compat $DESTDIR/usr/bin/update-ca-certificates");

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
