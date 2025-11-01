#include <stdio.h>
#include <stdlib.h>

#include <forge/forge.h>

#define VERSION "12.2.1"

static const char *desktop = "[Desktop Entry]\n"
        "Version=" VERSION "\n"
        "Name=Floorp\n"
        "GenericName=Web Browser\n"
        "Keywords=Internet;WWW;Browser;Web;Explorer;Floorp\n"
        "Exec=/opt/floorp/floorp %u\n"
        "Terminal=false\n"
        "Type=Application\n"
        "Icon=/opt/floorp/browser/chrome/icons/default/default128.png\n"
        "Categories=Network;WebBrowser;\n"
        "MimeType=text/html;text/xml;application/xhtml+xml;application/xml;application/rss+xml;application/rdf+xml;image/gif;image/jpeg;image/png;x-scheme-handler/http;x-scheme-handler/https;x-scheme-handler/ftp;x-scheme-handler/chrome;video/webm;application/x-xpinstall;\n"
        "StartupNotify=true\n"
        "Actions=new-window;new-private-window;\n"
        "[Desktop Action new-window]\n"
        "Name=Open a New Window\n"
        "Exec=/opt/floorp/floorp -new-window\n"
        "[Desktop Action new-private-window]\n"
        "Name=Open a New Private Window\n"
        "Exec=/opt/floorp/floorp -private-window";

char *getname(void)  { return "Floorp@floorp-browser-" VERSION; }
char *getver(void)   { return VERSION; }
char *getdesc(void)  { return "A browser based off of Firefox"; }
char *getweb(void)   { return "https://github.com/Floorp-Projects/Floorp/releases/"; }

char *download(void) {
        CMD("wget -O floorp-zipped.tar.xz https://github.com/Floorp-Projects/Floorp/releases/download/v12.2.1/floorp-linux-amd64.tar.xz", {
                forge_io_rm_dir("floorp-zipped.tar.xz");
                return NULL;
        });
        mkdirp("floorp-" VERSION);
        CMD("tar -vxf ./floorp-zipped.tar.xz -C floorp-" VERSION, {
                forge_io_rm_dir("floorp-zipped.tar.xz");
                return NULL;
        });
        cmd("rm floorp-zipped.tar.xz");
        return "floorp-"  VERSION;
}

int install(void) {
        cd("floorp");
        //mkdirp("$DESTDIR/opt/floorp");
        cmd("mkdir -p $DESTDIR/opt/floorp", return 0);
        CMD("cp -r ./* $DESTDIR/opt/floorp", {
                return 0;
        });
        CMD("chmod -R 755 $DESTDIR/opt/floorp", {
                return 0;
        });
        CMD("chmod +x $DESTDIR/opt/floorp/floorp $DESTDIR/opt/floorp/floorp-bin", {
                return 0;
        });
        CMD("ln -s $DESTDIR/opt/floorp/floorp-bin " FORGE_PREFERRED_INSTALL_PREFIX "/bin/floorp", {
                return 0;
        });

        // Desktop Entry
        //mkdirp("$DESTDIR/usr/share/applications/");
        CMD("mkdir -p $DESTDIR/usr/share/applications", return 0);
        forge_io_create_file("$DESTDIR/usr/share/applications/floorp.desktop", 1);
        forge_io_write_file("$DESTDIR/usr/share/applications/floorp.desktop", desktop);
        cmd("chmod 644 $DESTDIR/usr/share/applications/floorp.desktop");

        return 1;
}
int uninstall(void) {
        cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/floorp");
        cmd("rm -r /opt/floorp");
        cmd("rm /usr/share/applications/floorp.desktop");
        return 1;
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .download        = download,
        .build           = NULL,
        .install         = install,
        .uninstall       = uninstall,
        .update          = forge_pkg_update_manual_check,
        .get_changes     = forge_pkg_get_changes_redownload,
};
