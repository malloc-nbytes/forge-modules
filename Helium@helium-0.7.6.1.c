#include <forge/forge.h>

#define VERSION "0.7.6.1"

const char *desktop =
        "[Desktop Entry]\n"
        "Version=1.0\n"
        "Name=Helium\n"
        "GenericName=Web Browser\n"
        "Comment=Access the Internet\n"
        "Exec=/opt/helium/helium %U\n"
        "StartupNotify=true\n"
        "StartupWMClass=helium\n"
        "Terminal=false\n"
        "Icon=helium\n"
        "Type=Application\n"
        "Categories=Network;WebBrowser;\n"
        "MimeType=application/pdf;application/rdf+xml;application/rss+xml;application/xhtml+xml;application/xhtml_xml;application/xml;image/gif;image/jpeg;image/png;image/webp;text/html;text/xml;x-scheme-handler/http;x-scheme-handler/https;\n"
        "Actions=new-window;new-private-window;\n"
        "\n"
        "[Desktop Action new-window]\n"
        "Name=New Window\n"
        "Exec=/opt/helium/helium %u\n"
        "\n"
        "[Desktop Action new-private-window]\n"
        "Name=New Incognito Window\n"
        "Exec=/opt/helium/helium --incognito\n";

char *getname(void)  { return "Helium@helium-browser-" VERSION; }
char *getver(void)   { return VERSION; }
char *getdesc(void)  { return "A privacy-focused browser based off of Chromium"; }
char *getweb(void)   { return "https://github.com/Helium-Projects/Helium/releases/"; }

char *
download(void)
{
        CMD("wget -O helium-zipped.tar.xz https://github.com/imputnet/helium-linux/releases/download/" VERSION "/helium-" VERSION "-x86_64_linux.tar.xz", {
                forge_io_rm_dir("helium-zipped.tar.xz");
                return NULL;
        });
        mkdirp("helium-" VERSION);
        CMD("tar -vxf ./helium-zipped.tar.xz -C helium-" VERSION, {
                forge_io_rm_dir("helium-zipped.tar.xz");
                return NULL;
        });
        cmd("rm helium-zipped.tar.xz");
        return "helium-"  VERSION;
}

int
install(void)
{
        cd("helium-" VERSION "-x86_64_linux");
        CMD("mv chrome helium",                                                                 return 0);
        CMD("mkdir -p $DESTDIR/opt/helium",                                                     return 0);
        CMD("cp -r ./* $DESTDIR/opt/helium",                                                    return 0);
        CMD("chmod -R 755 $DESTDIR/opt/helium",                                                 return 0);
        CMD("chmod +x $DESTDIR/opt/helium/helium",                                              return 0);
        CMD("ln -sf $DESTDIR/opt/helium/helium " FORGE_PREFERRED_INSTALL_PREFIX "/bin/helium",  return 0);
        CMD("ln -sf /opt/helium/helium " FORGE_PREFERRED_INSTALL_PREFIX "/bin/helium",          return 0);

        // Desktop Entry
        CMD("mkdir -p $DESTDIR/usr/share/applications", return 0);
        //CMD("cp helium.desktop $DESTDIR/usr/share/applications/helium.desktop", return 0);
        char *desktop_fp = forge_cstr_builder(env("DESTDIR"), "/usr/share/applications/helium.desktop", NULL);
        forge_io_create_file(desktop_fp, 1);
        forge_io_write_file(desktop_fp, desktop);
        CMD("chmod 644 $DESTDIR/usr/share/applications/helium.desktop", return 0);

        free(desktop_fp);

        return 1;
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .msgs            = NULL,
        .suggested       = NULL,
        .rebuild         = NULL,
        .web             = getweb,
        .deps            = NULL,
        .download        = download,
        .build           = NULL,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
