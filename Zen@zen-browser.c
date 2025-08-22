#include <stdlib.h>

#include <forge/forge.h>

char *deps[] = {NULL}; // Must be NULL terminated

static const char *desktop = "[Desktop Entry]\n"
        "Version=1.0\n"
        "Name=Zen\n"
        "GenericName=Web Browser\n"
        "Keywords=Internet;WWW;Browser;Web;Explorer;Zen\n"
        "Exec=/opt/zen/zen %u\n"
        "Terminal=false\n"
        "Type=Application\n"
        "Icon=/opt/zen/browser/chrome/icons/default/default128.png\n"
        "Categories=Network;WebBrowser;\n"
        "MimeType=text/html;text/xml;application/xhtml+xml;application/xml;application/rss+xml;application/rdf+xml;image/gif;image/jpeg;image/png;x-scheme-handler/http;x-scheme-handler/https;x-scheme-handler/ftp;x-scheme-handler/chrome;video/webm;application/x-xpinstall;\n"
        "StartupNotify=true\n"
        "Actions=new-window;new-private-window;\n"
        "[Desktop Action new-window]\n"
        "Name=Open a New Window\n"
        "Exec=/opt/zen/zen -new-window\n"
        "[Desktop Action new-private-window]\n"
        "Name=Open a New Private Window\n"
        "Exec=/opt/zen/zen -private-window";

char *getname(void) { return "Zen@zen-browser"; }
char *getver(void) { return "1.14.5b"; }
char *getdesc(void) { return "A browser based off of Firefox"; }
char *getweb(void) { return "https://github.com/zen-browser/desktop/releases/"; }
char **getdeps(void) { return deps; }
char *download(void) {
        cmd("curl -O -L https://github.com/zen-browser/desktop/releases/latest/download/zen.linux-x86_64.tar.xz");
        cmd("tar -vxf zen.linux-x86_64.tar.xz");
        cmd("rm zen.linux-x86_64.tar.xz");
        return "zen";
}
int build(void) { return 1; }
int install(void) {
        mkdirp("/opt/zen");
        cmd("cp -r ./* /opt/zen");
        cmd("chmod -R 755 /opt/zen");
        cmd("chmod +x /opt/zen/zen /opt/zen/zen-bin");
        cmd("ln -s /opt/zen/zen-bin " FORGE_PREFERRED_INSTALL_PREFIX "/bin/zen");

        // Desktop Entry
        mkdirp("/usr/share/applications/");
        forge_io_create_file("/usr/share/applications/zen.desktop", 1);
        forge_io_write_file("/usr/share/applications/zen.desktop", desktop);
        return cmd("chmod 644 /usr/share/applications/zen.desktop");
}
int uninstall(void) {
        cmd("rm " FORGE_PREFERRED_INSTALL_PREFIX "/bin/zen");
        cmd("rm -r /opt/zen");
        return cmd("rm /usr/share/applications/zen.desktop");
}

FORGE_GLOBAL pkg package = {
        .name = getname,
        .ver = getver,
        .desc = getdesc,
        .web = getweb,
        .deps = NULL,
        .download = download,
        .build = build,
        .install = install,
        .uninstall = uninstall,
        .update = forge_pkg_update_manual_check,
        .get_changes = forge_pkg_get_changes_redownload,
};
