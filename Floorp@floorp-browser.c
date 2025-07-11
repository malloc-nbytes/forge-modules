#include <stdio.h>
#include <stdlib.h>

#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

static const char *desktop = "[Desktop Entry]\n"
        "Version=1.0\n"
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

char *getname(void) { return "Floorp@floorp-browser"; }
char *getver(void) { return "11.28.0"; }
char *getdesc(void) { return "A browser based off of Firefox"; }
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("wget -O floorp-zipped.tar.bz2 https://github.com/Floorp-Projects/Floorp/releases/download/v11.28.0/floorp-11.28.0.linux-x86_64.tar.bz2");
        printf("Unzipping (bz2)\n");
        cmd("bzip2 -vd ./floorp-zipped.tar.bz2");
        printf("Unzipping (tar)\n");
        cmd("tar -vxf ./floorp-zipped.tar");
        cmd("rm floorp-zipped.tar");
        return "floorp";
}
void build(void) {}
void install(void) {
        mkdirp("/opt/floorp");
        cmd("cp -r ./* /opt/floorp");
        cmd("chmod -R 755 /opt/floorp");
        cmd("chmod +x /opt/floorp/floorp /opt/floorp/floorp-bin");
        cmd("ln -s /opt/floorp/floorp-bin " FORGE_PREFERRED_INSTALL_PREFIX "/bin/floorp");

        // Desktop Entry
        mkdirp("/usr/share/applications/");
        forge_io_create_file("/usr/share/applications/floorp.desktop", 1);
        forge_io_write_file("/usr/share/applications/floorp.desktop", desktop);
        cmd("chmod 644 /usr/share/applications/floorp.desktop");
}
void uninstall(void) {
        cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/floorp");
        cmd("rm -r /opt/floorp");
        cmd("rm /usr/share/applications/floorp.desktop");
}

FORGE_GLOBAL pkg package = {
        .name = getname,
        .ver = getver,
        .desc = getdesc,
        .deps = NULL,
        .download = download,
        .build = build,
        .install = install,
        .uninstall = uninstall,
        .update = forge_pkg_update_manual_check,
        .get_changes = forge_pkg_get_changes_redownload,
};
